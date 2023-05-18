#include "post.h"
#include "../../helpers/helpers.h"

#define BUFFER_SIZE 4096
#define DATA_SIZE 1024

void directory_check_post(char *data, char *post_data, char *directory, char *host, char *content_type) {
    if (directory == NULL) {
        sprintf(data, "POST / HTTP/1.1\r\nHost: %s\r\nUser-Agent: my-client\r\nContent-Length: %lu\r\nContent-Type: %s\r\nConnection: close\r\n\r\n%s", host, strlen(post_data), content_type, post_data);
    } else {
        sprintf(data, "POST %s HTTP/1.1\r\nHost: %s\r\nUser-Agent: my-client\r\nContent-Length: %lu\r\nContent-Type: %s\r\nConnection: close\r\n\r\n%s", directory, host, strlen(post_data), content_type, post_data);
    }
}

bool requests_post(int port, char *website, char *directory, char *post_data, char *content_type) {
    int fd;
    ssize_t n;
    char port_str[6];
    struct addrinfo hints, *res, *addr;
    struct sockaddr_in server;
    char i_host[INET6_ADDRSTRLEN];
    char data[DATA_SIZE], buffer[BUFFER_SIZE];

    sprintf(port_str, "%d", port);

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    int status = getaddrinfo(website, port_str, &hints, &res);
    if (status != 0) {
        fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(status));
        return false;
    }

    for (addr = res; addr != NULL; addr = addr->ai_next) {
        if (addr->ai_family == AF_INET) {
            struct sockaddr_in *i_addr = (struct sockaddr_in *)addr->ai_addr;
            inet_ntop(AF_INET, &i_addr->sin_addr, i_host, sizeof(i_host));
            break;
        }
    }

    if (addr == NULL) {
        fprintf(stderr, "Could not find a valid address to connect to\n");
        return false;
    }

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr(i_host);
    server.sin_port = htons(port);

    fd = socket(addr->ai_family, addr->ai_socktype, addr->ai_protocol);
    if (fd == -1) {
        perror("socket");
        freeaddrinfo(res);
        return false;
    }

    if (connect(fd, (struct sockaddr *)&server, sizeof(server)) == -1) {
        perror("connect");
        freeaddrinfo(res);
        close(fd);
        return false;
    }

    directory_check_post(data, post_data, directory, website, content_type);

    printf("Sending data:\n%s\n", data);

    n = send(fd, data, strlen(data), 0);
    if (n == -1) {
        perror("send");
        freeaddrinfo(res);
        close(fd);
        return false;
    }

    memset(buffer, 0, sizeof buffer);
    while ((n = recv(fd, buffer, sizeof buffer - 1, 0)) > 0) {
        buffer[n] = '\0';
        printf("Received data:\n%s\n", buffer);
        memset(buffer, 0, sizeof buffer);
    }

    if (n == -1) {
        perror("recv");
        freeaddrinfo(res);
        close(fd);
        return false;
    }

    freeaddrinfo(res);
    close(fd);

    return true;
}