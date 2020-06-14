# Le righe che iniziano con # sono commenti.
# La stringa ***sezione*** indica l'inizio di una nuova sezione.
# Le sezioni devono essere sempre presenti tutte, l'ordine non conta ma è
# meglio se sono nell'ordine: variables, prototypes, calls, input, output


***variables***
int N
int M
int A[M]
int B[M]
int P[M]
int C[N-1]
int D[N-1]
int minimo


***prototypes***
int mst(int N, int M, int A[], int B[], int P[], int C[], int D[])

***calls***
minimo = mst(N, M, A, B, P, &C, &D)

***input***
N M
A[] B[] P[]

***output***
minimo
C[] D[]
