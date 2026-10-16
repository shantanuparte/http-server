#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define MY_PORT "6969"
#define PENDING 23 // just my favriote number


void con_bint_str_ip(struct addrinfo *s, char *res){

    struct sockaddr_in *ipv4;
    struct sockaddr_in6 *ipv6;
    void *addr;

    if (s->ai_family == AF_INET)
    {
        ipv4 = (struct sockaddr_in*)s->ai_addr;
        addr = &(ipv4->sin_addr);
        
    }else{
        ipv6 = (struct sockaddr_in6*)s->ai_addr;
        addr = &(ipv6->sin6_addr);
    }
    
    inet_ntop(s->ai_family, addr, res, INET6_ADDRSTRLEN);

}

int get_listining_socket()
{

    struct addrinfo hints, *server_info;

    memset(&hints, 0, sizeof hints);

    hints.ai_family = AF_UNSPEC;     // doesn't care abot 4 or 6 ip
    hints.ai_socktype = SOCK_STREAM; // tcp
    hints.ai_flags = AI_PASSIVE;     // fill my ip automatically

    int status;
    if ((status = getaddrinfo(NULL, MY_PORT, &hints, &server_info)) != 0) // everything goes in the server_info
    {
        fprintf(stderr, "Error: %s", gai_strerror(status));
        return -1;
    }

    if (server_info == NULL)
    {
        printf("Getaddrinfo failed\n");
        return -1;
    }

    int sock_fd;

    if ((sock_fd = socket(server_info->ai_family, server_info->ai_socktype, server_info->ai_protocol)) == -1)
    {
        printf("Error in socket function\n");
        return -1;
    }
    

    if (bind(sock_fd, server_info->ai_addr, server_info->ai_addrlen) != 0)
    {
        printf("Error in binding\n");
        return -1;
    }

    if (listen(sock_fd, PENDING) != 0)
    {
        printf("Error in listen\n");
        return -1;
    }

    

    char ipstr[INET6_ADDRSTRLEN];
    con_bint_str_ip(server_info, ipstr);

    printf("Server running on %s : %s\n",ipstr,MY_PORT);
    
    freeaddrinfo(server_info);

    return sock_fd;
}
