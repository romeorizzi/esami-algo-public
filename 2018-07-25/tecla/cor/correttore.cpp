/* correttore oddcycle
   Romeo 2017-03-15
   last updated: 2018-07-15, portato da 30 a 1000000 nodi e da C a c++
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <vector>

#define  MAXN   1000000

int N, M, L;
std::vector<int> adj[MAXN];

int areAdj(int u, int v) {
  for(int i = 0; i < adj[u].size(); i++)
    if(adj[u][i] == v)
      return 1;
  return 0;
}  

void ex( char *msg, float res ) {
   if (msg) fprintf(stderr, "%s\n", msg);

   printf("%f\n", res);

   exit(0);
}


int main(int argc, char *argv[]) {
  FILE *in, *rif, *an;

  if ( argc != 4 ){
    fprintf( stderr, "usage: %s input correct_answ user_answ\n", argv[0]);
    return -100000;
  }

  /* input */
  in = fopen( argv[1], "r");
  if ( in == NULL )
    ex("File di input mancante\n", 0.0);
  
  /* correct answer */
  rif = fopen( argv[2], "r");
  if ( rif == NULL)
    ex("File con output di riferimento mancante\n", 0.0);

  /* user answer */
  an = fopen( argv[3], "r");
  if ( an == NULL )
    ex("Output errato.", 0.0);


  /* Lettura parametri dell'input */
  if( fscanf(in, "%d", &N) != 1) ex("File di input errato.", 0.0);
  if( fscanf(in, "%d", &M) != 1) ex("File di input errato.", 0.0);
  for (int i=0; i<M; i++) {
    int a, b;
    if( fscanf(in, "%d %d", &a, &b) != 2) ex("File di input errato.", 0.0);
    adj[a].push_back( b );
    adj[b].push_back( a );
  }

  /* Lettura output da validare */

  if( fscanf(an, "%d", &L) != 1) ex("Output errato.", 0.0);
  int u,v;
  if( fscanf(an, "%d", &u) != 1) ex("Output errato.", 0.0);
  if( u != 0 ) ex("Output errato: non parte da 0.", 0.0);
  for(int i=0; i < L; i++) {
    if( fscanf(an, "%d", &v) != 1) ex("Output errato.", 0.0);
    if( (v < 0) || (v >= N ) )
        ex("Output errato: nodo non esistente.", 0.0);
    if( ! areAdj(u, v) )
      ex("Output errato: filamento non esistente.", 0.0);
    u = v;
  }
  if( v != 0 ) ex("Output errato: non finisce con 0.", 0.0);

  if( L % 2 == 0) ex("Output errato: ritorno con BLEACH.", 0.0);

  ex("Output corretto.", 1.000);

  return 0;
}
