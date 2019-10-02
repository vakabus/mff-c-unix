#include <stdio.h>
#include <stdbool.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>


int main() {
    char* buff[2];
    buff[0] = NULL;
    buff[1] = NULL;

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

        // vymena bufferu
        current = !current;
    }

    free(buff[0]);
    free(buff[1]);
    
}
