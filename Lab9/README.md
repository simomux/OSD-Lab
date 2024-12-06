# ESERCITAZIONE DI GIOVEDÌ 05/12/2024
## ESERCIZI SU THREAD
1. Scrivere un programma C `fumatori.c` che deve generare 4 threads che eseguono il codice corrispondente al PROBLEMA DEI FUMATORI DI SIGARETTE (con la soluzione illustrata ad esercitazione).
    - Il primo thread creato deve essere il tabaccaio, mentre gli altri 3 threads devono essere i fumatori.
    - La start_routine del tabaccaio si deve chiamare *eseguiTabaccaio*, mentre quella dei fumatori si deve chiamare *eseguiFumatore*.
    - La fase corrispondente a fumare la sigaretta da parte dei fumatori deve essere simulata con una *sleep(5)*.

    **OSSERVAZIONE**: nell’implementazione è meglio che i fumatori eseguano in un ciclo infinito, mentre per il tabaccaio si faccia eseguire il codice in un ciclo con NTIMES ripetizioni (per semplicità si assuma NTIMES costante e uguale a 10).
    
    Quindi il main dovrà aspettare solo il tabaccaio e al termine del main anche i thread fumatori termineranno.
    
    Provare il funzionamento del programma:
    ```bash
    $ fumatori
    ```


2. Scrivere un programma C `cuocoECannibali.c` che deve generare un numero non noto di threads che eseguono il codice corrispondente al PROBLEMA DEI CANNIBALI A CENA (con la soluzione illustrata ad esercitazione).
    - Il primo thread creato deve essere il cuoco, mentre gli altri threads devono essere i cannibali.
    - Per semplicità M sia posto costante e uguale a 5.
    - La start_routine del cuoco si deve chiamare *eseguiCuoco*, mentre quella dei cannibali si deve chiamare *eseguiCannibale*.
    - La fase di riempimento della pentola da parte del cuoco e la fase di mangiare da parte di cannibali devono essere simulate con una *sleep(5)*.
    
    **OSSERVAZIONE**: nell’implementazione è meglio che il cuoco esegua in un ciclo infinito; quindi il main non dovrà aspettare il cuoco e al termine del main anche il thread del cuoco terminerà.

    Provare il funzionamento del programma, ad esempio con la seguente invocazione:
    ```bash
    $ cuocoECannibali 10
    ```
    
    **OSSERVAZIONE**: è opportuno che il numero di thread CANNIBALE sia sempre maggiore del valore di M: nella soluzione di cui verrà mostrato un possibile output il numero porzioni è posto uguale a 5 e quindi 9 cannibali (10 thread con il cuoco) è un numero che potrebbe evidenziare, in dipendenza dei tempi di arrivo dei cannibali, che alcuni cannibali si sospendono in attesa che il cuoco riempia di nuovo la pentola.


3. Scrivere un programma C `cuocoECannibali-ConPorzioniInizialiA0.c` che, partendo dal programma precedente ponga semplicemente il numero iniziale di porzioni uguale a 0.

    Provare il funzionamento del programma, ad esempio con la seguente invocazione:
    ```bash
    $ cuocoECannibali-ConPorzioniInizialiA0 10
    ```
    **DOMANDA**: Che differenza sostanziale si nota nel funzionamento?
    
    **OSSERVAZIONE**: Fare attenzione a non cambiare il valore iniziale del semaforo VUOTA ponendolo a 1 perché in tal caso si può avere una corsa critica per cui arriva per primo un cannibale che fa una signal su VUOTA e porta il semaforo a 2 e il cuoco, quindi, potrebbe svolgere due cicli di riempimento, il secondo dei quali potrebbe avvenire prima che la pentola sia stata svuotata.