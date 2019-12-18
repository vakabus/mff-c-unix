#include<stdio.h>
#include<stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdint.h>
#include <stdbool.h>
#include <err.h>

void parent(pid_t child) {
    printf("Waiting for my child to die...\n");
    while (true) {
        int status;
        pid_t pid = waitpid(child, &status, WUNTRACED | WCONTINUED);
        if (pid == -1) err(1, "wait");

        if (WIFSIGNALED(status)) {
            printf("Killed by signal %d\n", WTERMSIG(status));
            exit(0);
        } else if (WIFSTOPPED(status)) {
            printf("Child stopped by signal %d\n", WSTOPSIG(status));
        } else if (WIFCONTINUED(status)) {
            printf("Child was resumed...\n");
        } else {
            printf("something else has happened...\n");
        }

    }
}

void child() {
    sleep(3600);
    printf("Child terminating...\n");
}

int main() {
    printf("Starting the process - main PID is %d\n", getpid());

    pid_t chld = fork();
    switch(chld) {
        case 0:
            printf("Running in child... My PID is %d\n", getpid());
            child();
            break;
        case -1:
            err(1, "fork");
        default:
            printf("Running in parent...\n");
            parent(chld);
            break;
    } 
}
