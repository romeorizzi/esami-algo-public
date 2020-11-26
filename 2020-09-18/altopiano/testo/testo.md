# Poldo e l'altopiano (altopiano)

## Descrizione del problema

Poldo ama camminare in montagna e godersi il panorama ovunque trova un altipiano su cui fermarsi lungo le sue camminate.
Con l'aiuto della mappa altimetrica, ripone in un array $A$ indicizzato da $0$ a $N-1$ le $N$ altezze (in metri) incontrate lungo un percorso prefissato, come preso da una delle sue guide tascabili. Poi individua e studia con attenzione gli altipiani: per Poldo un altipiano è una sequenza di almeno 3 altezze uguali.
Raramente Poldo ha il tempo per attraversare l'intero percorso, o i mezzi per raggiungere le località ai suoi estremi, e seleziona piuttosto la sua camminata come un sottopercorso opportuno.
Ogni sua camminata corrisponde pertanto ad un sottointervallo dell'array $A$, e la prima cosa cui guarda sono gli altipiani più alti della sua camminata.
Ma tra una camminata e l'altra qualche altezza del percorso potrebbe cambiare, a causa delle frane o degli agenti atmosferici.


## File di input

Il programma deve leggere da `stdin`.
Nella prima riga sono presenti due interi $N$ e $M$, il numero delle altezze e il numero di operazioni da eseguire.
La seconda riga contiene $N$ interi, le altezze iniziali del percorso. (Oggi Poldo è di stanza a Pompei e vorrà affrontare il Sentiero degli Dei della Costiera Amalfitana.)
Le successive $M$ righe contengono la descrizione dell'operazione richiesta:
-Se il primo intero è 1, è seguito da altri due interi $x$ e $y$ e descrive una variazione dell'altitudine di indice $x$ di $y$ metri ($x\in [0,N-1]$, l'intero $y$ può essere anche negativo).
-Se il primo intero è 2, è seguito da altri due interi che specificano l'inizio e la fine della camminata di Poldo (estremi inclusi).

## File di output

Il programma deve scrivere su `stdout`.  
Per ogni richiesta di tipo 2, il programma dovrà stampare una riga contenente un unico intero: l'altezza dell'altipiano più alto presente
nel cammino di Poldo. E' richiesto che tutte e tre le posizioni dell'altipiano più alto, intese come posizioni consecutive del percorso, siano ricomprese entro il cammino. Se non esiste nessun altipiano,
restituire la stringa "NESSUN_ALTOPIANO" (senza virgolette).

## Assunzioni

* $1 \leq N \leq 100\,000$
* $1 \leq M \leq 100\,000$

## Subtask

- **Subtask  1 [ 1  punti]:** casi di esempio
---
- **Subtask  2 [ 1  punti]:** $N \leq 1$, $M \leq 5$
- **Subtask  3 [ 3  punti]:** $N \leq 3$, $M \leq 500$
- **Subtask  4 [ 5  punti]:** $N \leq 10$, $M \leq 500$
---
- **Subtask  5 [ 5 punti]:** $N \leq 1\,000$, $M \leq 1\,000$
- **Subtask  6 [ 10 punti]:** $N \leq 10\,000$, $M \leq 1\,000$, la prima operazione di tipo $2$ avviene dopo l'ultima operazione di tipo $1$
- **Subtask  7 [ 15 punti]:** la prima operazione di tipo $2$ avviene dopo l'ultima operazione di tipo $1$
---
<!-- - **Subtask  8 [ 20 punti]:** è garantito che al momento di ogni richiesta, nel sottointervallo specificato ci sia un unico altipiano. -->
- **Subtask  8 [ 25 punti]:** il cammino di Poldo è l'intero percorso $[0,N-1]$
- **Subtask  9 [ 35 punti]:** nessuna limitazione
---

## Esempio di input/output

| input from stdin                                                  | &nbsp;&nbsp;&nbsp;&nbsp; | output to stdout |
| ----------------                                                  | ------------------------ | ---------------- |
|3 6<br>0 0 0<br>2 0 2<br>1 0 5<br>2 0 2<br>1 1 5<br>1 2 5<br>2 0 2 | &nbsp;                   | 0<br>NESSUN_ALTOPIANO<br>5         |
| &nbsp;                                                            | &nbsp;                   | &nbsp;           |
| 5 4<br> 3 -5 -5 -5 2<br>2 0 2<br>2 2 4<br>2 1 3<br>2 0 4           | &nbsp;                   | NESSUN_ALTOPIANO<br>NESSUN_ALTOPIANO<br>-5<br>-5 |
| &nbsp;                                                            | &nbsp;                   | &nbsp;           |
| 8 4<br>1 2 2 2 3 3 4 5<br>2 1 7<br>2 2 6<br>1 6 -1<br>2 0 7                                                   | &nbsp;                   | 2<br>NESSUN_ALTOPIANO<br>3   |

<!-- ## Note -->
