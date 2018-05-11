#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
#include "mshell.h"

#define     BUFFER_SIZE     1024
#define     MAXRD           255

static int extractRedirect(char* buf, char* input, char* output);
static char* skipWS(char* arg);
static Command* addCommandStage(Command* c, Stage* s);
static void freeStage(Stage* s);

/* Skip white spaces. 
 * Returns a pointer to the first non-space character 
 * or NULL if there is none.
 * */
static char * skipWS(char * arg)
{
    while (arg && *arg && isspace(*arg)) 
        arg++;
    return arg;
}

/*
 *  Returns NULL on errors
 *  Otherwise, returns a pointer to a string, which can be empty!
 *  pos will be changed to the position of NULL or the character after the current argument.
 */
static char *get_argument(char * buffer, int *pos)
{
    char *p0 = skipWS(buffer + *pos);

    if (! *p0)   // empty argument
        return p0;

    if (*p0 == '\'' || *p0 == '"') {
        int qmark = *p0 ++;

        // quoted. search for the first qmark
        char *p = strchr(p0, qmark);
        if (p == NULL) {
            ERROR_MSG("String missing the ending quotation mark.");
            return NULL;
        }
        *p ++ = 0;
        *pos = p - buffer;
    }
    else {
        // search for the first WB
        char *p = p0;
        while (*p && ! isspace(*p)) 
            p ++;
        if (*p) {
            *p++ = 0;
        }
        *pos = p - buffer;
    }
    return p0;
}

#if 0
/* remove trailing white spaces */
int trimString(char* buf, int len)
{
    char* ptr = buf + len - 1;
    while (ptr >= buf && isspace(*ptr))
        ptr--, len--;
    *++ptr = 0;
    return len;
}
#endif

/* Allocate memory for a new command */
static Command* allocCommand()
{
    Command * r = (Command*)calloc(1, sizeof(Command));
    // The following assignments are not really necessary.
    r->cmd = NULL;
    r->kind = noCMD;
    r->mode = R_NONE;
    return r;
}

/* free the space of a command */
static Command * freeCommand(Command * c)
{
    if (c->cmd) 
        free(c->cmd);
    if (c->input) 
        free(c->input);
    if (c->output) 
        free(c->output);
    for (int i = 0; i < c->num_args; i++)
        if (c->args[i]) 
            free(c->args[i]);
    free(c->args);
    if (c->stages) { 
        for(int j = 0; j < c->num_stages; j++)
            freeStage(c->stages[j]);
        free(c->stages);
    }
    free(c);
    return NULL;
}

static Command * setCommand(Command* c, enum Kind k, char* com)
{
    c->kind = k;
    if (c->cmd) 
        free(c->cmd);
    c->cmd = strdup(com);
    return c;
}

// allocate (nb+1) pointers
// copy strings
// set the last pointer to be NULL
static Command * setCommandArgs(Command * c, int na, char** args)
{
    c->num_args = na + 1;
    c->args = (char**) malloc(sizeof(char*) * c->num_args);
    for (int i = 0; i < na; i++)
        c->args[i] = strdup(args[i]);
    c->args[na] = NULL;
    return c;
}

static Command* addCommandStage(Command* c, Stage* s)
{
    printf("New stage:");
    printStage(s);

    c->stages = realloc(c->stages, sizeof(Stage*) * (c->num_stages + 1));
    c->num_stages += 1;
    c->stages[c->num_stages - 1] = s;
    return c;
}

static void printCommand(Command* c)
{
    if (c->mode & R_INPUT)
        printf("<  [%s]\n", c->input);
    if (c->mode & R_OUTPUT)
        printf(">  [%s]\n", c->output);
    if (c->mode & R_APPEND)
        printf(">> [%s]\n", c->output);
    printf("CORE: %s\n", c->cmd);
    for(int i = 0; i < c->num_args; i++)
        printf("\targs[%d] = %s\n", i, c->args[i]);
    if (c->num_stages > 0) {
        printf("Stages:");
        for (int i = 0; i < c->num_stages; i++)
            printStage(c->stages[i]);
        printf("\n");
    }
}

