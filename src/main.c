#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include "network.h"

int main()
{
    printf("Weloce to http server\n\n");

    int server_fd = get_listining_socket();

    if (server_fd == -1)
        return 1;

    fflush(stdout);

    getchar();  

    
    
    return 0;
}


