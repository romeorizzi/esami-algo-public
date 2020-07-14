# analisi del gioco del triangolo (gioco\_triangolo)

Alle superiori, durante le ore più noiose, giocavamo tra compagni di banco tracciando su un foglio uno schizzo come questo:

| Configurazione <br> Iniziale |  Tweedledum esegue <br> la prima mossa  |  Tweedledee lo ha <br> già in pugno! |
|----------|:-------------:|------:|
| ![Figura: configurazione iniziale del gioco del triangolo](https://github.com/romeorizzi/esami-algo-public/raw/master/2020-07-14/gioco_triangolo/testo/figs/NimGame_matches.png) | ![Figura: configurazione iniziale del gioco del triangolo](https://github.com/romeorizzi/esami-algo-public/raw/master/2020-07-14/gioco_triangolo/testo/figs/NimGame_matches_1.png) | ![Figura: configurazione iniziale del gioco del triangolo](https://github.com/romeorizzi/esami-algo-public/raw/master/2020-07-14/gioco_triangolo/testo/figs/NimGame_matches_2.png) |

poi, a turno, tiravamo una riga orizzontale che tagliava un intervallo di fiammiferi contigui disposti su di una stessa riga.
Perdeva chi non poteva più muovere (la classica normal play condition).

Anche se al tempo non conoscevamo questa teoria e relative tassonomie, questo gioco imparziale offre esempio di un progressively finite game, poichè ad ogni mossa almeno un fiammifero viene spezzato (sul nostro foglio erano semplici linee verticali allineate come soldatini). Potrà sembrare che questo gioco sia esattamente il Nim (riguardando ogni riga come una diversa pila di Nim) ma invece non lo è perchè se in una mossa taglio un fiammifero $f$ ma non un qualche fiammifero $f_s$ alla sua sinistra nè un qualche fiammifero $f_d$ alla sua destra, tutti e $3$ contenuti nella stessa riga, in seguito non sarà più possibile tagliare sia $f_s$ che $f_d$ in una sola mossa.
La generica mossa taglia con un solo tratto un intervallo di fiammiferi che nella configurazione iniziale erano tutti consecutivamente disposti entro una stessa riga, ma sempre  rispettando la condizione che tutti i fiammiferi interessati dal taglio siano ancora integri quando esso viene tracciato. In questo modo gli intervalli massimali di fiammiferi non tagliati non solo si vedono strappare via degli elementi ma possono anche venire spezzati in due ad ogni mossa che li riguardi (succede quando tagliamo un intervallo $I$ di fiammiferi consecutivi che non includa nè il primo nè l'ultimo della riga e avendo ancora intatto il fiammifero che precede il primo e quello che segue l'ultimo di $I$: in questo gioco l'ordine dei fiammiferi è importante e i fiammiferi prima e dopo un fiammifero non cambiano mano a mano che dei fiammiferi vengono tagliati).
Una configurazione del gioco è quindi catturata dalla famiglia di intervalli massimali di fiammiferi consecutivi e non tagliati. Ma poichè di questi intervalli interessa solo il numero di elementi in essi contenuti, potremmo dire che una configurazione del gioco è una lista $L$ di numeri interi positivi e la mossa si svolge come segue:
1. si sceglie e rimuove un qualsiasi elemento $e$ della lista $L$.
2. Sia $x$ in numero che era immagazzinato in $e$. Se $x=1$ la mossa è finita. Altrimenti, se $x>1$ si sceglie quale delle seguenti due opzioni adottare, dove la seconda opzione è disponibile solo se $x>2$:
        $(a)$ si inserisce in $L$ un unico numero intero positivo $x'<x$;
        $(b)$ si inseriscono in $L$, come due elementi distinti, due interi positivi $x_1$ e $x_2$ con $x_1+x_2 < x$.

Anche nel Nim la generica configurazione del gioco può essere vista come una lista di numeri interi positivi, e la lista vuota è una configurazione di tipo "chi tocca perde", ma la differenza è che nel Nim non è disponibile l'opzione $(b)$.

Trovi tra gli attachments del problema <a href="attachments/pfg.pdf">una dispensa che introduce al Nim, offre strumenti per giocarlo ottimamente, e introduce il concetto di equivalenza tra due giochi</a>. E' il documento che avevo reso disponibile già tempo fà sul canale Telegram del corso. In questo esercizio imparerai a giocare ottimamente a Triangolo, eventualmente sfruttando quanto per il Nim già sai o puoi trovare nella dispensa. 

Ti converrà innanzitutto dimostrare che una qualsiasi lista $L$ di numeri interi positivi rappresenta una configurazione vincente del gioco Triangolo se e solo se rappresenta una configurazione vincente di Nim.
Vale anzi qualcosa di più forte: il valore di Grundy dei giochi $Tri(L)$ e $Nim(L)$ è lo stesso per ogni lista $L$.
In altre parole: $Tri(L)$ e $Nim(L)$ sono giochi equivalenti nel senso che aggiungere l'uno oppure l'altro su un nuovo tavolo di una somma di giochi non può comportare una differenza tra chi vince e chi perde. Questo fatto più generale sarà più accessibile da verificare (potere del pensiero ricorsivo) in quanto potremo quì avvalerci del criterio: due giochi $A$ e $B$ sono equivalenti se e solo se il gioco somma $A + B$ è "chi tocca perde".

Pertanto, per ottenere tutti questi risultati ed altre implicazioni ti basterà progettare ed esibire una tua contromossa vincente ad ogni possibile prima mossa nel gioco $Tri(L) + Nim(L)$. 

Una volta che avrai saputo fare questo (obiettivo $1$), dovrebbe venirti possibile giocare ottimamente a Triangolo sfruttando quanto già noto per il Nim (obiettivo $2$). 

Riguardo all'obiettivo $2$ puoi partire per esso anche subito, prendendo semplicemente per buona l'equivalenza che ti chiediamo di dimostrare con l'obiettivo $1$ e interpretando con coraggio cosa possa significare (le congetture sono profezie che si autorealizzano se solo si sà credere in esse nei modi opportuni).
Anche l'obiettivo $1$ può essere portato a casa (anzi nel modo più formale e concreto) semplicemente scrivendo il tuo codice.
Tuttavia vogliamo quì venirvi incontro consentendo ed anzi promuovendo che vi possiate esprimere anche in frasi (ma vi conviene siano concise e precise) sulle quali poter ottenere un grado contingentato di feedback umano (non sciupate queste cartucce).

<img src="https://github.com/romeorizzi/esami-algo-public/raw/master/2020-07-14/gioco_triangolo/testo/figs/helping_hand.png" alt="Procediamo insieme!" style="width:30px;"/></a> Ti invitiamo a 
<a href="mailto:romeo.rizzi@univr.it?cc=andrea.cracco@studenti.univr.it&subject=Dimostrazione%20che%20T(M)+N(M)%20è%20persa.%20Problema%20gioco_triangolo%20in%20esame%20Algoritmi%202020-06-30&body=NOTA:%20SE%20VUOI%20CHE%20QUESTA%20MAIL%20CONTRIBUISCA%20AI%20TUOI%20PUNTI%20ESAME%20RICORDATI%20DI%20INVIARLA%20DA%20TUO%20INDIRIZZO%20UNIVR%20E%20SPECIFICA%20LA%20TUA%20MATRICOLA.%0D%0A%0D%0AMATRICOLA:%20VR??????%0D%0A%0D%0ACome%20compongo%20la%20mia%20contromossa%20se%20l'avversario%20gioca%20la%20sua%20prima%20mossa%20sul%20tavolo%20del%20Nim:%0D%0A%0D%0ATO%20DO%20DESCRIZIONE%20CONTROMOSSA%0D%0A%0D%0ACome%20argomentare%20che%20la%20contromossa%20proposta%20è%20vincente:%0D%0A%0D%0ATO%20DO%20I%20TUOI%20ARGOMENTI%0D%0A%0D%0ACome%20compongo%20la%20mia%20contromossa%20se%20l'avversario%20gioca%20la%20sua%20prima%20mossa%20sul%20tavolo%20del%20Triangolo:%0D%0A%0D%0ATO%20DO%20DESCRIZIONE%20CONTROMOSSA%0D%0A%0D%0ACome%20argomentare%20che%20la%20contromossa%20proposta%20è%20vincente:%0D%0A%0D%0ATO%20DO%20I%20TUOI%20ARGOMENTI%0D%0A%0D%0A">scriverci una mail utilizzando questo template</a>
e contenente espressione chiara di quale sia la tua contro-mossa vincente in tutti i casi che possano presentarsi al tavolo.
Se il link sopra non dovesse funzionare correttamente sul tuo sistema, ricopialo allora da <a href="https://github.com/romeorizzi/esami-algo-public/tree/master/2020-07-14/gioco_triangolo/testo/template_mail_builder/template_mail_buona_congettura.md">questo template</a> per impostare correttamente la tua mail.
Fino a dove ci sarà possibile, cercheremo di rispondere a queste mail durante lo svolgimento dell'esame, per convalidare quanto scrivi oppure cassarlo (daremo max 3 controesempi per studente, se ci riusciremo, cercando di servire prima chi ha già ricevuto meno aiuto).

<b>Qualora il tuo codice non dovesse, per qualsivoglia ragione, consegnarti i punti in palio sull'obbiettivo $1$, prenderemo in considerazione anche questa mail (solo quella nella sua ultima versione inviataci entro la conclusione dell'esame). Se essa conterrà cose di senno espresse in chiarezza e lucidità, potrà recuperare in tutto od in parte i punti in palio sull'obbiettivo $1$</b>.


## Input:

Da `stdin` ricevi, nell'ordine:
1. il parametro _$t=1,2$_ che specifica quale degli obiettivi menzionati sopra vada conseguito in questa istanza;
2. la lunghezza $n$ della lista $L$;
3. gli $n$ numeri interi positivi $x_1,\ldots,x_n$ disposti in $L$;
4. descrizione di una mossa nel gioco $Tri(L) + Nim(L)$, ossia, nell'ordine: un carattere in $\{"T","N"\}$ che specifica il tavolo su cui la mossa ha deciso di operare, un intero $x\in L$ che specifica su quale elemento di $L$ la mossa opera, ed una coppia di interi non-negativi $y_1$ e $y_2$ con $y_1+y_2 < x$ che, ove positivi, vanno a rimpiazzare $x$ nella lista $L$ per produrre la lista $L'$ che và a sostituirsi ad $L$ nel tavolo su cui la mossa opera. Per praticità ti forniremo questa mossa in tutte le istanze, anche quelle dove $t=2$.
Nota 1: le mosse di tipo (a) sul tavolo "T" possono così trovare codifica in mosse con $y_2=0$. (Ed anche le mosse sul tavolo "N" sono ovviamente passibili di questa stessa rappresentazione.)
Gli input da noi erogati rispettano un'ulteriore regola interna secondo cui $y_1=0$ tutte le volte che $y_2=0$, ma non richiediamo in alcun modo che tu debba ottemperare a questa regola nei tuoi output.
Nota 2: gli input da noi erogati rispettano la separazione in righe che vedi negli esempi del testo.

## Output:

Il tuo programma deve scrivere su `stdout` quanto previsto a seconda dell'obiettivo:
- $t=1$: deve scrivere la contro-mossa vincente, ossia la specifica di tavolo in $\{"T","N"\}$, un intero $x$ in $L$ (oppure in $L'$, qualora si sia deciso di rispondere sullo stesso tavolo scelto dal primo giocatore), ed una coppia di interi non-negativi $y_1$ e $y_2$ come ampiamente spiegato sopra nello specificare l'input.
- $t=2$: deve scrivere $0$ se la posizione $Tri(L)$ è di tipo "chi tocca perde", altrimenti deve scrivere $1$ e poi restituire mossa vincente nel gioco $Tri(L)$ secondo il formato specificato sopra (impiegando necessariamente la "T").
Nota: i tuoi output non sono tenuti a rispettare la separazione in righe che vedi negli esempi del testo: ovviamente i vari elementi mandati su `stdout` dovranno essere separati, ma tratteremo in modo equivalente un fine riga oppure una sequenza di uno o più spazi). Ti sarà inoltre consentito proporre $y_2=0$ pur con $y_1>0$.

## Esempi

| input from `stdin`         | &nbsp;&nbsp;&nbsp;&nbsp; | output to `stdout`    |
| --------------------------- | ------------------------ | --------------------- |
| 1 2<br>1 2<br>N 2 0 0       | &nbsp;                   | T 2 0 0               |
| &nbsp;                      | &nbsp;                   | &nbsp;                |
| 2 2<br>1 2<br>N 2 0 0       | &nbsp;                   | 1<br>T 2 1 0          |
| &nbsp;                      | &nbsp;                   | &nbsp;                |
| 1 3<br>1 2 3<br>T 3 1 1     | &nbsp;                   | T 2 1 0               |
| &nbsp;                      | &nbsp;                   | &nbsp;                |
| 2 3<br>1 2 3<br>T 3 1 1     | &nbsp;                   | 0                     |


## Assunzioni:

- $n$ è un numero intero compreso tra $0$ e $100\,000$
- gli $n$ valori in $L$ sono tutti interi compresi tra $0$ e $100\,000$


### Subtask
- **Subtask  1 [ 1 punto]**: risolvere correttamente i casi d'esempio quì sopra nel testo.
- **Subtask  2 [ 2 punti]**: $t=1$, $n=1$.
- **Subtask  3 [ 2 punti]**: $t=2$, $n=1$.
---
- **Subtask  4 [15 punti]**: $t=1$, $n=2$.
- **Subtask  5 [10 punti]**: $t=2$, $n=2$.
---
- **Subtask  6 [15 punti]**: $t=1$, $n=3$.
- **Subtask  7 [10 punti]**: $t=2$, $n=3$.
---
- **Subtask  8 [15 punti]**: $t=1$, $n\leq 100$.
- **Subtask  9 [10 punti]**: $t=2$, $n\leq 100$.
---
- **Subtask 10 [10 punti]**: $t=1$.
- **Subtask 11 [10 punti]**: $t=2$.
