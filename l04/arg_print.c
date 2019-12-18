#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <stdbool.h>
#include <stdint.h>
#include <unistd.h>
#include <err.h>

extern char *optarg;
extern int optind, opterr, optopt;

int main(int argc, char **  argv) {
    int32_t res;
    while ((res = getopt(argc, argv, "abF:")) != -1) {
        switch (res) {
            case '?': {
                errx(1, "Unknown option %s", argv[optind - 1]);
            }
            case 'a': {
                printf("option a\n");
                break;
            }
            case 'b': {
                printf("option b\n");
                break;
            }
            case 'F': {
                printf("option F (file \"%s\")\n", optarg);
                break;
            }
        }
    }
}
