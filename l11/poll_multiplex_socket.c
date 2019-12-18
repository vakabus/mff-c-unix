#include <stdio.h>
#include <stdlib.h>
#include <poll.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdint.h>
#include <err.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

typedef void (*handler_fn)();

int socketfd;

void stdin_handler() {
    uint8_t buff[32];
    int res = read(STDIN_FILENO, buff, 32);
    if (res < 0) err(1, "read");
    res = write(STDOUT_FILENO, buff, res);
    if (res < 0) err(1, "write");
}

void socket_handler() {
    int s;
    if ((s = accept(socketfd, NULL, 0)) == -1)
			err(1, "accept");

    shutdown(s, SHUT_RDWR); 
    close(s);

    printf("socket handler\n");
}

void main() {
    int optval = 1;
    struct pollfd fds[2];
    handler_fn handlers[2];

    fds[0].fd = STDIN_FILENO;
    fds[0].events = POLLIN; // this is important and it's the only thing that works for non-streams
    fds[0].revents = 0;
    handlers[0] = stdin_handler;

    socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if (socketfd == -1) err(1, "socket");

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
	addr.sin_port = htons(5555);
	addr.sin_addr.s_addr = htonl(INADDR_ANY);

    /* So that we can use the port immediately again after restart. */
	if (setsockopt(socketfd, SOL_SOCKET, SO_REUSEADDR,
	    &optval, sizeof (optval)) == -1) {
		err(1, "setsockopt");
	}

    if (bind(socketfd, (struct sockaddr *)&addr, sizeof (addr)) == -1)
		err(1, "bind");

    if (listen(socketfd, 100) == -1)
		err(1, "listen");
    
    fds[1].fd = socketfd;
    fds[1].events = POLLIN;
    fds[1].revents = 0;
    handlers[1] = socket_handler;


    int res;
    while ((res = poll(fds, 2, 10000)) != -1) {
        if (res == 0) {
            printf("    timeout\n");
            continue;
        }

        for (int i = 0; i < 2; i++) {
            if (fds[i].revents != 0)
                handlers[i]();
            fds[i].revents = 0;
        }
    }
    err(1, "poll");
}
