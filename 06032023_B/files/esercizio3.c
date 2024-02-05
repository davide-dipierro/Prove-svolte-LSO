#include "stdio.h"
#include "stdlib.h"
#include "sys/wait.h"
#include "unistd.h"
#include "signal.h"

void signal_handler(int s){ ; }

int main (int argc, char** argv) {
    printf("\nINIZIO PROGRAMMA\n");
    int N = atoi(argv[1]);
    int N1 = atoi(argv[2]);
    int N2 = atoi(argv[3]);
    char* comando = argv[4]; 

    int pid1 = fork();
    if(pid1==0){
        printf("P1: Inizia l'esecuzione.\n");
        fflush(stdout);
        sleep(N1);
        printf("P1: Terminata l'attesa.\n");
        execlp(comando, comando, NULL);
        printf("Errore nell'esecuzione del comando.\n");
        return 0;
    }
    int pid2 = fork();
    if(pid2==0){
        printf("P2: Inizia l'esecuzione.\n");
        while(N2){
            kill(getppid(), SIGUSR1);
            N2--;
            printf("P2: Segnale USR1 inviato a P0.\n");
            sleep(1);
        }
        kill(pid1, SIGKILL);
        printf("P2: Segnale KILL inviato a P1.\nP2: Termino.\n");
        return 0;   
    }
    signal(SIGUSR1, signal_handler);
    printf("P0: Inizia l'esecuzione.\n");
    while(N) {
        pause();
        N--;
    }
    printf("P0: Ricevuti tutti o segnali. Attendo P1 e P2.\n");
    while(wait(NULL)>0) ;

    printf("P0: Termino.\n");
    return 0;
}