/* ==== functions about stages ==== */

// print all the arguments in this stage
void printStage(Stage* s)
{
    printf("\t(%d)[",s->num_args);
    for (int i = 0; i < s->num_args; i++)
        if (s->args[i] != NULL)
            printf("%s ",s->args[i]);
        else
            printf("null ");
    printf("]\n");
}

// allocate memory for Stages
static Stage * allocStage(int nba, char ** args)
{
    Stage* s = (Stage*)calloc(1, sizeof(Stage));
    s->num_args = nba + 1;
    s->args = (char**)calloc(s->num_args, sizeof(char*));
    s->fdin = s->fdout = -1;
    s->child = -1;
    for (int i = 0; i < nba; i++)
        s->args[i] = strdup(args[i]);
    // used calloc. s->args[nba] should be NULL.
    return s;
}

// free the memory for Stages
static void freeStage(Stage* s)
{
    for (int i = 0; i < s->num_args; i++) 
        if (s->args[i] != NULL)  // should be fine to free NULL too
            free(s->args[i]);
    free(s->args);
    free(s);
}

#define GET_ARG(a)  do{(a) = get_argument(buffer, &pos); if (!(a)) return freeCommand(c);} while (0)

/* ==== the messy function that makes Command from the command line  ==== */
static Command* makeCommand()
{
    char buffer[BUFFER_SIZE];
    int  i;
    char ch;

    printf("%% ");
    fflush(stdout);

    // Read a command into buffer
    i = 0;
    while (i < (BUFFER_SIZE - 1) && (ch = getchar()) != '\n' && ch != EOF)
        buffer[i++] = ch;

    if (i == BUFFER_SIZE) { // too long
        ERROR_MSG("Command is too long.\n");
        while ((ch = getchar()) != '\n' && ch != EOF);
        return NULL;
    }
    buffer[i] = 0;

    Command* c = allocCommand();
    if (ch == EOF) {
        if (buffer[0]) 
            ERROR_MSG("A command does not end with a new line."); 
        return setCommand(c, exitCMD, "exit");
    }

    { // dealing with indirect
        char input[BUFFER_SIZE];
        char output[BUFFER_SIZE];
        *input = *output = 0;

        int mode = extractRedirect(buffer, input, output);
        if (mode < 0) 
            return freeCommand(c);

        c->mode = mode;
        c->input = strdup(input);
        c->output = strdup(output);
    }

    int    pos = 0;
    char * pipe = strchr(buffer, '|');

    if (pipe == NULL) {
        // basic command 
        char * sc;
        GET_ARG(sc);
        
        if (*sc == 0) {
            if (c->mode) 
                ERROR_MSG("An empty command with redirect."); 
            return freeCommand(c);
        } else if (!strcmp(sc, "cd")) {
            char * a0 = get_argument(buffer, &pos);
            char * args[1] = {a0};
            return setCommandArgs(setCommand(c, cdCMD, sc), 1, args);
        } else if (strcmp(sc,"exit") == 0) {
            return setCommand(c,exitCMD,sc);
        } else { // basic command 
            char *  args[BUFFER_SIZE];
            int     na = 0;
            char *  arg = sc;

            while (*arg) {
                args[na++] = arg;
                assert(na < BUFFER_SIZE);
                GET_ARG(arg);
            }
            return setCommandArgs(setCommand(c, basicCMD, args[0]), na, args);
        }
    } else  { // This is a pipeline.
        char *  args[BUFFER_SIZE];
        int     na;
        char *  arg;
        int     done = 0;

        setCommand(c, pipelineCMD, "");

        do {
            if (pipe) // if there are more than one stage, turn '|' to NULL
                *pipe = 0;
            na = 0;
            do {
                GET_ARG(arg);
                if (*arg) {
                    args[na++] = arg;
                    assert(na < BUFFER_SIZE);
                }
            } while (*arg); 

            if (na == 0) {
                ERROR_MSG("Empty pipeline stage.");
                return freeCommand(c);
            }

            addCommandStage(c, allocStage(na, args));

            if (pipe) {
                pos = (pipe - buffer) + 1; 
                pipe = strchr(pipe + 1, '|');
            }
            else 
                done = 1;
        } while (! done);

        return c;
    }

    return c;
}

