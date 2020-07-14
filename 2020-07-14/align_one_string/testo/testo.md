# Allineamento per pompaggio di una stringa ad una stringa target (align\_one\_string)

## Descrizione del problema

Sia $\Sigma$ l'alfabeto dei 26 caratteri dell'alfabeto inglese maiuscolo, dalla A (ASCII 65) alla Z (ASCII 90). Sia $\Sigma'$ l'alfabeto ottenuto da $\Sigma$ aggiungendogli, come ventisettesimo carattere, il simbolo `*` (ASCII 45). Per ogni  coppia di caratteri $\{c_1,c_2\}$ in $\Sigma'$ vale il predicato di compatibilità $is$\_$comp(c_1,c_2)$ che è vero precisamente quando $c_1=c_2$, oppure $c_1=$`*`, oppure $c_2=$`*`. Il predicato $is$\_$comp(c_1,c_2)$ è invece falso se e solo se $c_1,c_2\in \Sigma$ con $c_1$ diverso da $c_2$.

Per ogni carattere $c\in \Sigma'$ e numero naturale $\delta$, indichiamo con $rep(c,\delta)$ la stringa composta da $\delta$ caratteri $c$.


In questo problema sono date 2 stringhe $a$ e $b$ di lunghezza $m$ ed $n\leq m$, entrambe sull'alfabeto $\Sigma'$. Viene inoltre fornito un numero intero positivo $p$ e un vettore $cost$ di lunghezza $p+1$, dove, per ogni intero $i\in [0,\ldots,p]$, $cost[i]$ è un intero non-negativo che specifica il costo di andare ad inserire un run $rep($*$,i)$ di $i$ caratteri * consecutivi entro una qualsivoglia stringa in una qualsivoglia posizione (è garantito che $cost[0] \geq 0$).
Viene richiesto di produrre, partendo da $b$, una stringa $b'$ di lunghezza $m$ sull'alfabeto $\Sigma'$, e tale che $is$\_$comp(b'_i,a_i)$ sia vero per ogni $i=1,2,\ldots, m$. La stringa $b'$ deve essere ottenuta partendo dalla stringa $b$ come segue:


1. $b' := b$
2. finchè $len(b') < m$:
3.  - seleziona un numero intero positivo $\delta \leq m-len(b')$
4.  - paga alla cassa $cost[\delta]$
5.  - inserisci la stringa $rep($*$,\delta)$ in una qualsiasi posizione della attuale stringa $b'$.
   

L'obiettivo è minimizzare la somma dei costi pagati alla cassa. 


Esempio:
a: asdfdsdff
b: asdf
cost: 0 1 3 3 2 8 6 7

in questo caso si hanno molte possibilità (forse ce ne sono anche altre):
```
ASDFDSDFF
ASDF*****
costo = 8 (con un gap da 5) o ad esempio 6 (con un gap da 2 e uno da 3). 
Ci possono essere più combinazioni di gap piccoli che danno un gap più grande ad un costo inferiore.
```
```
ASDFDSDFF
AS**D***F
costo = 3+3 (per il costo di un gap da 2 e uno da 3) = 6
```
```
ASDFDSDFF
AS****D*F
costo = 3 (un gap da 4 e uno da 1)
```

Il minimo costo totale da pagare è pertanto 3, ed è questo che ti chiediamo di computare.

## File di input

Il programma deve leggere da `stdin`.  
Nella prima riga sono presenti gli interi $m$, $n$ e $p$ separati da uno spazio.
Nella secoda riga è presente la stringa $a$ di lunghezza $m$.
Nella terza riga è presente la stringa $b$ di lunghezza $n$.
Nella quarta riga sono riportati, ordinatamente, i $p+1$ valori che compongono il vettore $cost$.

## File di output

Il programma deve scrivere su `stdout`.
Scrive $-1$ se partendo da $b$ non è possibile ottenere un $b'$ per inserimento di caratteri jolly * e tale che ogni carattere di $b'$ sia compatibile al rispettivo carattere in $a$.
Altrimenti, scrivere il minimo costo totale da pagare alla cassa per ottenere, partendo da $b$, un tale $b'$ compatibile con $a$ nel senso sopra definito.

## Assunzioni

* $1 \leq m,n,p \leq 1\,000$
* $cost[i] \leq 10\,000$ per ogni $i=1,\ldots,p$
* $cost[0] = 0$

## Subtask

- **Subtask  1 [ 2 punti]:** casi di esempio
---
- **Subtask  2 [ 5 punti]:** $m \leq 10$
- **Subtask  3 [ 6 punti]:** $m \leq 15$
- **Subtask  4 [11 punti]:** $m \leq 20$
---
- **Subtask  5 [21 punti]:** $p=2$
---
- **Subtask  6 [30 punti]:** $a=rip(A,999)Z$, $b=Z$
---
- **Subtask  7 [25 punti]:** $m,n,p \leq 1\,000$

## Esempio di input/output

| input from stdin                                                 | &nbsp;&nbsp;&nbsp;&nbsp; | output to stdout |
| -------------  | ------------- |        --- |
| 8 4 7 <br> ASDFDSDF <br> ASDF <br> 0 1 3 3 2 8 6 7           | &nbsp;                   | 2 |

| input from stdin                                                 | &nbsp;&nbsp;&nbsp;&nbsp; | output to stdout |
| -------------  | ------------- |        --- |
| 7 2 5 <br> ABCDEFG <br> AA <br> 0 1 1 1 1 1           | &nbsp;                   | -1 |

