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
#include <ctype.h>

extern char *optarg;
extern int optind, opterr, optopt;

typedef struct args {
    bool case_insensitive;
    char* filename;
} args;

args new_args() {
    args a;
    a.case_insensitive = false;
    a.filename = NULL;
    return a;
}

args get_options(int argc, char ** argv) {
    args res = new_args();
    int32_t optres;
    while ((optres = getopt(argc, argv, "i")) != -1) {
        switch (optres) {
            case '?': {
                errx(1, "Unknown option %s", argv[optind - 1]);
            }
            case 'i': {
                res.case_insensitive = true;
                break;
            }
        }
    }

    res.filename = argv[optind];

    return res;
}

size_t get_file_size(int32_t fd) {
    off_t off = lseek(fd, 0, SEEK_END);
    if (off == -1) err(1, "error detecting size using seek");

    return (size_t) off;
}

uint8_t read_byte(int32_t fd, off_t offset, bool from_beggining) {
    off_t noff = lseek(fd, from_beggining ? offset : -offset-1, from_beggining ? SEEK_SET : SEEK_END);
    if (noff == -1) err(1, "Error seeking file");

    uint8_t res = 0;
    ssize_t r = read(fd, &res, 1);
    if (r == -1) err(1, "read");
    if (r != 1) errx(1, "read read something wrong");
    return res;
}

int main(int argc, char **  argv) {
    args args = get_options(argc, argv);

    if (args.filename == NULL) errx(1, "You must provide a file to check!");

    int32_t fd = open(args.filename, O_RDONLY);
    if (fd == -1) err(1, "Opening file '%s' failed", args.filename);

    size_t file_size = get_file_size(fd);
    for (size_t o = 0; o < (file_size / 2) + 1; o++) {
        int32_t b = read_byte(fd, o, true);
        int32_t e = read_byte(fd, o, false);

        if (args.case_insensitive) {
            b = tolower(b);
            e = tolower(e);
        }

        if (e != b) {
            fprintf(stderr, "File is not palindromatic\n");
            close(fd);
            return 1;
        }
    }

    close(fd);
    return 0;
}
