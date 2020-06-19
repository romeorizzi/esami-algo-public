# Riempimenti di uno heap binario (bin\_heap\_fill)

Le$~n$ celle di un array$~A$ sono numerate da$~0$ a$~n-1$. Il _binary heap_ sovraimposto su$~A$ guarda a tali celle come ai nodi di un _albero binario_ (ossia dove ogni nodo ha al massimo due figli) la cui radice è la cella$~0$ ed ogni cella$~i$ ha come suo _figlio sinistro_ la cella$~2i+1$ e come suo _figlio destro_ la cella$~2(i+1)$. Ovviamente non appena$~2i+1$ e$~2(i+1)$ dovessero eccedere$~n-1$ il figlio in questione semplicemente non esiste.

![Figura: Lo heap binario quarda alle celle di un array come ai nodi di un albero binario](figs/bin_heap_array_correspondence.png)

I possibili collocamenti di$~n$ valori numerici$~x_0, \ldots, x_{n-1}$ entro le$~n$ celle di$~A$ sono$~n!$ se gli$~n$ valori da collocare sono tutti diversi, e  meno di$~n!$ altrimenti. In particolare, vi è un solo modo di riempire A qualora$~x_0=x_1=\ldots=x_{n-1}$. Esso è dato da$~A[i] = x_0$ per ogni $i=0,1,\ldots,n-1$.

Dato un sottoinsieme $E$ di$~\{1,\ldots,n-1\}$, un collocamento$~A$ è detto$~E$_-buono_ se soddisfa la seguente proprietà:

> __heap-property(__$E$__):__ $\;A[i] \geq A[(i-1)/2]\,$ per ogni $i \in E$.

Nota: quando$~E=\{1,\ldots,n-1\}$ la _heap-property_$(E)$ si traduce nella _classica proprietà di buon ordinamento di uno heap_ secondo cui il valore immagazzinato nel generico nodo$~i$, $i>0$, non deve mai essere inferiore al valore immagazzinato nel rispettivo padre$~((i-1)/2)$. (Questo garantisce che il valore collocato nella radice sia un minimo, cosa che viene sfruttata per reperire rapidamente la prossima cosa da fare in una Event Driven Simulation.)

Dato un collocamento iniziale$~A$ ed un _insieme di posizioni fisse_$~F\subseteq \{0,1,\ldots,n-1\}$, un _ricollocamento $F$-stabile_ di$~A$ è un collocamento$~A'$ tale che$~A'[i]=A[i]$ per ogni$~i=0,1,\ldots,n-1$.

Sono due i diversi obiettivi generali che dovrai porti a seconda del subtask:

1. decidere se il collocamento iniziale$~A$ assegnato sia$~E$-buono;
2. decidere se esista un ricollocamento$~F$-stabile di$~A$ che sia$~E$-buono.

A prescindere da quale dei due sia l'obiettivo dell'istanza, per praticità ti forniremo sempre e comunque un collocamento iniziale$~A$, un insieme di posizioni fisse$~F$, ed un _insieme di figli esuberanti_$~E$. 

Riguardo all'obiettivo$~2$ ricevi già i tuoi punti dal sistema di correzione automatica e contestuale se componi e sottometti un codice che, in qualche modo, decide correttamente. Se riesci a fare questo per istanze non piccole significa che hai messo il problema di decisione in P, e quindi esiste di certo una buona caratterizzazione di questa proprietà che in realtà devi avere già acquisito (se ti illudi di poter procedere oltre senza prima averla conquistata e non ne sei consapevole rischi allora di sciupare del tuo tempo sull'obiettivo$~2$ di questo esercizio). Ti invitiamo a congetturare la forma di questa buona caratterizzazione partendo dal caso in cui$~F$ sia vuoto, dove essa è banale.

