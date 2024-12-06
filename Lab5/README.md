# ESERCITAZIONE DI GIOVEDÌ 31/10/2024
## ESERCIZI SU THREAD

**OSSERVAZIONE**: su GitHub si trova un programma `nrogenericoThread.c` che, rispetto agli esempi forniti nella scorsa esercitazione, all’atto della invocazione accetta un parametro che rappresenta il numero di thread che devono essere creati.

1. Partendo dal programma nrogenericoThread.c, scrivere un programma C `nrogenericoThread-SommaSenzaUsoLock.c` in cui:
    - Si definisce una variabile globale x di tipo intero (inizializzata a 0).
    - Ogni thread figlio deve incrementare di 1 la variabile x e riportare su standard output il valore incrementato di x e il proprio TID (Thread IDentifier). Queste operazioni devono essere ripetute in un ciclo per 10 volte.

    Provare il funzionamento del programma usando, ad esempio, la seguente invocazione:
    ```
    $ nrogenericoThread-SommaSenzaUsoLock 10
    ```
    
2. Scrivere un programma C `nrogenericoThread-SommaConUsoLock.c` che, partendo dal programma precedente, vada a proteggere la SEZIONE CRITICA, rappresentata dal ciclo di incrementi con un mutex.

    Provare il funzionamento del programma usando, ad esempio, la seguente invocazione:
    ```bash
    $ nrogenericoThread-SommaConUsoLock 10
    ```
  