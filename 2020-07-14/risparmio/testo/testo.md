# Risparmio energetico (risparmio)

## Descrizione del problema

Come incaricato al risparmio energetico nell'illuminazione dell'università,
vuoi minimizzare il tempo di lavoro necessario a spegnere tutte le luci che ogni giorno sono
lasciate accese nelle aule. Hai scoperto che ti viene rapido spegnere una fila di luci consecutive,
quindi ti interessa solo sapere quanti intervalli consecutivi di luci sono rimasti accesi.
Per comodità hai rappresentato gli $N$ punti luce con un vettore $A$ di lunghezza $N$, indicizzato da $0$ a $N-1$.

Questo problema ti chiede di simulare due operazioni:
1) ogni tanto durante la giornata, qualcuno preme l'interruttore di un punto luce, invertendone lo stato acceso/spento.
2) in determinati momenti della giornata vuoi sapere quanti intervalli consecutivi di luci accese ci sono in un determinato
    sottointervallo dell'array $A$.

## Input

Il programma deve leggere da `stdin`.  
Nella prima riga sono presenti due interi $N$ e $M$, il numero delle luci presenti e il numero di operazioni da eseguire.
All'inizio tutte le $N$ luci in $A$ sono considerate spente.
Le successive $M$ righe contengono un numero variabile di interi a seconda dell'operazione richiesta:
-__[operazione di tipo $1$:__ il primo intero della riga è $1$, e un secondo intero specifica il punto luce il cui stato viene invertito.
-__[operazione di tipo $2$:__ il primo intero della riga è $2$, e lo seguono altri $2$ interi che specificano l'inizio e la fine dell'intervallo di cui si vuole sapere (estremi inclusi, indici vanno da $0$ a $N-1$).

## Output

Il programma deve scrivere su `stdout`.  
Per ogni richiesta di tipo 2, il programma dovrà stampare una riga contenente un unico intero:
il numero di intervalli di luci accese in quel determinato momento presenti
entro il sottointervallo specificato dalla richiesta.

## Assunzioni

* $1 \leq N \leq 100\,000$
* $1 \leq M \leq 200\,000$
* È garantito che il numero di query (tipo 2) sia $\leq \frac{M}{20}$ per ogni istanza del problema (tenendo conto dei limiti dei singoli subtask)

## Subtask

- **Subtask  1 [ 1  punti]:** casi di esempio.
---
- **Subtask  2 [ 1  punti]:** $N \leq 1$, $M \leq 5\,00$
- **Subtask  3 [ 3  punti]:** $N \leq 3$, $M \leq 5\,000$
- **Subtask  4 [ 5  punti]:** $N \leq 10$, $M \leq 5\,000$
---
- **Subtask  5 [ 5 punti]:** $N \leq 1\,000$, $M \leq 20\,000$
- **Subtask  6 [ 8 punti]:** $N \leq 10\,000$, $M \leq 20\,000$, la prima operazione di tipo $2$ avviene dopo l'ultima operazione di tipo $1$
- **Subtask  7 [ 12 punti]:**  la prima operazione di tipo $2$ avviene dopo l'ultima operazione di tipo $1$
---
- **Subtask  8 [ 20 punti]:** è garantito che al momento di ogni richiesta, nel sottointervallo specificato non siano mai presenti due $1$ consecutivi
- **Subtask  9 [ 15 punti]:** il sottointervallo di ogni query è sempre $[0,N-1]$
- **Subtask  10 [ 15 punti]:** nessuna limitazione
---

## Esempio di input/output

| input from stdin                                                  | &nbsp;&nbsp;&nbsp;&nbsp; | output to stdout |
| ----------------                                                  | ------------------------ | ---------------- |
| 3 7<br>1 0<br>1 2<br>1 1<br>2 0 2<br>1 1<br>2 0 2<br>2 1 2        | &nbsp;                   | 1<br>2<br>1      |
| &nbsp;                                                            | &nbsp;                   | &nbsp;           |
| 10 10<br>2 0 9<br>1 5<br>1 6<br>1 2<br>2 1 7<br>1 1<br>1 1<br>1 3<br>1 6<br>2 0 8                              | &nbsp;                  | 0<br>2<br>2      |
| &nbsp;                                                            | &nbsp;                   | &nbsp;           |
<!-- ## Note -->
