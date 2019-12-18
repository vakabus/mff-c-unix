#include <stdio.h>
#include <stdlib.h>
#include <poll.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdint.h>
#include <err.h>

void main() {
    struct pollfd fds[1];
    fds[0].fd = STDIN_FILENO;
    fds[0].events = POLLIN; // this is important
    fds[0].revents = 0;

    while (true) {
        int res = poll(fds, 1, 10000);
        if (res == -1) err(1, "poll");
        if (res == 0) { printf("   timeout\n"); continue; };

        uint8_t buff[32];
        res = read(STDIN_FILENO, buff, 32);
        if (res < 0) err(1, "read");
        res = write(STDOUT_FILENO, buff, res);
        if (res < 0) err(1, "write");
    }
}
