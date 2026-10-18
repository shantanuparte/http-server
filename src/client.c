
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <errno.h>

#include "client.h"

#define BUFF_SIZE 1024

void handle_client(int client_fd)
{
    char buff[BUFF_SIZE];

    while (1)
    {
        ssize_t byte_recv = recv(
            client_fd,
            buff,
            sizeof(buff),
            0
        );

        if (byte_recv == 0)
        {
            printf("Client disconnected.\n");
            break;
        }

        if (byte_recv == -1)
        {
            if (errno == EINTR)
                continue;

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
                0
            );

            if (bytes_sent == -1 && errno == EINTR)
                continue;

            if (bytes_sent <= 0)
            {
                perror("send");
                return;
            }

            total_sent += bytes_sent;
        }
    }
}
