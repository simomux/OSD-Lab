
# ESERCITAZIONE DI VENERDÌ 18/10/2024
## ESERCIZI SU PROCESSI, FILE E COMUNICAZIONE

**OSSERVAZIONE:** Nel programma `padreEFiglioComunicanti.c` della scorsa esercitazione, 
il protocollo di comunicazione che era stato adottato da padre-figlio prevedeva (a livello di programmazione) una
dimensione fissa dei messaggi che venivano scambiati. Nei primi due esercizi che seguono, invece, si
considera come (sempre a livello di programmazione) sia possibile prevedere un protocollo di comunicazione
in cui la dimensione dei messaggi sia variabile.

1. Scrivere un programma C `padreEFiglioComunicanti1.c` che, partendo dal programma
`padreEFiglioComunicanti.c` della scorsa esercitazione, assuma un diverso protocollo di comunicazione che consideri la possibilità di scambiare linee/stringhe di lunghezza generica.
    - Il figlio, dopo aver letto una linea dal file passato come parametro (supposta non più lunga
    di 512 caratteri, compreso il terminatore di linea) [*], deve:
        - Trasformare tale linea in stringa (come in `padreEFiglioComunicanti.c`)
        - Mandare per prima cosa la lunghezza della stringa al padre
        - Mandare la stringa al padre (con una singola `WRITE`)
    - A quel punto, il padre, per ogni linea letta dal figlio:
        - Riceve per prima cosa la lunghezza della stringa
        - Deve usare questa informazione per leggere (con una singola `READ`) i caratteri che costituiscono
        la stringa
        - Deve poi stamparla analogamente al programma `padreEFiglioComunicanti.c` della scorsa
        esercitazione.
    
    **[*] NOTA BENE:** Per leggere una linea dal file, il figlio deve leggere un carattere alla volta dal file fino a
    che non incontra il carattere `\n`.

2. Scrivere un programma C `padreEFiglioComunicanti2.c` che, partendo sempre dal programma
`padreEFiglioComunicanti.c` della scorsa esercitazione, assuma un altro protocollo
di comunicazione che consideri la possibilità di scambiare linee/stringhe di lunghezza generica, come
nell’esercizio precedente, ma risolvendo il problema in modo diverso.
    - Il figlio, dopo aver letto una linea dal file passato come parametro (supposta non più lunga
    di 512 caratteri compreso il terminatore di linea), deve:
        - Trasformare tale linea in stringa
        - Mandare la stringa al padre
    - A quel punto, il padre, per ogni linea letta dal figlio:
        - Deve ricevere via via i singoli caratteri inviati dal figlio fino al terminatore di stringa
        - Deve poi stampare la stringa analogamente al programma `padreEFiglioComunicanti.c` della scorsa esercitazione.
    
    **Domanda:** È rilevante che il figlio trasformi la linea in stringa?

3. Scrivere un programma C `multi_writerBis.c` che, partendo dal programma `multi-writer1.c` della prima
esercitazione (si veda il testo relativo), deve considerare solo 2 parametri:
    - Numero di blocchi (`nblocks`, strettamente maggiore di 0)
    - Nome di un file.

    Il padre deve:
    - Per prima cosa creare il file (che poi deve subito chiudere)
    - Poi creare 10 figli
    
    Ognuno dei figli deve:
    - Posizionarsi alla fine del file
    - Scrivere sul file il carattere numerico corrispondente al proprio numero d’ordine, ripetendo
    questa scrittura per `nblocks` volte.
    
    Provare il funzionamento del programma, ad esempio con la seguente invocazione:
    ```
    $ multi_writerBis 100000 log
    ```
    **[*] NOTA BENE:** Non c’è alcuna garanzia che i 100000 caratteri scritti da ogni processo sul file siano ‘adiacenti’.

4. Scrivere un programma C `multi_writerBis-conSimulazioneSemaforo.c` che, partendo dal programma
precedente, vada ad implementare un semaforo di mutua esclusione (come visto a lezione, usando una
`pipe`).
    - Tramite il semaforo di mutua esclusione si vada a proteggere, nel codice dei figli, la sezione critica
    rappresentata dal posizionamento alla fine del file e dal ciclo di scrittura degli `nblocks` caratteri.

    Provare il funzionamento del programma, ad esempio con la seguente invocazione:
    ```
    $ multi_writerBis-conSimulazioneSemaforo 100000 log1
    ```
    **[*] NOTA BENE:** Verificare che i 100000 caratteri scritti da ogni processo sul file siano ‘adiacenti’.
