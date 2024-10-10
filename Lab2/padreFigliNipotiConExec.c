#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

/* Esercizio 2:
2. Scrivere un programma `padreFigliNipotiConExec.c` che deve prevedere un numero variabile N di parametri (con N maggiore o uguale a 3, da controllare) che rappresentano nomi di file (F1, F2. ..., FN).

    Il processo padre deve generare N processi figli (P0, P1, … PN-1): i processi figli Pi (con i che varia da 0 a N-1) sono associati agli N file Ff (con f = i+1).

    Ogni processo figlio Pi deve, nell’ordine:
    - Creare un file FOut il cui nome deve risultare dalla concatenazione del nome del file associato Ff con la stringa “.sort”
    - Creare a sua volta un processo nipote Ppi. 
    
    Ogni processo nipote PPi esegue concorrentemente e deve:
    - Ordinare il file Ff secondo il normale ordine alfabetico usando in modo opportuno il filtro sort di UNIX/Linux
    - Riportare il risultato di tale comando sul file FOut
    - Ritornare al figlio il valore ritornato dal comando sort (in caso di insuccesso nella esecuzione del sort deve essere tornato il valore -1).

    A sua volta, ogni processo figlio Pi deve ritornare al padre il valore restituito da ciascun nipote. 
    
    Il padre deve stampare, su standard output, i PID di ogni figlio con il corrispondente valore ritornato.
*/

int main(int argc, char *argv[]) {
    int buffsize = 200;
    char error[buffsize];
    int nChildren, status, pid;

    if (argc < 3) {
        snprintf(error, buffsize, "Wrong arguments!\n");
        perror(error);
        exit(1);
    }

    nChildren = argc - 1;

    printf("Numero figli: %d\n", nChildren);

    for (int i = 0; i < nChildren; i++) {

        if ((pid = fork()) < 0) {
            perror("fork");
            exit(2);
        }

        if (pid == 0) {
            char *filename = argv[i+1];
            char *sortfilename = strcat(argv[i+1], ".sort");
            FILE *file = fopen(sortfilename, "w");
            printf("Il figlio %d con pid %d ha creato il file %s\n", i, getpid(), sortfilename);

            int sonPid, sonStatus;

            if ((sonPid = fork()) < 0) {
                perror("fork");
                exit(2);
            }

            if (sonPid == 0) {
                int sortValue;

                FILE *readfile = fopen(filename, "r");

                if (readfile == NULL) {
                    perror("file");
                    exit(3);
                }

                printf("Il nipote di %d con pid %d ha letto il file %s\n", i, getpid(), filename);

                return sortValue;
            }



            return 0;
        }
    }


    return 0;
}