# ESERCITAZIONE DI GIOVEDÌ 26/09/2024

## ESERCIZI SUI FILE UTILIZZANDO LE FUNZIONI DI BASSO LIVELLO

1. Scrivere  un  programma  in  C, `mycat.c`,  che  deve  implementare  il  cat  di  UNIX/Linux  sia  come comando che come comando-filtro. In altre parole, il programma deve funzionare:
    - Sia passandogli un parametro, che deve essere il nome di un file (versione comando),
    - Sia senza passargli parametri (versione comando-filtro).  

    Nel caso a) il programma deve visualizzare sullo standard output il contenuto del file il cui nome è stato passato come parametro; nel caso b) il programma deve visualizzare sullo standard output tutto quello che viene letto dallo standard input.  

    Provare  il  funzionamento  nei  due  casi  e  nel  caso  b)  provare  anche  la  ridirezione  in  input;  per entrambi i casi, poi, provare anche ad usare la ridirezione in output.

2. Scrivere un programma in C, `myhead.c`, che deve implementare  l’head di UNIX/Linux  sia come comando che come comando-filtro. In altre parole, il programma deve funzionare  con 0, 1 o 2 parametri:
    - Con 0 parametri, il programma si deve comportare come il comando-filtro head visualizzando sullo standard output le prime 10 linee dello standard input (se esistono);
    - Con 1 parametro:
        - Se  il  parametro  è  nella  forma  –numero,  il  programma  si  deve  comportare  come  il comando-filtro  head  visualizzando  sullo  standard  output  le  prime  -numero  linee  dello standard input (se esistono)
        - Se il parametro non è nella forma –numero, allora tale parametro deve essere considerato il nome di un file e il programma si deve comportare come il comando head visualizzando sullo standard output le prime 10 linee del file specificato (se esistono);

    - Con 2 parametri, questi devono essere rispettivamente –numero e il nome di un file (in questo ordine) e quindi il programma si deve comportare come il comando head visualizzando sullo standard output le prime -numero linee del file specificato (se esistono).

    Provare il funzionamento nei quattro casi e nei primi tre casi provare anche la ridirezione in input;
    per tutti i casi, poi, provare anche ad usare la ridirezione in output.

## ESERCIZI SU PROCESSI E I/O POINTER CONDIVISO

3. Scrivere  un  programma  in  C,  `multi-writer.c`,  che  deve  considerare  3  parametri  (strettamente maggiori di 0):  
    - numero di processi (nchildren),  
    - numero di blocchi (nblocks),  
    - dimensione del blocco (blocksize).

    Il padre deve creare nchildren figli, ognuno dei quali deve scrivere, CON UNA SINGOLA WRITE, un blocco di byte di dimensione blocksize per nblocks volte sullo standard output.  
    Una volta che tutti i figli abbiano terminato la scrittura (e quindi siano terminati), il padre deve verificare che la lunghezza dello standard output sia uguale a quella attesa (nblocks*blocksize).  

    Provare il funzionamento del programma utilizzando esclusivamente la ridirezione in output.
    Si suggerisce la seguente invocazione:
    `$ multi_writer 10 10000 1000 > log`

4.  Scrivere  un  programma  in  C,  `multi-writer1.c`,  che,  partendo  dal  programma  precedente,  deve considerare un quarto parametro. Questo parametro rappresenta il nome di un file che il padre deve creare PRIMA di creare i figli.
    
    Provare il funzionamento del programma.
    Si suggerisce la seguente invocazione:
`$ multi_writer1 10 10000 1000 log1`
