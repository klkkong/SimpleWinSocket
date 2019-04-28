#include <string.h>
#include <winsock.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>


const int SERVER_PORT=3333; // listen port
const int BACKLOG=10; // max requiry

int main()
{
    // windows add
    WORD wVersionRequested;
    WSADATA wsaData;
    int err;
    wVersionRequested = MAKEWORD(1, 1);
    err = WSAStartup(wVersionRequested, &wsaData);
    if(err != 0)
    {
        perror("WSAStartup error");
    }
    // add done

    int sockfd;
    int client_fd;
    int sin_size=0;

    struct sockaddr_in my_addr; // host info
    struct sockaddr_in remote_addr; // client info

    char* msg="You are welcome\n";

    if( (sockfd=socket(AF_INET, SOCK_STREAM, 0)) == -1 ) { // TCP socket
        printf("create socket failed\n");
        exit(1);
    }

    my_addr.sin_family=AF_INET;
    my_addr.sin_port=htons(SERVER_PORT);
    my_addr.sin_addr.s_addr=INADDR_ANY;
    memset(&(my_addr.sin_zero),0,8);

    if(bind(sockfd, (struct sockaddr *)&my_addr, sizeof(struct sockaddr))==-1) {
        printf("bind failed\n");
        exit(1);
    }

    if(listen(sockfd,BACKLOG)==-1) {
        printf("listen failed\n");
        exit(1);
    }

    while(1) {
        sin_size=sizeof(struct sockaddr_in);
        if((client_fd=accept(sockfd,(struct sockaddr *)&remote_addr, &sin_size))==-1) {
            printf("accept failed\n");
            continue;
        }
        if(send(client_fd,msg,strlen(msg),0)==-1) {
            printf("send failed\n");
            //close(client_fd);
            closesocket(client_fd);
            exit(0);
        }
        closesocket(client_fd);
    }

    return 0;
}
