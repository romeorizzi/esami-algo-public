# Le somme di Poldo (poldo\_sums)

## Descrizione del problema

Poldo ha cominciato a frequentare la palestra ed ora si ritrova con due liste di numeri interi, della stessa lunghezza: $panino$ e $gym$, con gli indici che vanno da$~0$ a$~N-1$.
Poldo analizza pazientemente tutte le possibili sottosequenze della sequenza $0, 1,\ldots,N-1$ che elenca questi indici nel loro ordine naturale. 
Tra queste, ritiene _ammissibili_ quelle sequenze $s=s(0),s(1),\ldots,s(k)$ tali da rispettare l'equazione fondamentale della riconversione della panza in muscoli:

$panino[s(i)]\geq panino[s(i-1)]+\sum_{t=s(i-1)}^{s(i)-1} gym[t]$ 

che, si badi bene, deve valere per ogni$~i=1,\ldots,k$ affinchè il miracolo avvenga.
Ad esempio, se Poldo vuol prendere il panino in posizione $s(i-1)=3$ e poi il panino in posizione $s(i)=7$,
allora la condizione sopra si traduce in:

$panino[7]\geq panino[3]+\sum_{t=3}^{6} gym[t] = gym[3]+gym[4]+gym[5]+gym[6]$.


Poldo intende produrre una sequenza ammissibile della massima lunghezza possibile. Per questo ha deciso di ricorrere al suo informatico di fiducia.


## File di input

Il programma deve leggere da un file di nome `input.txt`.
Nella prima riga è presente un intero $N$, la lunghezza comune delle sequenze $panino$ e $gym$.
Le successive $N$ righe contengono due numeri interi ciascuna, e più precisamente: l'$i$-esima di queste righe contiene i numeri interi $panino[i]$ e $gym[i]$, in questo ordine e separati da spazio.

## File di output

Il programma deve scrivere in un file di nome `output.txt`.  
La prima riga deve contenere un intero $M$, la massima lunghezza possibile per una sequenza ammissibile. La seconda ed ultima riga deve contenere una sequenza ammissibile di lunghezza$~M$.

## Assunzioni

* $1 \leq N \leq 100\,000$
* $0 \leq panino[i] \leq 10\,000$
* $-1\,000 \leq gym[i] \leq 1\,000$

## Subtask

- **Subtask  1 [ 2 punti]:** casi di esempio.
---
- **Subtask  2 [ 5 punti]:** $N \leq 12$, $gym[i]=0$ per ogni$~i=0,\ldots,N-1$.
- **Subtask  3 [ 5 punti]:** $N \leq 12$, $gym[i]=1$ per ogni$~i=0,\ldots,N-1$.
- **Subtask  4 [ 5 punti]:** $N \leq 12$, $gym[i]\geq 0$ per ogni$~i=0,\ldots,N-1$.
---
- **Subtask  5 [ 9 punti]:** $N \leq 100$, $gym[i]=0$ per ogni$~i=0,\ldots,N-1$.
- **Subtask  6 [ 6 punti]:** $N \leq 100$, $gym[i]=5$ per ogni$~i=0,\ldots,N-1$.
- **Subtask  7 [ 6 punti]:** $N \leq 100$, $gym[i]\geq 0$ per ogni$~i=0,\ldots,N-1$.
---
- **Subtask  8 [ 6 punti]:** $N \leq 1000$, $gym[i]=0$ per ogni$~i=0,\ldots,N-1$.
- **Subtask  9 [ 9 punti]:** $N \leq 1000$, $gym[i]=8$ per ogni$~i=0,\ldots,N-1$.
- **Subtask 10 [ 6 punti]:** $N \leq 1000$, $gym[i]\geq 0$ per ogni$~i=0,\ldots,N-1$.
---
- **Subtask 11 [ 6 punti]:** $N \leq 100\,000$, $gym[i]=0$ per ogni$~i=0,\ldots,N-1$.
- **Subtask 12 [ 6 punti]:** $N \leq 100\,000$, $gym[i]=-3$ per ogni$~i=0,\ldots,N-1$.
- **Subtask 13 [ 9 punti]:** $N \leq 100\,000$, $gym[i]\geq 0$ per ogni$~i=0,\ldots,N-1$.
---
- **Subtask 14 [10 punti]:** $N \leq 100\,000$, $panino[i] = 0$ per ogni$~i=0,\ldots,N-1$.
- **Subtask 15 [10 punti]:** $N \leq 100\,000$.

## Esempio di input/output

| input from stdin                                                  | &nbsp;&nbsp;&nbsp;&nbsp; | output to stdout |
| ----------------                                                  | ------------------------ | ---------------- |
| 5<br>3 1<br>8 2<br>2 3<br>9 4<br>4 5                              | &nbsp;                   | 2<br>0 1         |
| &nbsp;                                                            | &nbsp;                   | &nbsp;           |
| 7<br>9 3<br>4 -8<br>2 7<br>8 0<br>4 -5<br>5 0<br>2 12             | &nbsp;                   | 3<br>1 2 5       |
| &nbsp;                                                            | &nbsp;                   | &nbsp;           |
| 10<br> 2748 283<br>4278 -2128<br>7332 332<br>0 -1<br>2833 0<br>10000 3218<br>1343 2222<br>23 8853<br>2223 3847<br>8479 -847                                                   | &nbsp;                   | 4<br>0 1 2 5   |

## Note
Ci possono essere più sequenze corrette. Nel file di output specificatene una (e una sola) qualsiasi.
Ad esempio, nella prima istanza sarebbero state accettate come ugualmente corrette anche le sequenze$0 3$ e$2 3$. Entrambe rispettano infatti l'equazione fondamentale della riconversione della panza in muscoli, e sono tutte della lunghezza massima possibile (ossia, propongono~$2$ elementi così come quella fornita nell'esempio.)  


