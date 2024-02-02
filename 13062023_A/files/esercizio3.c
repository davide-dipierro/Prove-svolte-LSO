#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"

int main(int argc, char** argv){


	int N = atoi(argv[2]);
	char C = argv[3][0];

	// Creazione pipe
	int pipe1[2], pipe2[2];
	if(pipe(pipe1) == -1 || pipe(pipe2) == -1){
		printf("Errore: impossibile creare le pipe\n");
		return -1;
	}

	// Creazione processo figlio 1
	int pid1 = fork();
	if(pid1 == 0){
		printf("P1 INIZIA\n");

		// Chiusura pipe inutilizzate
		close(pipe1[0]);
		close(pipe2[0]);

		// Apertura file
		FILE* file = fopen(argv[1], "r");

		printf("P1 CALCOLA LUNGHEZZA DA LEGGERE\n");
		fseek(file, 0, SEEK_END);
		int length = ftell(file);
		fseek(file, 0, SEEK_SET);
		int pieceLength = length / N;
		if(length % N != 0)
			pieceLength++;

		// Allocazione buffer
		char* buffer = malloc(pieceLength * sizeof(char));

		printf("P1 LEGGE IL PEZZO\n");
		fseek(file, 0, SEEK_SET);
		fread(buffer, sizeof(char), pieceLength, file);
		fclose(file);

		printf("P1 INVIA IL PEZZO\n");
		write(pipe1[1], buffer, pieceLength);

		
		printf("P1 CONTA LE OCCORRENZE DI %c\n", C);
		int occurrences = 0;
		for(int i = 0; i < pieceLength; i++)
			if(buffer[i] == C)
				occurrences++;
		printf("P1 HA TROVATO %d OCCORRENZE DI %c\n", occurrences, C);

		printf("P1 INVIA IL NUMERO OCCORRENZE A P0\n");
		write(pipe2[1], &occurrences, sizeof(int));
		free(buffer);

		printf("P1 TERMINA\n");
		close(pipe1[1]);
		return 0;
	}

	// Creazione processo figlio 2
	int pid2 = fork();
	if(pid2 == 0){
		printf("P2 INIZIA\n");

		// Chiusura pipe inutilizzate
		close(pipe1[1]);
		close(pipe2[0]);

		// Allocazione buffer
		char* buffer = malloc(1024 * sizeof(char));

		// Lettura pezzo
		printf("P2 LEGGE DALLA PIPE IL PEZZO\n");
		int readLength = read(pipe1[0], buffer, 1024);

		printf("P2 CALCOLA IL NUMERO OCCORRENZE DI %c\n", C);
		int occurrences = 0;
		for(int i = 0; i < readLength; i++)
			if(buffer[i] == C)
				occurrences++;
		printf("P2 HA TROVATO %d OCCORRENZE DI %c\n", occurrences, C);


		printf("P2 INVIA IL NUMERO OCCORRENZE A P0\n");
		write(pipe2[1], &occurrences, sizeof(int));
		free(buffer);

		printf("P2 TERMINA\n");
		close(pipe1[0]);
		close(pipe2[1]);
		return 0;
	}

	printf("P0 INIZIA\n");
	// Chiusura pipe inutilizzate
	close(pipe1[0]);
	close(pipe1[1]);
	close(pipe2[1]);

	printf("P0 LEGGE IL NUMERO OCCORRENZE DA P1\n");
	int occurrences1;
	read(pipe2[0], &occurrences1, sizeof(int));
	printf("P0 LEGGE IL NUMERO OCCORRENZE DA P2\n");
	int occurrences2;
	read(pipe2[0], &occurrences2, sizeof(int));
	printf("P1 E P2 HANNO TROVATO LO STESSO NUMERO DI %c? %s\n", C, occurrences1==occurrences2 ? "true" : "false");
	
	return 0;
}
