#include "stdio.h"
#include "unistd.h"
#include "signal.h"
#include "stdlib.h"
#include "sys/wait.h"

void signal_handler(int signal){
    printf("Padre: Ricevuto segnale da figlio con pid dispari.\n");
}

int main(int argc, char** argv){

    int N = atoi(argv[1]);
    
    signal(SIGUSR1, signal_handler);

    for(int i=0; i<N; i++){
        printf("Nascita figlio %d-esimo.\n", i);
        int pid = fork();
        if(pid==0){
            if(getpid()%2==0){
                execlp("ls", "ls", NULL);
                printf("Errore nell'esecuzione del comando.\n");
                exit(1);
            }else{
                printf("Inviato segnale al padre.\n");
                kill(getppid(), SIGUSR1);
                return 0;
            }
        }
    }

    // Raccogli e stampa lo stato di terminazione dei figli
    int status;
    for(int i=0; i<N; i++){
        wait(&status);
        printf("Figlio %d-esimo terminato con stato %d.\n", i, status);
    }

    return 0;
}