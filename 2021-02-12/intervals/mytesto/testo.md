## Massimo numero di intervalli mutualmente disgiunti (intervals)

Il vostro lavoro è l'animatore turistico. Le agenzie viaggi hanno già buttato fuori il calendario delle loro offerte.
Ogni offerta prevede una vacanza articolata su un certo numero di giorni consecutivi (magari anche uno solo). Volete individuare il massimo numero di viaggi che siano mutualmente compatibili, ossia che non si sovrappongano nemmeno per un singolo giorno.

Con le agenzie di viaggio abbiamo anche un altro contratto: siamo noi che prepariamo il calendario per esporlo al pubblico in veste grafica. Vogliamo assegnare un colore ad ogni viaggio in modo che ogni due viaggi che si sovrappongano abbiano colore diverso. Due viaggi potranno avere lo stesso colore solo se mutualmente compatibili.

Assumiamo che $K$ sia il numero di giorni nel calendario (numerati da $0$ a $K-1$), che $N$ sia il numero di intervalli in input. Invece $T=0,1$ è il paramtro che viene dato per primo: esso vi consente di distinguere tra i due diversi task.

Le prime due istanze d'esempio (la prima con $T=0$ e la seconda con $T=1$) si riferiscono entrambe allo stesso insieme di intervalli che incontri nel problema di Zio Paperone che, partito per un viaggio di $K=8$ giorni, con partenza il giorno $0$ e ritorno il giorno $K-1=7$, non vuole però lasciare il deposito incostudito e ha quindi raccolo le seguenti disponibilità di amici e parenti alla sorveglianza (per ogni nome si indica l'intervallo di disponibilità).

- Paperino $[3,5]$
- Paperoga $[0,2]$
- Battista $[1,3]$
- Gastone $[5,6]$
- Archimede $[4,7]$

In realtà, tutte le istanze sono in comune tra i due problemi di questo appello.
Il parametro $X$ che compare nella definizione dei subtask rappresenta pertanto il numero di quei giorni che non ricadono in nessuno degli $N$ intervalli forniti in input. 

## Input

L'input avviene da `stdin` e consta di $3+N$ righe. La prima riga contiene l'intero $T$ che specifica la richiesta, come spiegato sopra.
La seconda riga contiene il numero di giorni $K$, la terza il numero di proposte di vacanza, ognuna rappresentata come un'intervallo di giorni. Le restanti $N$ righe contengono una coppia ordinata di interi $A$ e $B$, con $A\leq B$; la riga $3+i$ rappresenta l’intervallo $[A_i,B_i]$ della $i$-esima vacanza.

In realtà, tutte le istanze sono in comune tra i due problemi di questo appello.
Il parametro $X$ che compare nella definizione dei subtask rappresenta pertanto il numero di quei giorni che non ricadono in nessuno degli $N$ intervalli forniti in input.

## Output

L'output avviene su `stdout` e consiste di un solo numero intero:

- se $T=0$ si ritorni il massimo numer di intervalli mutualmente disgiunti e presenti nella famiglia di intervalli data in input.
- Se $T=1$ si ritorni il minor numero di colori necessario per colorare tutti gli intrvalli in modo che ogni due intervalli che ricomprendano uno stesso giorno abbiano colori diversi.

## Assunzioni

- $2 \leq K \leq 100\,000\,000$
- $2 \leq N \leq 100\,000$
- Per ognuna delle $N$ righe si ha $0 \leq A \leq B \leq K-1$. Nel caso $A=B$ la disponibilità è di un solo giorno mentre in generale è di $B-A+1$ giorni.

## Esempi

| 0<br>8<br>5<br>3 5<br>0 2<br>1 3<br>5 6<br>4 7         | &nbsp;   | 2 <br><br><br><br><br><br><br><br><br><br><br><br><br> |
| 1<br>8<br>5<br>3 5<br>0 2<br>1 3<br>5 6<br>4 7         | &nbsp;   | 3 <br><br><br><br><br><br><br><br><br><br><br><br><br> |
| 1<br>10<br>6<br>2 5<br>0 2<br>1 3<br>5 6<br>4 7<br>7 9 | &nbsp;   | 3 <br><br><br><br><br><br><br><br><br><br><br><br><br> |
| 1<br>9<br>6<br>2 5<br>0 2<br>1 3<br>5 6<br>4 7<br>2 2  | &nbsp;    | 4 <br><br><br><br><br><br><br><br><br><br><br><br><br> |

### Subtask
- **Subtask  1 [10 punti]**: risolvere correttamente gli 11 casi d'esempio forniti in attachment (i primi quattro sono quelli del testo).
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
