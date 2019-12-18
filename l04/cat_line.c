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


        // check for newline in buff
        uint32_t start = 0;
        uint32_t end = size;
        while (true) {
            bool newline_present = false;
            for (uint32_t i = start; i < size; i++) {
                if (buff[i] == '\n') { newline_present = true; end = i + 1; break; }
            }

            if (!newline_present) {
                write(STDOUT_FILENO, buff+start, size-start);
                break;
            } else {
                write(STDOUT_FILENO, buff+start, end - start);
                start = end;
                sleep(1);            
            }
        }
    }
}
