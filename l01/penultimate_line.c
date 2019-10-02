#include <stdio.h>
#include <stdbool.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>


int main(int argc, char ** argv) {
    char* buff[2];
    buff[0] = NULL;
    buff[1] = NULL;
    size_t sizes[2];
    sizes[0] = 0;
    sizes[1] = 0;

    bool current = true;

    while (true) {

        char* tmpbuff = NULL;
        size_t tmpsize = 0;
        
        ssize_t read = getline(&tmpbuff, &tmpsize, stdin);
        if (read == -1) {
            // zkousim tisknout predchozi
            printf("%s", buff[current]);
            free(tmpbuff);
            break;
        }

        free(buff[current]);
        buff[current] = tmpbuff;
        sizes[current] = tmpsize;

        // vymena bufferu
        current = !current;
    }

    free(buff[0]);
    free(buff[1]);
    
}
