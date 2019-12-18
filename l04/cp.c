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
    if (argc != 3) errx(1, "You must provide a input file and output file!");

    int32_t fd_source = open(argv[1], O_RDONLY);
    if (fd_source == -1) err(1, "Opening source %s failed.", argv[1]);

    int32_t fd_dest = open(argv[2], O_WRONLY | O_CREAT, 0666);
    if (fd_dest == -1) err(1, "Opening dest %s failed.", argv[2]);

    while (true) {
        uint8_t buff[128];
        ssize_t size = read(fd_source, buff, 128);
        if (size == -1) err(1, "read");
        if (size == 0) break;  // eof

        ssize_t written_size = write(fd_dest, buff, size);
        if (written_size != size) errx(1, "failed to write everything");
    }

    close(fd_dest);
    close(fd_source);
}
