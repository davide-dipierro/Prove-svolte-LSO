#include "stdio.h"
#include "stdlib.h"
#include "signal.h"
#include "unistd.h"

char* comando;

void signal_handler(int s){
    printf("\nP1: Ricevuto il segnale.");
    execlp(comando, comando, NULL);
    exit(0);
}

int main(int argc, char** argv){
    printf("\nInizio del programma\n");
    comando = argv[2];
    char Cstop = argv[3][0];
    char Cecc = argv[4][0];
    int comm_pipe[2];
    pipe(comm_pipe);

    int pid = fork();
    if(pid==0){
        signal(SIGUSR1, signal_handler);
        close(comm_pipe[0]);
        printf("P1: Inizio a leggere da file.\n");
        FILE* filein = fopen(argv[1], "r");
        char c;
        do{
            c = fgetc(filein);
            write(comm_pipe[1], &c, sizeof(char));
        } while (c!=EOF);
        printf("P1: Finito di leggere, aspetto il segnale.\n");
        pause();
    }

    close(comm_pipe[1]);
    printf("P0: Inizio a leggere da pipe.\n");
    char c;
    printf("P0: ");
    do{
        read(comm_pipe[0], &c, sizeof(char));
        printf("%c",c);
        if(c==Cstop) kill(pid, SIGKILL), exit(0);
        if(c==Cecc) kill(pid, SIGUSR1), exit(0);
        if(c==EOF) printf("P0: Nessun carattere significativo ricevuto.\n"), exit(1);
    } while(1);

}