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

// like a method of Stage. set the input and output fds.
static Stage * setStageInput(Stage * s, int fd)
{
    s->fdin = fd;
    return s;
}

static Stage * setStageOutput(Stage * s, int fd)
{
    s->fdout = fd;
    return s;
}

// A pipeline "object" contains
// 1. An array of nbStages stages
// 2. A mode flag to determine whether
//            - the pipeline input is redirected
//            - the pipeline output is redirected
// Each stage is a structure that encapsulates
// - The number of arguments
// - Each argument (in string form)
// BY DEFAULT THE MAIN PROGRAM CALLS THE PRINT METHOD OF THE COMMAND
// OBJECT. So you can see how the pipeline description is represented/stored
// Your objective:
//     * Implement the execute method to create and execute the entire pipeline.
// Hint: all the systems calls seen in class will be useful (fork/exec/open/close/pipe/....)
// Good Luck!

/*
 * This is actually the core: fork() and set up pipe.  
 *
 */
static void spawnStage(Stage* s)
{
    // TODO
    // only child - send forked child from command - 
    pid_t child = fork(); // fork it
    s->child = child; //create connection from parent to child
    if (child == 0){ //child process
        if (s->fdin != -1){ //check that fdin has stuff in it
            dup2(s->fdin, STDIN_FILENO); // 
            close(s->fdin); //
        }
        if (s->fdout != -1){
            dup2(s->fdout, STDOUT_FILENO);
            close(s->fdout);
        }
        execvp(s->args[0], s->args);
    }
    else if (child < 0)
        exit(0);

    if (child){ //parent process
        if (s->fdin != -1)
            close(s->fdin);
        if (s->fdout != -1)
            close(s->fdout);
    }   
    
}

// wait for the pipeline stage to complete.
static void waitStage(Stage* s)
{                         
    int st;
    waitpid(s->child, &st, 0);
        
    //store in stage child value - process id of the child - iterate through
    //each stage and call waitstage
}

/*
 * list:
 * 1.   Setup 'global' redirections.
 * 2.   Create all pipes. It is a fatal error if a pipe cannot be created.
 * 3.   spawn all processes, using spawnStage().
 * 4.   wait for processes to finish, using waitStage().
 *
 * The function always returns 1 for now.
 */
int setupCommandPipeline(Command * c)
{
    // i < c -- some stages 
    // TODO
    
    //redirection handling
    if (c->mode & R_INPUT)
        setStageInput(c->stages[0], open(c->input,O_RDONLY));
    else
        setStageInput(c->stages[0], STDIN_FILENO);

    if (c->mode & R_OUTPUT)
        setStageOutput(c->stages[c->num_stages-1], open(c->output, O_WRONLY|O_TRUNC|O_CREAT,0666)); //open for write
    else 
        setStageOutput(c->stages[0], STDOUT_FILENO);

    if (c->mode & R_APPEND)
            setStageOutput(c->stages[c->num_stages-1], open(c->output, O_WRONLY|O_APPEND|O_CREAT,0666)); //open for write
    else
        setStageOutput(c->stages[0], STDOUT_FILENO);
 
    //set otherr 2 
    //in forloop call pipe on

    for (int i=0; i < c->num_stages-1; i++){ //setup piping for num of stages
        int pipe1[2];
        if (pipe(pipe1) == -1){
            //error has occurred 
        }
        setStageOutput(c->stages[i], pipe1[1]);
        setStageInput(c->stages[i+1], pipe1[0]);
    }
    
    for (int i=0; i < c->num_stages; i++){ //spawn all stages
        spawnStage(c->stages[i]);
        
        //check if readonly or write only
   
    }
    for (int j=0; j < c->num_stages; j++){ //wait for processes to finish
        waitStage(c->stages[j]);
    }
    
    return 1;
}
