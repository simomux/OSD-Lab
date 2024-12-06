# ESERCITAZIONE DI GIOVEDÌ 14/11/2024
## ESERCIZI SUI THREAD

1. Scrivere un programma C `gestoreRisorse.c` che deve generare un numero non noto di thread (il numero sia passato come parametro, come nel caso del programma `nrogenericoThread.c`). 

    Questi thread eseguono il codice corrispondente al primo esempio di uso dei semafori visto a lezione: *GESTIONE DI UN INSIEME DI RISORSE EQUIVALENTI* (`EsempiDiUsoDISemafori-2ter.pdf`).

    Il numero di risorse equivalenti (per semplicità) può essere definito da una costante che deve essere chiamata `m` (ad esempio uguale a 5, ma chiaramente è possibile variare tale numero a piacimento). Si segnala che il caso più interessante è comunque quello in cui il numero di thread sia significativamente maggiore del numero di risorse (ad esempio, 10 thread per 5 risorse).

    La start_routine si deve chiamare *esegui* e devono essere previste le due funzioni RICHIESTA e RILASCIO mostrate a lezione.

    L'utilizzo della risorsa deve essere simulato con una sleep(5).
    
    Ogni thread deve tornare al main thread il numero d'ordine della risorsa che è stata assegnata e quindi utilizzata.

    Provare il funzionamento del programma, ad esempio con la seguente invocazione:
    ```bash
    $ gestoreRisorse 10
    ```

2. Scrivere un programma C `lettori-scrittori.c` che deve generare un numero non noto di threads (il numero sia passato come parametro, come nel caso del programma `nrogenericoThread.c` e, per quanto sarà di seguito illustrato, deve essere un multiplo di 4) che eseguono il codice corrispondente al secondo esempio di uso dei semafori visto a lezione: *LETTORI E SCRITTORI senza starvation* (`EsempiDiUsoDISemafori-2ter.pdf`).

    Si assuma, per semplicità, che il numero di lettori e il numero di scrittori sia uguale. Devono essere creati:
    - Per prima cosa un quarto dei thread classificati come lettori
    - Poi un quarto di quelli classificati come come scrittori
    - Poi, di nuovo, un quarto di lettori
    - Quindi l'ultimo quarto di scrittori.

    La start_routine dei lettori si deve chiamare *eseguiLettura*, mentre quella degli scrittori si deve chiamare *eseguiScrittura* e devono essere previste le 4 funzioni Inizio_lettura, Fine_lettura, Inizio_scrittura e Fine_scrittura mostrate a lezione.

    L'utilizzo della risorsa in lettura o in scrittura deve essere simulato con una sleep(5).
    
    Ogni thread deve tornare al main thread il proprio numero d'ordine.

    Provare il funzionamento del programma, ad esempio con la seguente invocazione:
    ```bash
    $ lettori-scrittori 16
    ```

    **OSSERVAZIONE**. Se si vuole ottenere un funzionamento più aleatorio, si può implementare una generazione random del ‘tipo’ di processo in modo che sia stabilito dal parametro solo il numero totale di thread, ma si abbia per ogni esecuzione un numero non noto di processi lettori e scrittori.

3. Scrivere due programmi C `filosofi-ConMutexCONDEADLOCK.c` e `filosofi-CONDEADLOCK.c` che devono
generare 5 thread che eseguono il codice corrispondente al terzo esempio di uso dei semafori visto a
lezione: *I FILOSOFI* (`EsempiDiUsoDISemafori-2ter.pdf`) risolto con la prima soluzione mostrata.

    Pertanto, si deve usare un array di mutex (per il programma `filosofi-ConMutexCONDEADLOCK.c`) oppure
    un array di semafori (per il programma `filosofi-CONDEADLOCK.c`).

    Si adotti una soluzione simmetrica (che può portare al DEADLOCK!)

    La start_routine si deve chiamare *eseguiFilosofo*.

    La fase in cui il filosofo mangia deve essere simulata con una sleep(5) mentre quella in cui pensa deve
    essere simulata con un descheduling del thread.

    I filosofi devono eseguire il loro codice in un ciclo con NTIMES ripetizioni: per semplicità si assuma NTIMES costante ed eguale a 10.

    Ogni thread deve tornare al main thread il proprio numero d'ordine.

    Provare il funzionamento dei due programmi.
    ```bash
    $ filosofi-ConMutexCONDEADLOCK
    $ filosofi-CONDEADLOCK
    ```

4. Scrivere due programmi C `filosofi-ConMutexSolAsimmetrica.c` e `filosofi-SolAsimmetrica.c` che partendo dai due programmi dell’esercizio precedente risolvano il possibile problema di deadlock usando una soluzione asimmetrica.

    Provare il funzionamento dei due programmi:
    ```bash
    $ filosofi-ConMutexSolAsimmetrica
    $ filosofi-SolAsimmetrica
    ```

    **SUGGERIMENTO**: Creare uno script in shell che prenda in ingresso un numero intero N e il nome di un eseguibile EXE. N deve essere usato nello script per chiamare iterativamente programma eseguibile EXE derivante dalle due soluzioni di questo esercizio, in modo da verificare in modo semi-automatico che esecuzioni diverse sono sempre esenti da problemi, ma possono generare output diversi. Si usi la ridirezione dell’output per mantenere i log delle varie esecuzioni.