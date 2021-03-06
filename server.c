#include <stdio.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <string.h>
#include <stdbool.h>
#include <netinet/tcp.h>
#include <assert.h>

int main(void) {
    // server
    int port = 15440;
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);  // TCP/IP socket
    struct sockaddr_in srv, cli;
    memset(&srv, 0, sizeof(srv));             // clear it first
    srv.sin_family = AF_INET;                 // IP family
    srv.sin_addr.s_addr = htonl(INADDR_ANY);  // don't care IP address
    srv.sin_port = htons(port);               // server port
    int rv = bind(sockfd, (struct sockaddr *)&srv, sizeof(struct sockaddr));
    if (rv < 0) {
        perror("bind");
        return 1;
    }

    int flag = 1;
    setsockopt(sockfd, IPPROTO_TCP, TCP_NODELAY, (char *)&flag, sizeof(int));

    rv = listen(sockfd, 5);
    if (rv < 0) {
        perror("listen");
        return 1;
    }
    while (1) {
        printf("%s: accepting\n", __FILE__);

        int sa_size = sizeof(struct sockaddr_in);
        int sessfd = accept(sockfd, (struct sockaddr *)&cli, &sa_size);
        while (1) {
            char buf[100];
            rv = recv(sessfd, buf, sizeof(buf), 0);
            if (rv <= 0) {
                printf("%s: bad recv(), restarting\n", __FILE__);
                break;
            } else {
                buf[rv] = '\0';
            }
            printf("%s: received msg = \"%s\", n = %d\n", __FILE__, buf, rv);
        }
    }
}
