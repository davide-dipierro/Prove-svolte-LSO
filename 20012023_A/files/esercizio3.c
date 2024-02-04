#include "unistd.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "stdbool.h"



int main(int argc, char **argv) {

    FILE *file = fopen(argv[1], "rw+");
    char *tabu = argv[2];
    size_t len = strlen(tabu);
    int i = atoi(argv[3]);
    int j = atoi(argv[4]);

    if (file == NULL || i >= j || i < 0 || j < 0 || argc != 5) printf("Errore\n"), exit(1);

    fseek(file, i, SEEK_SET);

    while(1) {
        if (ftell(file) == j) break;
        char c = fgetc(file);
        if (c == EOF) break;
        if (c == tabu[0]) {
            bool found = true;
            for (int k = 1; k < len; k++) {
                if (fgetc(file) != tabu[k]) {
                    fseek(file, -k, SEEK_CUR);
                    found = false;
                    break;
                }
            }
            if (found) {
                printf("Trovato %s\n", tabu);
                fseek(file, -len+1, SEEK_CUR);
                for (int k = 0; k < len; k++) {
                    fprintf(file, "*");
                }
            }
        }
    }

    fclose(file);
    return 0;


}