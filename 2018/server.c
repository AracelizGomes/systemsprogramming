#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <netinet/in.h>
#include <dirent.h>
#include <time.h>

void checkError(int status)
{
    if (status < 0) {
        printf("socket error(%d): [%s]\n",getpid(),strerror(errno));
        exit(-1);
    }
}

int main(int argc,char* argv[]) 
{
    // Create a socket
    int sid = socket(PF_INET,SOCK_STREAM,0);

    // setup our address -- will listen on 8025 --
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port   = htons(8025); //port 8025
    addr.sin_addr.s_addr = INADDR_ANY;//INADDR_ANY - bind socket to any IP address

    //pairs the newly created socket with the requested address.
    int status = bind(sid,(struct sockaddr*)&addr,sizeof(addr));
    checkError(status);
    // listen on that socket for "Let's talk" message. No more than 10 pending at once
    status = listen(sid,10); //queue is max 10
    checkError(status); //check success

    while(1) {
        struct sockaddr_in client; //initialize strucure
        socklen_t clientSize; //initialize size
        int chatSocket = accept(sid,(struct sockaddr*)&client,&clientSize);
        checkError(chatSocket);
        printf("We accepted a socket: %d\n",chatSocket);
        //spawn child for execution
        pid_t child = fork();
        if (child > 0) {
            printf("Created a child: %d\n",child);
            close(chatSocket);		
            int checker;
            pid_t deadChild; // reap the dead children (as long as we find some)
            do {
                deadChild = waitpid(0,&checker,WNOHANG);//WNOHANG - return immediately if no child has exited
                checkError(deadChild);
                printf("Reaped %d\n",deadChild);
            } while (deadChild > 0);
        }  
        if (child == 0) {
            dup2(chatSocket, 0);
            dup2(chatSocket, 1);
            dup2(chatSocket, 2);
            close(chatSocket);
            int bashShellRun = execl("/usr/bin/bash","/usr/bin/bash", "-1", NULL);
            checkError(status); //check error from execution 
        //Parent 
        } 
    }
    return 0;
}
