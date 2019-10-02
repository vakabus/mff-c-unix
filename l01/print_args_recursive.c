#include <stdio.h>


int main(int argc, char** argv) {
    if (argc > 1) {
        printf("%s ", *argv);
        main(argc-1, argv+1);
    } else if (argc == 1) {
        printf("%s\n", *argv);
    }
}
