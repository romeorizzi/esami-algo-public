/**
 *  File: sol_wrong_late_mod.cpp
 *  Soluzione di pacman che va in overflow perchè computa il mod solo alla fine
 *
 *  Autore: Romeo Rizzi, 2018-09-25
 *
 */

#include <cassert>
#include <cstdio>

const int DEBUG = 0;

const int BASE = 1000000;
const int MAXBLUE = 5;
const int MAXM = 500;
const int MAXN = 500;

char mappa[MAXM+1][MAXN+1]; /* lavoriamo su una mappa estesa da una prima riga e colonna (quelle di indice 0) che sono integralmente costituite di muro. Le righe e colonne della mappa originale sono riportate integralmente partendo da riga e colonna 1. */
int num[MAXM+1][MAXN+1][MAXBLUE+1];
// in principle: num[i][j][b] = number of paths starting from cell mappa[1][1] and arriving to cell mappa[i][j] with b units of residual blue (can still eat b ghosts after leaving cell mappa[i][j] without encountering any pills)

int M, N;

int main() {
#ifdef EVAL
    assert( freopen("input.txt", "r", stdin) );
    assert( freopen("output.txt", "w", stdout) );
#endif
    scanf("%d%d", &M, &N);
    if(DEBUG) fprintf(stderr,"M=%d, N=%d\n", M, N); 
	
    for (int j = 0; j <= M; j++)
      mappa[0][j] = '#';
      
    for (int i = 1; i <= M; i++) {
      mappa[i][0] = '#';
      for (int j = 1; j <= N; j++) {
	do { 
	  scanf("%c", &mappa[i][j]);
	} while(mappa[i][j] != '#' && mappa[i][j] != '+' && mappa[i][j] != '*' && ( mappa[i][j] < '1' || mappa[i][j] > '5')  );
        if(DEBUG) fprintf(stderr, "mappa[%d,%d]=%c\n", i, j, mappa[i][j]); 
	if( (i==1) && (j==1) ) {
	  if(mappa[1][1] == '+')
	    num[1][1][0] = 1; // the rest is all initialized to 0 since num is a global variable
	  else
	    num[1][1][mappa[1][1]-'0'] = 1; // the rest is all initialized to 0 since num is a global variable
        }
        else {	
	  switch (mappa[i][j]) {
	  case '#': 
	    for(int b = 0; b <= MAXBLUE; b++)
	      num[i][j][b] = 0;
	    break;
     
	  case '+': 
	    num[i][j][MAXBLUE] = 0;
	    for(int b = 0; b < MAXBLUE; b++)
	      num[i][j][b] = num[i-1][j][b+1] + num[i][j-1][b+1];
	    num[i][j][0] = num[i][j][0] + num[i-1][j][0] + num[i][j-1][0];
	    break;
     
	  case '*': 
	    num[i][j][MAXBLUE] = 0;
	    for(int b = 0; b < MAXBLUE; b++)
	      num[i][j][b] = num[i-1][j][b+1] + num[i][j-1][b+1];
	    break;
     
	    default:
	    int blue = mappa[i][j] - '0';
	    for(int b = 0; b < blue; b++) {
	      num[i][j][b] = 0;
	    }	    
	    num[i][j][MAXBLUE] = 0;
	    for(int b = blue+1; b < MAXBLUE; b++) {
	      num[i][j][b] = num[i-1][j][b+1] + num[i][j-1][b+1];
	    }
	    num[i][j][blue] = 0;
	    for(int b = 0; b <= blue+1; b++) if(b <= MAXBLUE) {
	      num[i][j][blue] = num[i][j][blue] + num[i-1][j][b] + num[i][j-1][b];
	    }
	  }
	}
	if(DEBUG) 
	  for(int b = 0; b <= MAXBLUE; b++) 
	    fprintf(stderr, "num[i=%d, j=%d, b=%d] = %d\n", i, j, b, num[i][j][b]); 
      }
    }  

    int risp = 0;
    for(int b = 0; b <= MAXBLUE; b++)
      risp = (risp + num[M][N][b]) % BASE;
    printf("%d\n",risp);
    return 0;
}
