#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <err.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdbool.h>

static void handler(int dummy) {
    printf("[%d] received %d\n", getpid(), dummy);
}


void run(int count) {
    pid_t parent_pid = getppid();
    pid_t child_pid = fork();
    if (child_pid == -1) err(1, "fork");
    if (child_pid == 0) {
        if (count == 0) {
            sleep(1);
            printf("Killing\n");
            kill(parent_pid, SIGTERM);
            kill(getpid(), SIGTERM);
            printf("I am dead\n");
            exit(2);
        } else {
            run(count - 1);
        }
        return;
    } else {
        // parent
        sigset_t set;
        sigemptyset(&set);
        sigaddset(&set, SIGTERM);
        int signal;
        printf("pre sigwait\n");
        //pid_t res = wait(&signal);
        //int res = sigsuspend(&set);




        int res = sigwait(&set, &res);
        if (res != 0) err(1, "sigwait");

        printf("post sigwait, killing %d, mypid %d\n", parent_pid, getpid());

        printf("Received signal %d\n", signal);
        kill(parent_pid, SIGTERM);
        kill(getpid(), SIGTERM);
        printf("I am dead too.\n");
        exit(1);
    }
}


int main(int argc, char ** argv) {

    struct sigaction psa;
    psa.sa_handler = handler;
    psa.sa_flags = SA_RESTART;
    sigaction(SIGTERM, &psa, NULL);


    run(5);
    
}
