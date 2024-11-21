# ERCITAZIONE DI GIOVEDÌ 21/11/2024

## ESERCIZI SU THREAD
1. Scrivere un programma C `produttori-consumatori.c` che deve generare un numero non noto di threads (il numero sia passato come parametro, come nel caso del programma `nrogenericoThread.c` e per quanto sarà di seguito illustrato sia un multiplo di 2) che eseguono il codice corrispondente al quarto esempio di uso dei semafori: PRODUTTORI E CONSUMATORI.

    Si assuma, per semplicità, che il numero di produttori e il numero di consumatori sia uguale:
    - devono prima essere creati una metà di thread che devono agire come produttori,
    - devono poi un'altra metà come consumatori.
    
    La dimensione del buffer usato per la comunicazione può essere definita da una costante (per semplicità) che deve essere chiamata $N$ (ad esempio uguale a 5).
    Ogni singolo messaggio scambiato deve essere una stringa di lunghezza 4 caratteri (quindi un array di 5 caratteri per comprendere anche il terminatore di stringa).
    La start_routine dei produttori si deve chiamare `eseguiProduttore`, mentre quella dei consumatori si deve chiamare `eseguiConsumatore` e devono essere previste le 2 funzioni INSERIMENTO e PRELIEVO mostrate a lezione.
    La fase di produzione deve essere simulata andando a memorizzare nel messaggio che deve essere
    depositato il numero d'ordine del thread produttore, mentre la fase di consumo del messaggio deve essere simulata con una sleep (ad esempio di 2 sec.).
    Sia produttori che consumatori eseguono il loro codice in un ciclo con NTIMES ripetizioni (per semplicità, si assuma NTIMES costante e eguale a 10). Ogni thread torna al main thread il proprio numero d'ordine.
    Provare il funzionamento del programma, ad esempio con la seguente invocazione: 
    
    ```bash
    $ produttori-consumatori 20
    ```

    **OSSERVAZIONE**. Per un funzionamento più aleatorio, si può implementare una generazione random del ‘tipo’ di processo in modo che sia stabilito dal parametro solo il numero totale di thread, ma si abbia per ogni esecuzione un numero non noto di processi lettori e scrittori.



2. Scrivere un programma C `produttori-consumatori-ConStruct.c` che, partendo dal precedente programma,
    renda più chiare le stampe facendo sì che i produttori depositino nel buffer un messaggio costituito dalla seguente struct:
    ```c
    typedef struct{
        char dato[5]; /* stringa che rappresenta il vero messaggio */
        int iter; /* valore della iterazione corrente */
                } Messaggio;
    ```
    Si noti che, nella struttura precedente, abbiamo un `dato[5]`; perché, per semplicità ogni messaggio va considerato di dimensione fissa e pari ad una stringa di 4 caratteri (più il terminatore di stringa).
    Quindi la fase di produzione deve essere simulata andando a memorizzare nel campo dato del messaggio (che deve essere depositato) il numero d'ordine del thread produttore e nel campo iter il numero della iterazione corrente (che si ricorda varia da 0 a NTIMES-1).

    Provare il funzionamento del programma, ad esempio con la seguente invocazione:

    ```bash
    $ produttori-consumatori-ConStruct 20
    ```

3. Scrivere un programma C `filosofi-ConVarCondition.c` che deve generare 5 threads che eseguono il codice corrispondente al PROBLEMA DEI FILOSOFI, ma risolto con la soluzione mostrata a lezione che usava un tipo `monitor`.

    Si devono quindi usare un mutex e un array di variabili condition.
    
    La start_routine si deve sempre chiamare `eseguiFilosofo`; e devono essere previste le 3 funzioni Pick_up, Put_down e test mostrate a lezione.

    Provare il funzionamento del programma, ad esempio con la seguente invocazione:

    ```bash
    $ filosofi-ConVarCondition
    ```

4. Scrivere un programma C `lettori-scrittori-ConVarCondition.c` che deve generare un numero non noto di threads che eseguono il codice corrispondente al PROBLEMA LETTORI E SCRITTORI, ma risolto con la
soluzione mostrata a lezione che usava un tipo `monitor`.

    Si devono quindi usare un mutex e due variabili condition. Si noti che, poiché le condition variable non prevedono la funzione QUEUE, usata nella soluzione mostrata a lezione, si dovranno mantenere due variabili (`int lettori_bloccati = 0`, `scrittori_bloccati = 0;`).

    Provare il funzionamento del programma, ad esempio con la seguente invocazione:
    
    ```bash
    $ lettori-scrittori-ConVarCondition 16
    ```


**ATTENZIONE**: Gli esercizi 3 e 4 si riferiscono all’uso delle variabili CONDITION della libreria PThreads. Quindi, bisognerebbe utilizzare uno schema di sospensione con un while invece che con un if. Per l’esercizio 3, la sostituzione if-while è banale, mentre per l’esercizio 4 comporta modifiche significative rispetto alla soluzione mostrata a lezione.

Si segnala comunque che sono state prodotte anche le soluzioni che fanno uso dell’if per questi due esercizi e sono state verificate con uno script eseguendole 10 e 100 volte, senza che abbiano presentato problemi. Per l’esercizio 4 sono state prodotte due versioni: una con starvation di lettori e un’altra senza.

