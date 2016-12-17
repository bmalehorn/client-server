#define _GNU_SOURCE

#include <stdio.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <string.h>
#include <netinet/tcp.h>
#include <assert.h>
#include <unistd.h>
#include <arpa/inet.h>

int main(void) {
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in srv;
    memset(&srv, 0, sizeof(srv));                  // clear it first
    srv.sin_family = AF_INET;                      // IP family
    srv.sin_addr.s_addr = inet_addr("127.0.0.1");  // IP address of server
    srv.sin_port = htons(15440);                   // server port
    int rv = connect(sockfd, (struct sockaddr *)&srv, sizeof(struct sockaddr));
    if (rv < 0) {
        perror("connect");
        return 1;
    }
    int flag = 1;
    setsockopt(sockfd, IPPROTO_TCP, TCP_NODELAY, (char *)&flag, sizeof(int));

    while (1) {
        char *msg = "hello";
        int n = strlen(msg);
        printf("%s: sending msg = \"%s\", n = %d\n", __FILE__, msg, n);
        rv = send(sockfd, msg, n, 0);
        if (rv <= 0) {
            perror("send");
            return 1;
        }
        sleep(1);
    }
}
