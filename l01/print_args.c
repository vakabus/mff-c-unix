#include <stdio.h>

int main(int argc, char ** argv) {
    for (int i = 0; i < argc; i++) {
        printf("%s", argv[i]);
        if (i != argc-1) {
            printf(" ");
        } else {
            printf("\n");
        }
            
    }
}
