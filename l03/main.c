#include "libmin.h"
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char** argv) {
    if (argc == 1) {
        printf("There are not enough arguments\n");
        exit(1);
    }

    int32_t* numbers = malloc(sizeof(int32_t) * (argc - 1));
    for (size_t i = 0; i < argc-1; i++) {
        // TODO validation that the numbers are actually numbers
        // TODO strtol instead of atoi
        numbers[i] = atoi(argv[i+1]);
    }

    printf("Minimum is %d\n", min(numbers, argc-1));
    free(numbers);
}
