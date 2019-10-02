#include <stdio.h>

int main(int argc, char ** argv) {
    int i = 1;
    char* iptr = (char*) &i;
    if (*iptr = '\0') {
        printf("big endian\n");
    } else {
        printf("little endian\n");
    }
}
