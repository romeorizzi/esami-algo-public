/* correttore tower_of_hanoi_pancakes
   Romeo 2018-07-16
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

#define  MAXN   1000000

int N;
int flip[MAXN+1]; // tutto numerato partendo da 1
long long int n_moves_declared, n_moves_rif;
int n[4], peg[4][MAXN+1]; // tutto numerato partendo da 1


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
    ex("Output errato. Non riesco ad aprire il file.", 0.0);


  /* Lettura parametri dell'input */
  if( fscanf(in, "%d", &N) != 1) ex("File di input errato.", 0.0);
  n[1] = N; n[2] = n[3] = 0;
  for (int i=1; i<=N; i++) {
    peg[1][N-i+1] = i; // tutto numerato partendo da 1
    if( fscanf(in, "%d", &flip[i]) != 1) ex("File di input errato.", 0.0);
  }

  /* Lettura parziale dell'output di riferimento */
  fscanf(rif, "%lld", &n_moves_rif);

  /* Lettura output da validare */

  if( fscanf(an, "%lld", &n_moves_declared) != 1) ex("Output errato. Deve iniziare dichiarando il numero di mosse.", 0.0);
  //printf("%lld\n", n_moves_declared);
  int disk, peg_from, peg_to;
  for(int i=0; i < n_moves_declared; i++) {
    //format: "Muovi il disco %d dal piolo %d al piolo %d" 
    if( fscanf(an, "%*s %*s %*s %d", &disk) != 1) ex("Output errato. Attendevo numero identificativo di disco.", 0.0);
    //printf(" %d\n", disk);
    
    if(0 >= disk || disk > N)
        ex("Output errato: i dischi sono numerati da 1 a N.", 0.0);

    if( fscanf(an, "%*s %*s %d", &peg_from) != 1) ex("Output errato. Attendevo numero di piolo da cui prelevare il disco.", 0.0);
    //printf(" %d\n", peg_from);

    if( fscanf(an, "%*s %*s %d", &peg_to) != 1) ex("Output errato. Attendevo numero di piolo dove riporre il disco.", 0.0);
    //printf(" %d\n", peg_to);
    
    if(0 >= peg_from || peg_from > 3   ||   0 >= peg_to || peg_to > 3)
        ex("Output errato: i possibili pioli sono numerati da 1 a 3.", 0.0);
    if(peg_from == peg_to)
        ex("Output errato: non puoi muovere un disco da un piolo al piolo stesso. In ogni tua mossa dovresti avere peg_from <> peg_to.", 0.0);
    if( peg[peg_from][n[peg_from]] != disk )
        ex("Output errato: il disco non si trova in cima al piolo da cui chiedi di spostarlo.", 0.0);
    if( n[peg_to] > 0 && peg[peg_to][n[peg_to]] < disk )
        ex("Output errato: chiedi di muovere il disco sopra un disco piu piccolo.", 0.0);
    n[peg_from]--;
    flip[disk] = 1 - flip[disk];
    n[peg_to]++;
    peg[peg_to][n[peg_to]] = disk;
  }
  
  if( n[3] < N) ex("Output errato: alla fine della sequenza di mosse prescritta i dischi non sono tutti sul piolo 3.", 0.0);

  for (int i=1; i<=N; i++) {
    if( flip[i] != 0)  ex("Output errato: alla fine della sequenza di mosse una frittella non resta correttamente flippata.", 0.0);
  }

  if(n_moves_declared == n_moves_rif)  
     ex("Output corretto e sequenza di mosse ottima.", 1.000);
  else if(n_moves_declared > n_moves_rif)  
     ex("Output corretto ma esistono soluzioni in meno mosse.", 0.500);
  else
     ex("Output corretto. Soluzione SUPEROTTIMA (migliore della nostra di riferimento)!!!", 3.000);
  
  return 0;
}
