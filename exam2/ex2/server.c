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

/* Same as the socket_send function in mail client solution */
int socket_send(int sid, char *message)
{
    int sent = 0;
    int length = strlen(message);
    int rem = length;

    while (sent < length) {
        int nbSent = write(sid, message+sent, rem);
        sent += nbSent;
        rem -= nbSent;
    }

    return sent;
}

/*
 * Read a line from socket. 
 * The line from the socket must end with '\n'.
 *
 * Parameters:
 *      sid:    socket ID
 *      p:      buffer to save the line
 *      size:   The size of the buffer
 * 
 * return value: 
 *    If read() or recv() fails, return -1.
 *    Otherwise, return the length of string in the buffer (including '\n').
 *
 * Important: 
 *
 * If the return value is not -1, 
 * the string in the buffer (pointed to by p) always has an NULL ('\0') at the end. 
 * If the line from the socket is long, place the first (size - 1) characters in the buffer.
 * If the last character is not '\n', the caller knows the line is too long.
 *
 * For example, suppose size is 32. 
 * the length of the line from the socket is 100 (including '\n').
 * Only first 31 character in the line is saved in the buffer, along with the NULL. 
 * The return value is 31. 
 *
 */
int  socket_read(int sid, char *p, int size)
{
    int len = 0;
    int mess = -1;
    p = malloc(size);

    //size = 30
    //p is buffer
    
    // TODO  
    while(!strstr(p, "\n")){
        mess = recv(sid, p, size, 0);
        if (mess ==0){
            printf("recv failed");
            break;
        }
        int tot;
        tot = len+mess;
        
        if (mess<tot){
            char * v = realloc(p, 2*(size));
            if(v){
                p = v;
                size = 2*size;
            }
            else{
                printf("realloc failed");
                break;
            }

            len+=mess;
            size-=mess;
        }   
    }


    p[len] = '\0';
    return len;
}

int main(int argc,char* argv[]) 
{
    // Create a socket
    int sid = socket(PF_INET,SOCK_STREAM,0);
    // setup our address -- will listen on 8025 --
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port   = htons(8025);
    addr.sin_addr.s_addr = INADDR_ANY;
    //pairs the newly created socket with the requested address.
    int status = bind(sid,(struct sockaddr*)&addr,sizeof(addr));
    checkError(status);
    // listen on that socket for "Let's talk" message. No more than 10 pending at once
    status = listen(sid,10);
    checkError(status);

    // The typical while loop in a server.
    // You can revise the loop from an example or your pevious work.
    // It is fine to print out some messages, as in examples.
    // TODO

    while(1) {
        struct sockaddr_in client;
        socklen_t clientSize;
        int chatSocket = accept(sid,(struct sockaddr*)&client,&clientSize);
        checkError(chatSocket);
        printf("Socket %d was accepted \n",chatSocket);
        //spawn child
        pid_t child = fork();
        if (child == 0) { //parent
            close(chatSocket);
            return -1; /* Report that I died voluntarily */
        } else if (child > 0) {
            printf("Created a child: %d\n",child);
            close(chatSocket);		
            int status = 0;
            pid_t deadChild; // reap the dead children (as long as we find some)
            do {
                deadChild = waitpid(0,&status,WNOHANG);
                checkError(deadChild);
                if (deadChild > 0)
                    printf("Reaped %d\n",deadChild);
            } while (deadChild > 0); 
        } 
    }
    return 0;
}