/* Find a file path, save it to fn. 
 * Replace the characters in buf with space.
 * fn has at least MAXRD bytes.
 * Return the pointer to a space or NULL if successful.
 * return NULL on erros. 
 */
static char * get_redirect_file (char *buf, char *fn)
{
    char    *p = skipWS(buf);
    int     ch, i = 0;

    while ((ch = *p) != 0 && !isspace(ch)) {
        if (isalnum(ch) || ch == '.' || ch == '-' || ch == '/' || ch == '_') {
            // valid characters in file path
            if (i + 1 >= MAXRD) {
                ERROR_MSG("File path is too long.");
                return NULL;
            }
            fn[i ++] = ch;
        } else {
            ERROR_MSG("Invalid characters in file path.");
            return NULL;
        }
        *p ++ = ' ';
    }
    fn[i] = 0;
    return p;
}

/* The routine extracts any redirects and replaces those parts of the command
   by whitespaces.

   save the input file path in input.
   save the output file path in input.

   return a negative value on errors.

   return a valid mode otherwsie.
   */
static int extractRedirect(char* buf, char* input, char* output)
{
    char* ptr = buf; // may use buf directly
    int mode = R_NONE;

    while (ptr && *ptr) {
        int ch = *ptr;
        if (ch == '<') {
            if (mode & R_INPUT) {
                ERROR_MSG("Ambiguous input redirect.");
                return -1;
            } 
            ptr[0] = ' ';
            ptr = get_redirect_file(ptr + 1, input);  
            if (ptr == NULL) 
                return -2;
            if (! input[0]) {
                ERROR_MSG("Input redirect file name not found.");
                return -3;
            } 
            mode |= R_INPUT;
        } else if (ch == '>' && ptr[1] == '>') {
            if (mode & (R_APPEND | R_OUTPUT)) {
                ERROR_MSG("Ambiguous output redirect\n");
                return -11;
            } 
            ptr[0] = ' ';
            ptr[1] = ' ';
            ptr = get_redirect_file(ptr + 2, output);  
            if (ptr == NULL) 
                return -12;
            if (! output[0]) {
                ERROR_MSG("Output redirect file name not found.");
                return -13;
            } 
            mode |= R_APPEND;
        } else if (ch == '>') {
            if (mode & (R_APPEND | R_OUTPUT)) {
                ERROR_MSG("Ambiguous output redirect\n");
                return -21;
            } 
            ptr[0] = ' ';
            ptr = get_redirect_file(ptr + 1, output);  
            if (ptr == NULL) 
                return -22;
            if (! output[0]) {
                ERROR_MSG("Output redirect file name not found.");
                return -23;
            } 
            mode |= R_OUTPUT;
        } else 
            ptr++;
    }
    return mode;
}

// execut a command 
static int executeCommand (Command * c)
{
    switch (c->kind) {
        case cdCMD: {
            // redirect is ignored
            int st = chdir(c->args[0]);
            if (st == -1)
                fprintf(stderr, "cd error: [%s]\n", strerror(errno));
            return TRUE;
        }
        case exitCMD:
            return FALSE;
        case basicCMD: {
            return basicExecute(c->cmd,c->mode,c->input,c->output,c->args);
        }
        case pipelineCMD: {
            setupCommandPipeline(c);
            return TRUE;
        }
        case noCMD: {
            return TRUE;
        }
        default:
            ERROR_MSG("oops, unknown command type.");
            return TRUE;
    }
}

int main(int argc,char* argv[])
{
    int loop = 1;

    while (loop) {
        Command * cmd  = makeCommand();
        if (cmd == NULL)
            continue;
        printCommand(cmd);
        loop = executeCommand(cmd);
        freeCommand(cmd);
    }
    return 0;
}

