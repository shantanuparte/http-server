#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>

#define MY_PORT 6969
#define PENDING 23   //just my favriote number 

int get_listining_socket()
{

    struct addrinfo hints, *server_info;

    memset(&hints, 0, sizeof hints);

    hints.ai_family = AF_UNSPEC;     // doesn't care abot 4 or 6 ip
    hints.ai_socktype = SOCK_STREAM; // tcp
    hints.ai_flags = AI_PASSIVE;     // fill my ip automatically

    int status;
    if (status = getaddrinfo(NULL, MY_PORT, &hints, &server_info) != 0)//everything goes in the server_info
    {
        fprintf(stderr, "Error: ", gai_strerror(status));
        return -1;
    }

    if(server_info == NULL){
        printf("Getaddrinfo failed\n");
        return -1;
    }

    int sock_fd = socket(server_info->ai_family, server_info->ai_socktype, server_info->ai_protocol);

    bind(sock_fd, server_info->ai_addr, server_info->ai_addrlen);

    listen(sock_fd, PENDING);
    

}
