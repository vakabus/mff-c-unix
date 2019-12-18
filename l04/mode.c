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


int main(int argc, char **  argv) {
    if (argc != 3) errx(1, "You must provide a filename and mode!");

    char* filename = argv[1];
    char* mode_str = argv[2];

    long int mode = strtol(mode_str, NULL, 8);
    printf("mode=%lx\n", mode);

    umask(0);
    int32_t fd_dest = open(filename, O_CREAT | O_WRONLY, mode);
    if (fd_dest == -1) err(1, "create");
    close(fd_dest);

}
