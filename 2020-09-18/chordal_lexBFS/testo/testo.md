# Grafi Cordali: lexBFS, riconoscimento, Max Cliques e colorings (chordal\_lexBFS)

E' dato un grafo connesso $G=(V,E)$ i cui $n$ nodi sono i numeri interi da $1$ ad $n$.
Il primo goal è stabilire se una visita lexBFS di $G$ possa visitarne i nodi nell'ordine da $1$ ad $n$.
Una [visita lexBFS](https://en.wikipedia.org/wiki/Lexicographic_breadth-first_search) di un grafo ne visita i nodi uno ad uno, facendo ogni volta attenzione a visitare uno di quei nodi maggiormente attratti dai nodi già visitati, dove un nodo attrae solamante i suoi vicini e la forza di attrazione di un nodo è incomparabilmente maggiore a quella di ogni nodo che lo segua nell'ordinamento.
Pertanto, ciascun nodo del grafo potrà essere il primo nodo ad essere visitato. Se etichettiamo con $1$ il primo nodo visitato, seguiranno prima tutti i vicini del nodo $1$ e solo poi quei nodi che non sono invece vicini di $1$. E queste due epoche in serie sono di nuovo entrambe suddivise in una prima sotto-epoca che ricomprende i nodi adiacenti al nodo $2$ ed una seconda sotto-epoca dove nessun nodo è adiacente al nodo $2$. E così via per ogni altro nodo $i$ fino ad $n$.
Dovete quindi confermare che l'ordine dei nodi da $1$ ad $n$ è lexBFS oppure ritornare tre nodi $j$, $i$ e $j'$, con $j'$ vicino di $j$ ma non di $i$, con $j'<i<j$, e tali che per ogni $i'$ vicino di $i$ ma non di $j$ valga $i'>j'$. Se ve ne sono, di tutte tali triple $(j,i,j')$ vi chiediamo di ritornare quella lessicograficamente minima.

Un grafo si dice _cordale_ se in esso ogni ciclo di lunghezza almeno $4$ ha almeno una corda (ossia i triangoli siano gli unici cicli a comparire come sottografi indotti). Rimandiamo alla [pagina di Wikipedia](https://en.wikipedia.org/wiki/Chordal_graph) già segnalata prima dell'esame per maggiori informazioni sulle proprietà algoritmiche di questi grafi.

Un _buco_ di $G$ è un ciclo di lunghezza almeno $4$ ma privo di corde.
Un ordinamento dei nodi di $G$ è detto un _perfect elimination scheme_ se ogni due nodi adiacenti ad uno stesso nodo che li precede entrambi nell'ordinamento sono tra di loro adiacenti.
Si noti che se $C$ è un ciclo di $G$ e $v$ è il minor nodo di $C$ in un perfect elimination scheme di $G$ allora il nodo $x$ che precede $v$ in $C$ ed il nodo $y$ che segue $v$ in $C$ devono essere vicini, e questo arco $xy$ è una corda di $C$.
Come secondo goal, siete chiamati a realizzare una procedura efficiente che risponda alla seguente definizione a black-box:

> __input:__ un grafo connesso $G=(V,E)$ dove l'ordinamento dei nodi da $1$ ad $n$ sia lexBFS.
__output:__ precisamente uno dei seguenti due oggetti: 
> 1. se l'ordinamento $n$ $n-1$ $\cdots$ $2$ $1$ è un perfect di $G$ si ritorni esso come certificato di cordalità di $G$.
> 2. altrimenti, un buco di $G$, come certificato di NON cordalità di $G$. In realtà ti chiediamo di ritornare solamente il più piccolo $i$ tale che il grafo indotto $G[\{1,2,\ldots,i\}]$ contiene un buco.

Una _clique_ di $G$ è un sottoinsieme $C\subseteq V$ di nodi tale che ogni due nodi in $C$ sono adiacenti in $G$ ($\forall u,v\in C$, $uv \in E$). Il parametro $\omega(G)$ indica la massima cardinalità di una clique di $G$ ed il suo computo è un importante problema NP-completo per grafi generici.
Un $k$-_coloring_ di $G$ è un mapping $c:V\mapsto \{1,\ldots, k\}$ che assegna un colore $c(v)$ ad ogni nodo $v$ di $G$, col vincolo che se due nodi sono adiacenti allora devono ricevere colori diversi ($\forall uv \in E$, $c(u)\neq c(v)$). Il parametro $\chi(G)$ indica il minimo $k$ per cui $G$ ammette un $k$-coloring. Il computo di $\chi(G)$ è un importante problema NP-completo per grafi generici.
Si noti che se $Q$ è una clique di un grafo $k$-colorabile allora $k\geq |Q|$, ossia $\chi(G) \geq \omega(G)$ vale per ogni grafo $G$. E' noto che nei grafi cordali questi due parametri si eguagliano fornendo buona caratterizzazione per entrambi questi importanti problemi di ottimizzazione combinatoria. E' quanto andate a dimostrare next, dove siete chiamati a realizzare una procedura efficiente che risponda alla seguente definizione a black-box:


> __input:__ un grafo connesso $G=(V,E)$ dove l'ordinamento dei nodi da $1$ ad $n$ sia un perfect elimination scheme di $G$.
__output:__ uno dei seguenti tre a seconda del task:
> goal 3: il valore comune di $\chi(G)$ ed $\omega(G)$.
> goal 4: una clique di cardinalità $\omega(G)$, di tutte tali clique ti chiediamo di tornare quella clique $Q$ che massimizza $\min\{i \,: \, i\in Q\}$.
> goal 5: un $\chi(G)$-coloring di $G$, di tutti tali coloring ti chiediamo di tornare quel coloring $c$ che minimizza $\sum_{i\in V} c(i)n^{2i}$.



## Input:

Da `stdin`. La prima riga contiene gli interi $g$, $n := |V|$ ed $m := |E|$, separati da spazio. Assumeremo che gli $n$ nodi di $G$ siano rappresentati dagli $n$ numeri naturali da $1$ ad $n$. Il parametro intero $t\in \{1,2,3,4,5\}$ indica il tipo di goal.
Le successive $m$ righe codificano ciascuna un diverso arco di $G$. La codifica di un arco $uv$ riporta i due nodi $u$ e $v$ a capo dell'arco (due interi nell'intervalo $[1,n]$ e separati da spazio).


