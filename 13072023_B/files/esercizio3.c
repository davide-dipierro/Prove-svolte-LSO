#include "unistd.h"
#include "stdlib.h"
#include "stdio.h"
#include "signal.h"
#include "stdbool.h"

void signal_handler(int s){
    printf("Svegliato un %s\n", (getpid()%2) ? "dispari" : "pari");
}

int main(int argc, char** argv){

    int N = atoi(argv[1]);
    int* pids = (int*)malloc(N*sizeof(int));

    for(int i=0; i<N; i++){
        pids[i] = fork();
        if(pids[i]==0){
            signal(SIGUSR1, signal_handler);
            pause();
            execlp("ls", "ls", NULL);
            exit(0);
        }
    }

    bool dispari = (getppid()%2) ? true : false; 
    for(int i=0; i<N; i++){
        if(dispari){
            if(i%2) kill(pids[i], SIGUSR1);
            else kill(pids[i], SIGKILL);
        } else {
            if(i%2) kill(pids[i], SIGKILL);
            else kill(pids[i], SIGUSR1);
        }
    }

    sleep(1);
    return 0;
}