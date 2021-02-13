## Turni di guardia (turni. Preso e rivisto dalle selezioni Territoriali 2012)

La Banda Bassotti è stata rimessa in libertà. Zio Paperone, in partenza per un viaggio di $K$ giorni, ha la necessità di far sorvegliare il deposito: dovrà esserci sempre presente almeno una persona. Per risparmiare, chiede aiuto ad amici e parenti, e ognuno di questi fornisce un intervallo di giorni contigui in cui è disponibile per la sorveglianza gratuita. La prima questione è determinare i giorni su cui resta necessario prenotare un qualche servizio a pagamento. Poi però Paperone sà che dovrà fare un regalo a ognuna delle persone di cui accetterà la disponibilità, e, volendo risparmiare al massimo, intende anche quì minimizzarne il numero. In questo modo riuscirà a risparmiare anche sui regali.

Per esempio, se il viaggio di Zio Paperone è di $K=8$ giorni, con partenza il giorno $0$ e ritorno il giorno $K-1=7$, e con le seguenti disponibilità (per ogni nome si indica l'intervallo di disponibilità).

- Paperino $[3,5]$
- Paperoga $[0,2]$
- Battista $[1,3]$
- Gastone $[5,6]$
- Archimede $[4,7]$

In questo caso la disponibilità di amici e parenti è sufficiente a tenere il deposito sorvegliato su tutti e $8$ i giorni del viaggio. Inoltre, a Zio Paperone basta coinvolgere Paperoga, Paperino e Archimede per assicurarsi che il deposito sia sempre sorvegliato, e se la cava quindi con tre soli regali.

Sapendo il numero di giorni di viaggio, e le disponibilità di ognuno, il vostro compito è quello di aiutare Zio Paperone a calcolare i giorni in cui ricorrere ad una sorveglianza a pagamento e anche il minimo numero di regali.

## Input

L'input avviene da `stdin` e consta di $3+N$ righe. La prima riga contiene un intero $T$ che specifica la richiesta:
se $T=0$ allora vanno stabiliti i giorni sui quali occorre ricorrere alla sorveglianza a pagamento, altrimenti $T=1$ e la richiesta è di stabilire il minor numero di regali. La seconda riga contiene il numero di giorni $K$, la terza il numero di persone $N$ che hanno dato la loro disponibilità. Le restanti $N$ righe contengono una coppia ordinata di interi $A$ e $B$, con $A\leq B$; la riga $3+i$ rappresenta l’intervallo $[A_i,B_i]$ di disponibilità della $i$-esima persona.

## Output

L'output avviene su `stdout` e consiste di un solo numero intero:

- se $T=0$ si ritorni il minimo numero di giorni $X$ in cui ricorrere al servizio di soreveglianza a pagamento.
- Se $T=1$ si ritorni il minor numero di parenti $M$ da coinvolgere, senza però aumentare i giorni di sorveglianza a pagamento.

## Assunzioni

- $2 \leq K \leq 100\,000\,000$
- $2 \leq N \leq 100\,000$
- Per ognuna delle $N$ righe si ha $0 \leq A \leq B \leq K-1$. Nel caso $A=B$ la disponibilità è di un solo giorno mentre in generale è di $B-A+1$ giorni.

## Esempi

| 0<br>8<br>5<br>3 5<br>0 2<br>1 3<br>5 6<br>4 7         | &nbsp;   | 0 <br><br><br><br><br><br><br><br><br><br><br><br><br> |
| 1<br>8<br>5<br>3 5<br>0 2<br>1 3<br>5 6<br>4 7         | &nbsp;   | 3 <br><br><br><br><br><br><br><br><br><br><br><br><br> |
| 1<br>10<br>6<br>2 5<br>0 2<br>1 3<br>5 6<br>4 7<br>7 9 | &nbsp;   | 4 <br><br><br><br><br><br><br><br><br><br><br><br><br> |
| 1<br>9<br>6<br>2 5<br>0 2<br>1 3<br>5 6<br>4 7<br>2 2  | &nbsp;    | 3 <br><br><br><br><br><br><br><br><br><br><br><br><br> |

### Subtask
- **Subtask  1 [10 punti]**: risolvere correttamente i 11 casi d'esempio forniti in attachment (i primi quattro sono quelli del testo).
---
- **Subtask  2 [10 punti]**: $T=0$, $N, K \leq 100$.
- **Subtask  3 [10 punti]**: $T=0$, $N, K \leq 100\,000$.
- **Subtask  4 [10 punti]**: $T=0$, $N \leq 100\,000, K \leq 100\,000\,000$.
---
- **Subtask  5 [10 punti]**: $T=1$, $X=0$, $N, K \leq 100$.
- **Subtask  6 [10 punti]**: $T=1$, $X=0$, $N, K \leq 100\,000$.
- **Subtask  7 [10 punti]**: $T=1$, $X=0$, $N \leq 100\,000, K \leq 100\,000\,000$.
---
- **Subtask  8 [10 punti]**: $T=1$, $N, K \leq 100$.
- **Subtask  9 [10 punti]**: $T=1$, $N, K \leq 100\,000$.
- **Subtask 10 [10 punti]**: $T=1$, $N \leq 100\,000, K \leq 100\,000\,000$.