## Output:

Su `stdout`.
Se $g=1$, nella prima riga si scriva $1$ se l'ordine dei nodi da $1$ ad $n$ è lexBFS, altrimenti si scriva $0$ e si offra, su una seconda riga, la tripla $(j,i,j')$ lessicograficamente minima.
Se $g=2$ è dato sapere dall'inizio che l'ordinamento da $1$ ad $n$ è lexBFS, ed abbiamo due possibilità: se l'ordinamento rovesciato da $n$ ad $1$ è un perfect elimination scheme di $G$ allora si ritorni esso come certificato di cordalità di $G$. In pratica stampiamo $n$ $n-1$ $\cdots$ $2$ $1$ sulla seconda riga, in questo ordine e separati da spazio.
Nel secondo caso, si ritorni il più piccolo $i$ tale che il grafo indotto $G[\{1,2,\ldots,i\}]$ contiene un buco.
Se $g=3,4$ o $5$ è dato sapere dall'inizio che l'ordinamento da $1$ ad $n$ è un perfect elimination scheme, e quindi $\omega(G)=\chi(G)$. Nella prima riga si ritorni questo numero intero a doppia valenza.
Se $g=3$ non serve scrivere altro.
Se $g=4$ si ritorna una seconda riga che riporta separati da spazio ed in ordine crescente i nodi della clique Q con $|Q|=\omega(G)$ e per la quale sia massimo il funzionale $\min\{i \,: \, i\in Q\}$.
Se $g=5$ la seconda riga riporta invece, separati da spazio e nell'ordine, gli $n$ valori $c(1)$ $c(2)$ $\cdots$ $c(n)$ che esplicano il $\chi(G)$-coloring $c$ di $G$ che minimizza $\sum_{i\in V} c(i)n^{2i}$.



## Esempi

Trovi delle coppie input/output d'esempio nei file in attachment.


## Assunzioni:
- the graph $G$ is connected
- $1 \leq n \leq 10\,000$
- $0 \leq m \leq 200\,000$

## Nota:
  Tra gli attachments trovate coppie input/output d'esempio per ciascuno dei diversi subtask.

### Subtask
- **Subtask  1 [ 10 punti]**: $g=1$, $n\leq 100$, $m\leq 1000$.
- **Subtask  2 [ 10 punti]**: $g=1$, $n\leq 10\,000$, $m\leq 200\,000$.
---
- **Subtask  3 [ 10 punti]**: $g=2$, $n\leq 100$, $m\leq 1000$.
- **Subtask  4 [ 10 punti]**: $g=2$, $n\leq 10\,000$, $m\leq 200\,000$.
---
- **Subtask  5 [ 10 punti]**: $g=3$, $n\leq 100$, $m\leq 1000$.
- **Subtask  6 [ 10 punti]**: $g=3$, $n\leq 10\,000$, $m\leq 200\,000$.
---
- **Subtask  7 [ 10 punti]**: $g=4$, $n\leq 100$, $m\leq 1000$.
- **Subtask  8 [ 10 punti]**: $g=4$, $n\leq 10\,000$, $m\leq 200\,000$.
---
- **Subtask  9 [ 10 punti]**: $g=5$, $n\leq 100$, $m\leq 1000$.
- **Subtask 10 [ 10 punti]**: $g=5$, $n\leq 10\,000$, $m\leq 200\,000$.