<img src="figs/helping_hand.png" alt="Procediamo insieme!" style="width:30px;"/></a> Ti invitiamo in particolare a
<a href="mailto:romeo.rizzi@univr.it?cc=andrea.cracco@studenti.univr.it&subject=Buone%20Caratterizzazioni%20per%20il%20problema%20bin_heap_fill%20in%20esame%20Algoritmi%202020-06-30&body=NOTA:%20SE%20VUOI%20CHE%20QUESTA%20MAIL%20CONTRIBUISCA%20AI%20TUOI%20PUNTI%20ESAME%20RICORDATI%20DI%20INVIARLA%20DA%20TUO%20INDIRIZZO%20UNIVR%20E%20SPECIFICA%20LA%20TUA%20MATRICOLA.%0D%0A%0D%0AMATRICOLA:%20VR???%0D%0A%0D%0ABuona%20Congettura%20nel%20caso%20generale:%0D%0A%0D%0A%20%20%20***TO%20DO%20STATEMENT***%0D%0A%0D%0ADimostrazione:%0D%0A%0D%0A%20%20%20***TO%20DO%20PROOF***%0D%0A%0D%0ABuona%20Congettura%20nel%20caso%20particolare%20con%20F%20vuoto:%0D%0A%0D%0A%20%20%20***TO%20DO%20STATEMENT***%0D%0A%0D%0ADimostrazione:%0D%0A%0D%0A%20%20%20***TO%20DO%20PROOF***%0D%0A%0D%0ABuona%20Congettura%20nel%20caso%20particolare%20con%20E%20=%20%7b1%2c%2e%2e%2e%2cn%2d1%7d:%0D%0A%0D%0A%20%20%20***TO%20DO%20STATEMENT***%0D%0A%0D%0ADimostrazione:%0D%0A%0D%0A%20%20%20***TO%20DO%20PROOF***%0D%0A%0D%0A">Scriverci una mail utilizzando questo template</a><a href="mailto:romeo.rizzi@univr.it?cc=andrea.cracco@studenti.univr.it&subject=Buone%20Caratterizzazioni%20per%20il%20problema%20bin_heap_fill%20in%20esame%20Algoritmi%202020-06-30&body=NOTA:%20SE%20VUOI%20CHE%20QUESTA%20MAIL%20CONTRIBUISCA%20AI%20TUOI%20PUNTI%20ESAME%20RICORDATI%20DI%20INVIARLA%20DA%20TUO%20INDIRIZZO%20UNIVR%20E%20SPECIFICA%20LA%20TUA%20MATRICOLA.%0D%0A%0D%0AMATRICOLA:%20VR???%0D%0A%0D%0ABuona%20Congettura%20nel%20caso%20generale:%0D%0A%0D%0A%20%20%20TO%20DO%20STATEMENT%0D%0A%0D%0ADimostrazione:%0D%0A%0D%0A%20%20%20TO%20DO%20PROOF%0D%0A%0D%0ABuona%20Congettura%20nel%20caso%20particolare%20con%20F%20vuoto:%0D%0A%0D%0A%20%20%20TO%20DO%20STATEMENT%0D%0A%0D%0ADimostrazione:%0D%0A%0D%0A%20%20%20TO%20DO%20PROOF%0D%0A%0D%0ABuona%20Congettura%20nel%20caso%20particolare%20con%20E%20=%20%7b1%2c%2e%2e%2e%2cn%2d1%7d:%0D%0A%0D%0A%20%20%20TO%20DO%20STATEMENT%0D%0A%0D%0ADimostrazione:%0D%0A%0D%0A%20%20%20TO%20DO%20PROOF%0D%0A%0D%0A">Scriverci una mail utilizzando questo template</a>
e contenente espressione chiara di tale congettura ed eventuale sua dimostrazione (puoi congetturarla più o meno in generale e dimostrarla in casi particolari, anche quì suggeriamo di procedere con gradualità).
Se il link sopra non dovesse funzionare correttamente sul tuo sistema, ricopia allora da <a href="template_mail_builder/template_mail_buona_congettura.md">questo template</a> per impostare correttamente la tua mail.
Ovviamente se dai una dimostrazione generale chiara non ti serve dare anche la dimostrazione del caso particolare, ma non omettere di coniugare nei vari casi particolari gli statements perchè ti permetterà di essere più preciso nell'esprimere ciò che pensi e potrà consentire un feedback più efficace da parte nostra, agevolandoci significativamente e consentendoci di attribuirti ogni competenza compiutamente dimostrata.
Fino a dove ci sarà possibile, cercheremo di rispondere a queste mail durante lo svolgimento dell'esame, per convalidare quanto scrivi oppure cassarlo (daremo max 3 controesempi per studente, se ci riusciremo, cercando di servire prima chi ha già ricevuto meno aiuto).

