
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include "network.h"

#define buff_SIZE 1024

int main(void)
{
    printf("Welcome to the TCP echo server!\n\n");

    int server_fd = get_listining_socket();

    if (server_fd == -1)
        return 1;

    int client_fd = accept(server_fd, NULL, NULL);

    if (client_fd == -1)
    {
        perror("accept");
        close(server_fd);
        return 1;
    }

    printf("Client connected!\n");

    char buff[buff_SIZE];

    while (1)
    {
        ssize_t byte_recv = recv(client_fd, buff, sizeof(buff), 0);

        if (byte_recv == 0)
        {
            printf("Client disconected.\n");
            break;
        }

        if (byte_recv == -1)
        {
            perror("recv");
            break;
        }

        ssize_t total_sent = 0;

        while (total_sent < byte_recv)
        {
            ssize_t bytes_sent = send(
                client_fd,
                buff + total_sent,
                (size_t)(byte_recv - total_sent),
                0);

            if (bytes_sent <= 0)
            {
                perror("send");
                goto cleanup;
            }

            total_sent += bytes_sent;
        }
    }

cleanup:
    close(client_fd);
    close(server_fd);

    return 0;
}
