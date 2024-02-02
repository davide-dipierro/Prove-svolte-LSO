#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

void P_Func(char* f, char C){
    printf("Il processo %d inizia\n", getpid());
    int fd = open(f, O_RDONLY);
    char c;
    do read(fd, &c, sizeof(char));
    while(c!=C && c!=EOF);
}

void notifica(pid_t P_Winner){
    printf("Il processo %d ha vinto\n", P_Winner);
}

void Padre_Func(pid_t P1_PID, pid_t P2_PID){
    pid_t P_Winner = wait(NULL);
    if(P_Winner==P1_PID) kill(P2_PID, SIGKILL);
    else kill(P1_PID, SIGKILL);
    notifica(P_Winner);
}

int main(int argc, char** argv){
    if(argc!=6) printf("Usage: %s <i> <j> <f> <C1> <C2>\n", argv[0]), exit(1);

    char* f = argv[3];
    char C1 = argv[4][0];
    char C2 = argv[5][0];
    
    pid_t P1_PID = fork();
    if(P1_PID==0) P_Func(f, C1); 
    else{ 
        pid_t P2_PID = fork();
        if(P2_PID==0) P_Func(f, C2);
        else Padre_Func(P1_PID, P2_PID);
    }

}