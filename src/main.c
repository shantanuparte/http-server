
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <errno.h>

#include "network.h"
#include "client.h"
#include "sig.h"

int main(void)
{
    printf("Welcome to the http server\n\n");

    if (set_sig_handler() == -1)
    {
        perror("sigaction");
        
        return 1;
    }

    int server_fd = get_listining_socket();

    if (server_fd == -1)
        return 1;

    while (1)
    {
        int client_fd = accept(server_fd, NULL, NULL);

        if (client_fd == -1)
        {
            if (errno == EINTR)
                continue;

            perror("accept");
            continue;
        }

        pid_t pid = fork();

        if (pid == -1)
        {
            perror("fork");
            close(client_fd);
            continue;
        }

        if (pid == 0)
        {
            close(server_fd);

            handle_client(client_fd);

            close(client_fd);
            _exit(0);
        }

        close(client_fd);
    }

    close(server_fd);
    return 0;
}
