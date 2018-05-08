#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

#include <errno.h>
#include <assert.h>

#define ERROR_MSG(x)  fprintf(stderr, "%s\n", (x))

#define BUF_SIZE    1024

typedef struct program_tag {
    char**   args;      // array of pointers to arguments
    int      num_args;  // number of arguments
    int	     pid;	// process ID of this program
    int      fdpcr;     // parent to child, read
    int      fdpcw;     // parent to child, write
    int      fdcpr;     // child to parent, read
    int      fdcpw;     // child to parent, write
    char*    buf;       // buffer to save the output of the program
    int      buf_size;  // the size of allocated buffer
} Program;


/* start a program
 * The informaton about one or more programs is passed in.
 * parameters:
 *      progs:  array of pointers to Program.
 *      total:  number of valid programs in progs.
 *      cur:    the one that needs to be started.
 *
 *  You need fork and then turn child into the program.
 *  Close pipes that are not used.
 */
void start_program(Program *progs, int total, int cur)
{
    // TODO
    //int pc[2], cp[2];
    //pipe(pc);
   // pipe(cp);
    pid_t child = fork();
    progs->fdcpr = chtopr;
    progs->fdpcw = patochw;

    if (child == 0){}
    if (progs->fdcpr != -1){ //check that fdin has stuff in it
            dup2(progs->fdcpr, progs->fdpcr); // 
            close(progs->fdpcr);
; //
        }
        if (s->fdout != -1){
            dup2(progs->fdcpw, progs->fdpcw);
            close(progs->fdpcw);
            
        }
        execvp(progs->args[0],progs->args );
    }
    else if (child < 0)
        exit(0);

    if (child){ //parent process
        if (progs->fdcpw != -1)
            close(s->fdcpw);
        if (s->fdout != -1)
            close(progs->fdcpw);
    }   
   
   
}


/* Wait on the program.
 */
int wait_on_program(Program *prog)
{
    // TODO

    int st;
    waitpid(s->child, &st, 0);
        
}


/* creae pipes to be used for communication 
 * between this process and the program.
 */
void prepare_pipe(Program *prog)
{
    // TODO
}

/* send data to a program. 
 *
 * parameters:
 *
 *  prog:   the program to receive data.
 *  buf:    buffer that contains data.
 *  len:    number of bytes to be sent.
 */
int write_to_program(Program *prog, char *buf, int len)
{
    // TODO
}

/* get result from a program
 *
 * The result is a string that ends with '\n'.
 * 
 * Save the string in prog->buf. 
 * Adjust the size of the buf if necessary.
 */
int read_from_program(Program *prog)
{
    int ttl = 0;
    // TODO
    prog->buf[ttl] = 0;
    return ttl;
}

/* clean up
 *
 * free memory, close pipes.
 */
void cleanup_program(Program *prog)
{
    // TODO
    close(
}


/*********************************************************/
/* Do not change code below                              */
/*********************************************************/
void init_program(Program *prog, int na)
{
    // allocate memory for array of arguments
    prog->args = malloc(na * sizeof(char *));
    assert(prog->args != NULL);
    prog->num_args = 0;

    // allocate memory to save reply from the program
    prog->buf_size = 10;
    prog->buf = malloc(prog->buf_size);
    assert(prog->buf != NULL);

    prog->pid = -1;
    prog->fdpcr = -1;
    prog->fdpcw = -1;
    prog->fdcpr = -1;
    prog->fdcpw = -1;
}

int main(int argc, char **argv)
{
    Program progs[2];
    int     num_programs;
    char    line[BUF_SIZE];

    if (argc <= 1) {
        ERROR_MSG("Specify one or two programs to run.");
        exit(-1);
    }

    // Prepare programs and their arguments
    num_programs = 0;
    int     cur_arg = 1;
    while (cur_arg < argc) {

        init_program(&progs[num_programs], argc);

        int     ia;
        for (ia = 0; cur_arg < argc; cur_arg ++) {
            if (!strcmp(argv[cur_arg], "--")) {
                if (num_programs == 1) {
                    ERROR_MSG("Only two programs are supported.");
                    exit(-1);
                }
                if (cur_arg + 1 == argc) {
                    ERROR_MSG("The second program is empty.");
                    exit(-1);
                }
                cur_arg ++;
                break;
            }
            progs[num_programs].args[ia++] = argv[cur_arg];
        }  
        if (ia == 0) {
            ERROR_MSG("Empty program.");
            exit(-1);
        }
        progs[num_programs].args[ia] = NULL;
        progs[num_programs].num_args = ia;
        num_programs ++;
    }

    // Prepare pipes
    for (int i = 0; i < num_programs; i ++) {
        prepare_pipe(&progs[i]);
    }

    // spawn children
    for (int i = 0; i < num_programs; i ++) {
        start_program(progs, num_programs, i);
    }

    // Get lines from stdin, send to both children, get feedback from them
    while (fgets(line, sizeof(line), stdin)) {
        int len = strlen(line);
        if (len > 0 && line[len - 1] != '\n') {
            ERROR_MSG("Line is too long, or does not have LF.");
            exit(-2);
        }

        // write to programs
        for (int i = 0; i < num_programs; i ++) {
            write_to_program(&progs[i], line, len);
        }

        // read from programs
        for (int i = 0; i < num_programs; i ++) {
            read_from_program(&progs[i]); 
        }

        // print the bufs
        for (int i = 0; i < num_programs; i ++) {
            printf("Child %d(%5d): %s", i, progs[i].pid, progs[i].buf);
        }
    } 

    // cleanup
    for (int i = 0; i < num_programs; i ++) 
        cleanup_program(&progs[i]);
   
    // wait for children
    for (int i = 0; i < num_programs; i ++) {
        printf("Waiting for %d(%5d)...\n", i, progs[i].pid);
        wait_on_program(&progs[i]);
    }
    printf("Everything is good.\n");
    return 0;
}
