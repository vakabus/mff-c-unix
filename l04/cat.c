#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <getopt.h>
#include <stdbool.h>
#include <stdint.h>
#include <unistd.h>
#include <err.h>

extern char *optarg;
extern int optind, opterr, optopt;

int main(int argc, char **  argv) {
    if (argc != 2) errx(1, "You must provide a file to print out!");

    int32_t fd = open(argv[1], O_RDONLY);
    if (fd == -1) err(1, "Opening file %s failed.", argv[1]);

    while (true) {
        uint8_t buff[129];
        buff[128] = 0;
        ssize_t size = read(fd, buff, 128);
        if (size == -1) err(1, "read");
        if (size == 0) break;

        write(STDOUT_FILENO, buff, size);
    }
}
