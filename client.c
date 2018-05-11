#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/select.h>
#include <assert.h>


void checkError(int status,int line)
{
    if (status < 0) {
        printf("socket error(%d)-%d: [%s]\n",getpid(),line,strerror(errno));
        exit(-1);
    }
}

int main(int argc,char* argv[]) 
{
    int sid = socket(PF_INET,SOCK_STREAM,0); //create socket
    struct sockaddr_in srv;//initialize socket stucture from server
    struct hostent *server = gethostbyname(argv[1]); //set up to localhost
    if (server==NULL) { //check server was found
        printf("Couldn't find a host named: %s\n",argv[1]);
        return 2;
    }
    srv.sin_family = AF_INET;//AF_INET refers to the IP addresses from the internet
    srv.sin_port   = htons(8025); //port number 
    memcpy(&srv.sin_addr,server->h_addr_list[0],server->h_length);
    int status = connect(sid,(struct sockaddr*)&srv,sizeof(srv)); //connect  
    checkError(status,__LINE__);

    fd_set afd; //create fd set
    char ch;
    int done = 0;   
    
    do {
        FD_ZERO(&afd);      // clear all bytes in fd sets
        FD_SET(0,&afd);     // set stdin
        FD_SET(sid,&afd);   // set socket
        int nbReady = select(sid+1,&afd,NULL,NULL,NULL); //num bytes ready
        //if bytes are ready
        if (nbReady > 0) {
            if (FD_ISSET(0,&afd)) { // if there are data in stdin
                int rc = read(0,&ch,1); //read in command
                assert(rc >= 0);
                int nbSent = write(sid, &ch, 1); //write out command to server
            }
            else if (FD_ISSET(sid,&afd)) { // if there are data in stdout
                int rc = read(sid,&ch,1);
                assert(rc >= 0);
                int nbSent = write(1, &ch, 1);
            }
        else{ 
            done = 1;
            }
        }
   } while(!done);
   return 0;
}

