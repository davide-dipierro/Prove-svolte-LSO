#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"
#include "sys/wait.h"


int main(int argc, char *argv[]) {

    printf("\nEsecuzione di %s\n\n", argv[0]);
    
    for(int i = 1; i < argc; i++) {
        int pid = fork();
        if(pid == 0) {
            execlp(argv[i], argv[i], NULL);
            printf("Errore nell'esecuzione di %s\n", argv[i]);
            exit(1);
        }
    }
    
    while (wait(NULL) > 0);
    

    printf("Esecuzione terminata\n");
    return 0;
}
