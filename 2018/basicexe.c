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

// ================================================================================
// Write the basic command logic here.
// ================================================================================
int basicExecute(char* com,int mode,char* input,char* output,char** args)
{
    // TODO
    
    
    pid_t child = fork();
    if (child < 0)
        printf("Error");
    if (child == 0){        
        if (mode & R_INPUT){
            int a = open(input, O_RDONLY);
            dup2(a, 0);
        }

        if (mode & R_OUTPUT){
            int b = open(output, O_WRONLY|O_TRUNC|O_CREAT,0666); //open for write
            dup2(b, 1);
        }
    
        if (mode & R_APPEND){
            int c = open(output,O_WRONLY|O_APPEND|O_CREAT,0666); //Open for append
            dup2(c, 1);
        }
        execvp(com, args); //executing the child (last thing that should be done)
    }
    else
        wait(NULL);
    return 1;
}
