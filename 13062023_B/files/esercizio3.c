#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"
#include "signal.h"

#define buffer_size 6


void inverti(char* buffer){
    for(int i = 0; i < buffer_size/2; i++) {
        char temp = buffer[i];
        buffer[i] = buffer[buffer_size - i - 1];
        buffer[buffer_size - i - 1] = temp;
    }
}

void signal_handler(int signo){
    ;
}

int main(int argc, char** argv){


    int pid = fork();
    if(pid == 0){ // Codice P1
        char buffer[buffer_size];
        printf("P1: Inserisci il messaggio: ");
        scanf("%s", buffer);

        FILE* file = fopen("mail2.txt", "w");
        fwrite(buffer, sizeof(char), buffer_size, file);
        fclose(file);
        kill(getppid(), SIGUSR1);
        printf("P1: Ho inviato il messaggio\n");

        signal(SIGUSR1, signal_handler);
        pause();
        printf("P1: Ho ricevuto il segnale\n");

        FILE* file2 = fopen("mail1.txt", "r");
        fread(buffer, sizeof(char), buffer_size, file2);
        fclose(file2);
        printf("P1: Ho letto il messaggio: %s\n", buffer);
        return 0;


    }else{ // Codice P2
        signal(SIGUSR1, signal_handler);
        pause();
        printf("P2: Ho ricevuto il segnale\n");

        char buffer[buffer_size];
        FILE* file2 = fopen("mail2.txt", "r");
        fread(buffer, sizeof(char), buffer_size, file2);
        fclose(file2);
        printf("P2: Ho letto il messaggio: %s\n", buffer);

        inverti(buffer);
        printf("P2: Ho invertito il messaggio\n");

        FILE* file3 = fopen("mail1.txt", "w");
        fwrite(buffer, sizeof(char), buffer_size, file3);
        fclose(file3);
        kill(pid, SIGUSR1);
        printf("P2: Ho inviato il messaggio\n");
        return 0;
    }
}