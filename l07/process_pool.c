#include<stdio.h>
#include<stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdint.h>
#include <stdbool.h>
#include <err.h>
#include <sys/random.h>

typedef struct job {
    void (*func)(void*);
    void* argument;
} job_t;

typedef struct pp {
    uint32_t workers_wanted;
    job_t job;
} pp_t;

void sleep_worker(void* junk) {
    while (true) {
        uint8_t byte;
        getrandom(&byte, 1, GRND_NONBLOCK);
        sleep(1);
        if (byte < 16) break;    
    }
    printf("Child timed out...\n");
}

void spawn_new_worker(uint32_t* workers, job_t job) {
    pid_t chld = fork();
    switch(chld) {
        case 0:
            printf("New worker with PID=%d\n", getpid());
            job.func(job.argument);
            exit(0);
        case -1:
            err(1, "fork");
        default:
            (*workers)++;
            break;
    } 
}

void send_my_pid_to_pipe(char * namedpipename) {
    int pipe_fd = open(namedpipename, O_WRONLY);
    if (pipe_fd == -1) err(1, "open pipe");
    dprintf(pipe_fd, "%d\n", getpid());
    close(pipe_fd);
}

void await_worker_change(uint32_t* workers) {
    int status;
    pid_t pid = wait(&status);
    if (pid == -1) err(1, "wait");

    if (WIFSIGNALED(status) || WIFEXITED(status)) {
        printf("Worker with PID=%d terminated...\n", pid);
        (*workers)--;
    } else {
        printf("something else has happened to PID=%d...\n", pid);
    }
}

void process_manager(pp_t* pp) {
    uint32_t workers = 0;
    printf("entering ethernal management loop\n");
    while (true) {
        if (workers < pp->workers_wanted) {
            spawn_new_worker(&workers, pp->job);
        } else {
            await_worker_change(&workers);
        }
    }
}

int main(int argc, char ** argv) {
    if (argc != 2) errx(1, "need one argument with fifo name");

    printf("Starting the pool controller with PID=%d\n", getpid());
    printf("Connecting to debug pipe...\n");
    send_my_pid_to_pipe(argv[1]);

    pp_t* sleep_pp = malloc(sizeof(pp_t));
    sleep_pp->workers_wanted = 4;
    sleep_pp->job.func = &sleep_worker;
    sleep_pp->job.argument = NULL;

    pp_t* pm = malloc(sizeof(pp_t));
    pm->workers_wanted = 4;
    pm->job.func = &process_manager;
    pm->job.argument = sleep_pp;

    pp_t* pt = malloc(sizeof(pp_t));
    pt->workers_wanted = 2;
    pt->job.func = &process_manager;
    pt->job.argument = pm;

    process_manager(pt);

    free(sleep_pp);
    free(pm);
    free(pt);
}