<b>Anche questa mail (solo quella nella sua ultima versione inviataci entro la conclusione dell'esame), se conterrà cose di senno espresse in chiarezza e lucidità, aggiungerà punti anche significativi alla tua prova</b>.




<!--
![](figs/Binary_Heap_with_Array_Implementation.jpeg)
![](figs/File_Binary_tree_in_array.svg)
<img src="figs/File_Binary_tree_in_array.svg">
-->


## Input:

Da `stdin` ricevi, nell'ordine:
1. il parametro$~n$;
2. il parametro$~t=1,2$ che specifica quale degli obiettivi menzionati sopra vada conseguito in questa istanza;
3. gli$~n$ valori$~x_0, \ldots, x_{n-1}$ forniti nell'ordine come disposti nel collocamento iniziale$~A$;
4. una sequenza di$~n-1$ valori$~e_1, \ldots, e_{n-1}$ con$~e_i \in \{0,1\}$ per$~i=1,\ldots n-1$. Essi specificano $E$ nel senso che$~i \in E$ se e solo se$~e_i = 1$.
5. una sequenza di$~n$ valori$~f_0, \ldots, f_{n-1}$ con$~f_i \in \{0,1\}$ per$~i=0,\ldots n-1$. Essi specificano $F$ nel senso che$~i \in F$ se e solo se$~f_i = 1$. Per praticità ti forniremo questo dato in tutte le istanze, anche quelle dove$~t=1$.

## Output:

Il tuo programma deve scrivere su `stdout` quanto previsto a seconda dell'obiettivo:
-$~t=1$: deve scrivere$~1$ se il collocamento iniziale$~A$ è$~E$-buono, altrimenti deve scrivere$~0$;
-$~t=2$: deve scrivere$~1$ se esiste un ricollocamento$~F$-stabile di$~A$ che sia$~E$-buono, altrimenti deve scrivere$~0$;

## Esempi

| input from stdin                                          | &nbsp;&nbsp;&nbsp;&nbsp; | output to stdout |
| ----------------                                          | ------------------------ | ---------------- |
| 7 1<br>2 3 1 5 4 7 6<br>1 1 1 1 1 1 1<br>0 0 0 0 0 0 0    | &nbsp;                   | 0                |
| &nbsp;                                                    | &nbsp;                   | &nbsp;           |
| 7 1<br>2 3 1 5 4 7 6<br>1 1 0 1 1 1 1<br>0 0 0 0 0 0 0    | &nbsp;                   | 1                |
| &nbsp;                                                    | &nbsp;                   | &nbsp;           |
| 7 2<br>2 3 1 5 4 7 6<br>1 1 1 1 1 1 1<br>0 0 0 0 0 0 0    | &nbsp;                   | 1                |
  &nbsp;                                                    | &nbsp;                   | &nbsp;           |
| 7 2<br>2 3 1 5 4 7 6<br>1 1 1 1 1 1 1<br>1 0 0 0 0 0 0    | &nbsp;                   | 0                |

## Spiegazione casi d'esempio

Nel primo caso, $n=7$ e$~t=1$, quindi viene richiesto di controllare l'heap e potrei anche ignorare l'ultima riga (tutta di zeri). Il collocamento iniziale è quello che deve essere valutato. Esso ha posto un$~1$ nel nodo$~2$ e nel padre (il nodo$~0$) ha posto un valore più grande (un $2$). La risposta corretta è quindi~$0$. Infatti _heap-property_$(\{2\})$ non è soddisfatta e $2\in E$.  

Il secondo caso è identico al primo, eccetto che ora il nodo~$2$ non appartiene ad$~E$. Visto che ogni altro nodo$~i$ soddisfa la proprietà _heap-property_$(\{i\})$, la risposta corretta è~$1$.

Il terzo caso è di nuovo identico al primo, eccetto che pone l'obiettivo di tipo~$2$ (ora$~t=2$): si chiede ora se sia possibile riarrangiare gli elementi dello heap, mantenendo però fissi quelli nelle posizioni in~$F$, in modo da ottenere un collocamento $E$-buono. Non avendo elementi in $F$ (si veda l'ultima riga interamente di zeri),  
siamo liberi di riarrangiare gli elementi in qualunque modo, e semplicemente scambiando i valori contenuti nei nodi~$2$ e$~0$ otteniamo un collocamento $E$-buono. Perciò la risposta corretta è~$1$.

Il quarto caso è identico al terzo, eccetto che ora $F=\{0\}$. Non potendo spostare il valore $2$ dal nodo$~0$ non è possibile ottenere uno heap $E$-buono, perciò la risposta corretta è~$0$.


## Assunzioni:

- $~n$ è un numero intero compreso tra$~0$ e$~1\,000\,000$
- gli$~n$ valori$~x_0, \ldots, x_{n-1}$ sono tutti interi compresi tra$~0$ e$~10\,000\,000$


### Subtask
- **Subtask  0 [ 1 punto]**: risolvere correttamente i casi d'esempio quì sopra nel testo.
- **Subtask  1 [ 4 punti]**: $t=1$, $|F|=0$, $E=\{1,\ldots,n-1\}$.
- **Subtask  2 [ 5 punti]**: $t=1$, $|F|=0$, $E$ generico.
- **Subtask  3 [ 1 punti]**: $t=2$, $|F|=0$, $E=\{1,\ldots,n-1\}$.
--
- **Subtask  4 [5 punti]**: $t=2$, $|F|=1$, $E$ generico.
---
- **Subtask  5 [25 punti]**: $t=2$, $F$ generico, $E=\{1,\ldots,n-1\}$, $n \leq 1\, 000$.
- **Subtask  6 [30 punti]**: $t=2$, $F$ generico, $E=\{1,\ldots,n-1\}$.
---
- **Subtask  7 [30 punti]**: $t=2$, $F$ generico, $E$ generico.
