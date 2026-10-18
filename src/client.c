
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <stdlib.h>

#include "client.h"

void handle_client(int client_fd)
{
    char request[1024];

    // Read the request
    int bytes = recv(client_fd, request, sizeof(request) - 1, 0);

    if (bytes <= 0)
        return;
    
    request[bytes] = '\0';

    printf("Request received:\n%s\n", request);

    if (strncmp(request, "GET / ", 6) != 0 &&
        strncmp(request, "GET /index.html ", 16) != 0)
    {
        char response[] =
            "HTTP/1.1 404 Not Found\r\n"
            "Content-Type: text/html\r\n"
            "Connection: close\r\n"
            "\r\n"
            "<h1>404 - Page not found</h1>";

        send(client_fd, response, strlen(response), 0);
        return;
    }

    FILE *file = fopen("../index.html", "r");

    if (file == NULL)
    {
        char response[] =
            "HTTP/1.1 500 Internal Server Error\r\n"
            "Content-Type: text/html\r\n"
            "Connection: close\r\n"
            "\r\n"
            "<h1>Could not open index.html</h1>";

        send(client_fd, response, strlen(response), 0);
        return;
    }

    char page[4096];

    size_t size = fread(page, 1, sizeof(page), file);
    fclose(file);

 
    char header[256];

    int header_size = snprintf(
        header,
        sizeof(header),
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: text/html\r\n"
        "Content-Length: %zu\r\n"
        "Connection: close\r\n"
        "\r\n",
        size);

    send(client_fd, header, header_size, 0);


    send(client_fd, page, size, 0);
}





