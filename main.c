#include <stdio.h>
#include <stdlib.h>

#include <winsock2.h>
#include <windows.h>
#include <io.h>


void main(int argc, char *argv[])
{
    int bufsize;

    long ii, status;

    struct sockaddr addr;

    SOCKET sockfd,
           dupfd;

    WSADATA wsaData;

    bufsize = sizeof(addr);

    status = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (status != 0)
    {
        fprintf(stderr, "WSAStartup: %d\n", WSAGetLastError( ));
        exit(1);
    }

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (! sockfd)
    {
        fprintf(stderr, "socket: %d\n", WSAGetLastError( ));
        exit(1);
    }

    ii = 0;

    while (1)
    {
        status = DuplicateHandle(GetCurrentProcess( ), (HANDLE) sockfd, 
                                 GetCurrentProcess( ), (HANDLE) &dupfd, 
                                 0, FALSE, 0);
        if (status == 0)
        {
            fprintf(stderr, "DuplicateHandle: %d\n", WSAGetLastError( ));
            exit(1);
        }
   
        printf("%06d  Orig FD: %d  Dupd FD: %d\n", ii++, sockfd, dupfd);
    }

    exit(0);
}
