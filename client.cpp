#include <string.h>
#include <winsock.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>


const int SERVER_PORT=3333; // listen port
const int MAXDATASIZE=1000;


int main(int argc, char* argv[])
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
    int recvbytes;
    char buf[MAXDATASIZE]={0};
    struct hostent *host;
    struct sockaddr_in serv_addr;

    if(argc<2) {
        //printf("enter server name\n");
        //exit(1);
    }

    if((host=gethostbyname(argv[1]))=NULL) {
        printf("gethostname failed\n");
        exit(1);
    }

    if( (sockfd=socket(AF_INET, SOCK_STREAM, 0)) == -1 ) { // TCP socket
        printf("create socket failed\n");
        exit(1);
    }

    serv_addr.sin_family=AF_INET;
    serv_addr.sin_port=htons(SERVER_PORT);
    serv_addr.sin_addr.s_addr=inet_addr("124.16.97.37");
    memset(&(serv_addr.sin_zero),0,8);

    if(connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(struct sockaddr))==-1) {
        printf("connect failed\n");
        exit(1);
    }

    if((recvbytes=recv(sockfd,buf,MAXDATASIZE,0))==-1) {
        printf("recv failed\n");
        exit(1);
    }

    buf[recvbytes]='\0';
    printf("recv: %s\n",buf);
    closesocket(sockfd);

    system("pause");

    return 0;
}

