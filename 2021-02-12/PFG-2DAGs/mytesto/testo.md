# Due giocatori avanzano due pedine in due DAGs (PFG\_2DAGs)

Sono dati due grafi diretti ed aciclici $D_1=(V_1,A_1)$ e $D_2=(V_2,A_2)$. Per $i=1,2$, una pedina $p_i$ è collocata su un nodo in $V_i$.
Due giocatori giocano a turno e il primo che non può muovere perde. Per muovere si deve scegliere un $i=1,2$ e un arco $(u,v)\in A_i$ uscente dal nodo $u$ di $D_i$ in cui è attualmente collocata la pedina $p_i$. La mossa consiste nel prendere la pedina $p_i$ e spostarla dal nodo $u$ al nodo $v$.
Poiché ad ogni mossa una delle due pedine "avanza" in uno dei due DAG (Directed Acyclic Graph) il gioco è destinato a terminare e si classifica come un PFG (Progressively Finite Game). Le possibili posizioni del gioco corrispondono alle coppie di nodi in $V_1\times V_2$.

Ricevi in input i due grafi e $p$ coppie $(v_1,v_2)\in V_1\times V_2$: per ognuna di esse devi dire se quella posizione di gioco è una "chi tocca vince" oppure una "chi tocca perde".

## Input:

Da `stdin`. Prima viene specificato il primo DAG, poi il secondo, infine la sequenza delle coppie.
Per specificare un DAG $D_i=(V_i,A_i)$, su una prima riga sono dati i numeri $n_i:=|V_i|$ e $m_i:=|A_i|$, separati da spazio. Seguono poi $m_i$ righe, ciascuna codifica un diverso arco $(u,v)\in A_i$ con due interi (le etichette di $u$ e di $v$ in questo ordine) separati da spazio. I nodi si assumono etichettati coi numeri da $0$ a $n_i-1$.
Per specificare la sequenza di posizioni, su una prima riga si dà $p$, e poi, sulle $p$ righe successive, si specificano una ad una le $p$ posizioni di gioco da valutare. Ciascuna di esse è una coppia ordinata $V_1\times V_2$ che, di nuovo, codifichiamo con le due etichette dei nodi separate da spazio. 

## Output:

Su `stdout` si scriveranno $p$ numeri, uno per riga. Essi corrispondono, anche nell'ordine, alle posizioni specificate nelle ultime $p$ righe dell'input. Si riporterà un $1$ in corrispondenza di una posizione "chi tocca vince" ed uno $0$ per le posizioni "chi tocca perde".

## Esempi

| input from `stdin` | &nbsp;&nbsp;&nbsp;&nbsp; | output to `stdout` |
| ------------------ | ------------------------ | ------------------ |
| 6 8<br>0 1<br>0 1<br>2 5<br>1 2<br>2 3<br>3 4<br>4 5<br>1 5<br>6 7<br>0 1<br>2 3<br>2 5<br>3 4<br>3 5<br>1 2<br>4 5<br>4<br>5 0<br>1 5<br>2 2<br>5 5 | &nbsp;                   | 1<br>1<br>0<br>0<br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br> |
| 5 6<br>3 2<br>4 2<br>4 2<br>4 2<br>0 4<br>1 2<br>5 7<br>0 4<br>3 4<br>0 4<br>3 2<br>0 2<br>1 2<br>4 2<br>6<br>1 1<br>3 4<br>2 3<br>4 3<br>3 2<br>0 2 | &nbsp;                   | 0<br>0<br>1<br>1<br>1<br>0<br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br> |




## Assunzioni:
- $2 \leq n_1, n_2, p \leq 10\,000$.
- $m_1 \leq 10\,n_1$, $m_2 \leq 10\,n_2$.

### Subtask
- **Subtask  1 [10 punti]**: risolvere correttamente i 10 casi d'esempio forniti in attachment (i primi due sono quelli del testo).
---
- **Subtask  2 [ 8 punti]**: $n_1=1$, $n_2, p \leq 10$. ($m1=0$, $m2 \leq 100$.)
- **Subtask  3 [ 8 punti]**: $n_1=1$, $n_2, p \leq 30$. ($m1=0$, $m2 \leq 300$).
- **Subtask  4 [ 9 punti]**: $u<v$ per ogni $(u,v) \in A_1 \cup A_2$. Moreover, $n_1=1$, $n_2, p \leq 500$. ($m1=0$, $m2 \leq 5000$).
- **Subtask  5 [ 9 punti]**: $u<v$ per ogni $(u,v) \in A_1 \cup A_2$, $n_1=1$, $n_2, p \leq 10\,000$. ($m1=0$, $m2 \leq 100\,000$).
---
- **Subtask  6 [ 7 punti]**: $u<v$ per ogni $(u,v) \in A_1 \cup A_2$, $n_1, n_2, p \leq 10$. ($m1,m2 \leq 100$).
- **Subtask  7 [ 7 punti]**: $u<v$ per ogni $(u,v) \in A_1 \cup A_2$, $n_1, n_2, p \leq 30$. ($m1,m2 \leq 300$).
- **Subtask  8 [ 7 punti]**: $u<v$ per ogni $(u,v) \in A_1 \cup A_2$, $n_1, n_2, p \leq 500$. ($m1,m2 \leq 5000$).
- **Subtask  9 [ 7 punti]**: $u<v$ per ogni $(u,v) \in A_1 \cup A_2$, $n_1, n_2, p \leq 10\,000$. ($m1,m2 \leq 100\,000$).
---
- **Subtask  10 [7 punti]**: $n_1, n_2, p \leq 10$. ($m1,m2 \leq 100$).
- **Subtask  11 [7 punti]**: $n_1, n_2, p \leq 30$.  ($m1,m2 \leq 300$).
- **Subtask  12 [7 punti]**: $n_1, n_2, p \leq 500$. ($m1,m2 \leq 5000$).
- **Subtask  13 [7 punti]**: $n_1, n_2, p \leq 10\,000$. ($m1,m2 \leq 100\,000$).

