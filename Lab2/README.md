# ESERCITAZIONE DI GIOVEDÌ 10/10/2024
## ESERCIZI SU PROCESSI, FILE E COMUNICAZIONE
1. Scrivere un programma `padreFigliConConteggioOccorrenze.c` che deve prevedere un numero variabile N+1 di parametri:
    - I primi N (con N maggiore o uguale a 2, da controllare) rappresentano N nomi di file (F1, F2, ..., FN),
    - L’ultimo rappresenta un singolo carattere Cx (da controllare). Il processo padre deve generare N processi figli (P0, P1, … PN-1): i processi figli Pi (con i che varia da 0 a N-1) sono associati agli N file Ff (con f = i+1). 
    
    Ogni processo figlio Pi deve leggere dal file associato contando le occorrenze del carattere Cx e, al termine del conteggio, deve ritornare al padre il numero di occorrenze (NOTA BENE: si può supporre minore di 255).
    
    A quel punto, il padre deve stampare su standard output il PID di ogni figlio e il valore ritornato.

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

3. Scrivere un programma `padreEFiglioComunicanti.c`, che deve considerare un singolo parametro che deve essere il nome di file (F). Si deve garantire che F contenga per ogni linea 4 caratteri (oltre al terminatore di linea ‘\n’) e quindi la lettura potrà avvenire a 5 caratteri alla volta, CON UNA SINGOLA READ.

    Il padre deve creare un singolo figlio.

    Il figlio:
    - Deve leggere dal file F 5 caratteri alla volta
    - Deve trasformare l’array di 5 caratteri in una stringa (quindi il carattere ‘\n’ deve essere sostituito con il carattere ‘\0’)
    - deve inviare al padre tale stringa CON UNA SINGOLA WRITE.
    - Una volta terminata la lettura di tutto il file, riportare sullo standard output il numero di informazioni lette (e quindi inviate al padre)
    - Infine, terminare riportando il valore di successo. 

    Il padre:
    - Deve ricevere tutte le stringhe inviate dal figlio e le deve riportare via via sullo standard output insieme con il numero d’ordine di tali stringhe (fatto partire da 0).
    - Deve riportare sullo standard output il numero totale di informazioni ricevute (una volta terminata la lettura di tutte le stringhe)
    - Poi deve aspettare il figlio, riportando sullo standard output il valore ritornato dal figlio.

    Provare il funzionamento del programma creando un opportuno file di nome `input.txt`. Dopo avere provato una prima volta il funzionamento, modificare il contenuto del file `input.txt`, aggiungendo o togliendo informazioni, quindi provare di nuovo il funzionamento.

4. Scrivere un programma `padreEFiglioComunicanti-senzaClose.c` partendo dal programma precedente, facendo sì che non effettui la chiusura dei lati della pipe usata nella comunicazione, sia per il figlio che per il padre.

    Provare il funzionamento del programma con lo stesso file `input.txt` del precedente programma e verificare che cosa succede.