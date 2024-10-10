#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 
#include <sys/types.h>
#include <sys/wait.h>

/* Esercizio 1:
Scrivere un programma `padreFigliConConteggioOccorrenze.c` che deve prevedere un numero variabile N+1 di parametri:
    - I primi N (con N maggiore o uguale a 2, da controllare) rappresentano N nomi di file (F1, F2, ..., FN),
    - L’ultimo rappresenta un singolo carattere Cx (da controllare). Il processo padre deve generare N processi figli (P0, P1, … PN-1): i processi figli Pi (con i che varia da 0 a N-1) sono associati agli N file Ff (con f = i+1). 
    
    Ogni processo figlio Pi deve leggere dal file associato contando le occorrenze del carattere Cx e, al termine del conteggio, deve ritornare al padre il numero di occorrenze (NOTA BENE: si può supporre minore di 255).
    
    A quel punto, il padre deve stampare su standard output il PID di ogni figlio e il valore ritornato.
 */

int main(int argc, char* argv[]) {
    int buffsize = 200;
    char error[buffsize];
    char charToCheck;
    int nChildren, pid, status;

    if (argc < 3) {
        snprintf(error, buffsize, "Not enough arguments!\n");
        perror(error);
        exit(1);
    }

    charToCheck = argv[argc-1][0];

    if (charToCheck < 32 || charToCheck > 127) {
        snprintf(error, buffsize, "Wrong character!\n");
        perror(error);
        exit(2);
    }

    nChildren = argc - 2;

    printf("Carattere da cercare: %c\n", charToCheck);
    printf("Numero di figli: %d\n", nChildren);


    for (int i = 0; i < nChildren; i++) {
        char *filename = argv[i+1];

        if ((pid = fork()) < 0) {
            perror("fork");
            exit(3);
        }

        if (pid == 0) {
            printf("Figlio %d con pid %d apre file %s\n", i, getpid(), filename);
            pid = getppid();

            FILE *file = fopen(filename, "r");

            if (file == NULL) {
                perror("file");
                exit(4);
            }

            char buffer[100];
            int charOccurrencies = 0;
            while (fgets(buffer, 100, file) != NULL) {
                int j = 0;
                while (buffer[j] != '\0'){
                    if (buffer[j] == charToCheck) charOccurrencies++;
                    j++;
                }
            }

            printf("Trovato nel file %s il carattere '%c' %d volte\n", filename, charToCheck, charOccurrencies);

            return(charOccurrencies);
        }
        waitpid(pid, &status, 0);
        if (WIFEXITED(status)) {
            printf("Il figlio %d con pid %d ha trovato nel file %s il carattere '%c' %d volte\n", i, pid, filename, charToCheck, WEXITSTATUS(status));
        }

    }

    return 0;
}