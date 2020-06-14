/*
  Flavio Chierichetti
  Pirellone
  
  Non testato completamente.
*/

#include <stdio.h>
/*#define STDIO*/

int N, M, B;
int **F;

int main(int argc, char *argv[]) {
  FILE *in, *out;

  int i, j;
  
  int impossible;

#ifdef STDIO
  in = stdin;
  out = stdout;
#else
  in = fopen("input.txt", "r");
  out = fopen("output.txt", "w");
#endif

  fscanf(in, " %d %d %d", &N, &M, &B);

  F = (int**) calloc(N, sizeof(int*));
  
  for ( i = 0 ; i < N ; i++ ) {
    F[i] = (int*) calloc(M, sizeof(int));

    for ( j = 0 ; j < M ; j++ )
      fscanf(in, " %d", F[i] + j);
  }

  /* Partiamo ottimisti... */
  impossible = 0;

  /* Sulle colonne spingiamo un interrutore se e 
     solo se la finestra relativa sulla prima riga
     e` accesa.
     Tutte le finestre sulla prima riga saranno quindi 
     spente.

     Il vettore d'uso degli interruttori colonna sara` F[0].
     Inoltre non useremo il primo interruttore riga.

     In generale, per conoscere lo stato della finestra (i, j)
     dopo aver eseguito le commutazioni colonna potremo eseguire:
     (F[i][j] != F[0][j])
  */

  for ( i = 1 ; i < N ; i++ ) {
    /* Se la prima finestra della riga i-esima e` accesa
       non possiamo non premere l'interruttore di quella
       riga. Vale anche il viceversa. */

    for ( j = 0 ; j < M ; j++ )
      /* Se lo stato della finestra (i, j) e` diverso dallo
	 stato della (i, 0): non c'e` niente da fare. */
      if ( (F[i][j] != F[0][j]) != (F[i][0] != F[0][0]) )
	impossible = 1;
  }

  if ( !impossible ) {
    /* Riga 0: spenta */
    fprintf(out, "%d ", 0);

    /* Righe 1...N : accese se e solo se la loro prima finestra
       e` accesa */
    for ( i = 1 ; i < N ; i++ )
      fprintf(out, "%d ", F[i][0] != F[0][0]);

    fprintf(out, "\n");

    /* Colonne 0...N : accese se e solo se la relativa finestra
       alla riga 0 e` accesa */
    for ( j = 0 ; j < M ; j++ )
      fprintf(out, "%d ", F[0][j]);

    fprintf(out, "\n");
  } else {
    /* Stampiamo solo zeri */
    for ( i = 0 ; i < N ; i++ )
      fprintf(out, "%d ", 0);
    fprintf(out, "\n");

    for ( j = 0 ; j < M ; j++ )
      fprintf(out, "%d ", 0);
    fprintf(out, "\n");
  }

  return 0;
}
