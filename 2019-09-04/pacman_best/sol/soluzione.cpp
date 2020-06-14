/**
 *  File: soluzione.cpp
 *  Soluzione di pacman_best
 *
 *  Autore: Romeo Rizzi, 2019-08-26
 *
 */

#include <cassert>
#include <cstdio>

const int DEBUG = 0;

const int MAXBLUE = 9;
const int MAXM = 100;
const int MAXN = 100;

char mappa[2][MAXN+1]; /* lavoriamo su una mappa estesa da una prima riga e colonna (quelle di indice 0) che sono integralmente costituite di muro. Le righe e colonne della mappa originale sono riportate integralmente partendo da riga e colonna 1.
In principio il dimensionamento avrebbe dovuto quindi essere:
   char mappa[MAXM+1][MAXN+1];
ma vogliamo sfruttare l'osservazione che per risolvere il problema basta lavorare su due righe alla volta. */

int DPexists[2][MAXN+1][MAXBLUE+2];
int DPghosts[2][MAXN+1][MAXBLUE+2];
int DPpills[2][MAXN+1][MAXBLUE+2];
/* In principle 1: the DP matrix should have been dimensioned as:
   int DP[MAXM+1][MAXN+1][MAXBLUE+2];
where DP[i][j][b] = best value of a path starting from cell mappa[1][1] and arriving to cell mappa[i][j] with b units of residual blue (can still eat b ghosts after leaving cell mappa[i][j] without encountering any pills)
   In principle 2: the path might not exists and, when it exists, its value is a pair: first comes the number of ghosts captured that we try to maximize as our first priority, then the number of pill cells visited that we try to minimize as our second priority.
   To manage 2: we prefer to have three DP matrices. 
   Concerning 1:  since in computing one row we need only entries from the current or previous row, and we are in need to spare memory, our DP process will work on just two rows:
      DP[i%2][j][b] = DP[i][j][b]
*/

int M, N;

int main() {
    scanf("%d%d", &M, &N); if(DEBUG) fprintf(stderr,"M=%d, N=%d\n", M, N); 

    int max_ghosts = 0, min_pills;
    
    for (int j = 0; j <= M; j++)
      mappa[0][j] = '#';

    for (int i = 1; i <= M; i++) {
      mappa[i%2][0] = '#';
      for (int j = 1; j <= N; j++) {
	do { 
	  scanf("%c", &mappa[i%2][j]);
	} while(mappa[i%2][j] != '#' && mappa[i%2][j] != '+' && mappa[i%2][j] != '*' && ( mappa[i%2][j] < '1' || mappa[i%2][j] > '9')  );
        if(DEBUG) fprintf(stderr, "mappa[%d,%d]=%c\n", i, j, mappa[i%2][j]);
	if( (i==1) && (j==1) ) {
	  min_pills = 0;
	  if(mappa[1][1] == '+') {
	    DPexists[1][1][0] = 1; // the rest is all initialized to 0 since DP is a global variable
	    DPghosts[1][1][0] = 0;
            DPpills[1][1][0] = 0;
	  } else {
	    min_pills = 1;
	    DPexists[1][1][mappa[1][1]-'0'] = 1; // the rest is all initialized to 0 since DP is a global variable
	    DPghosts[1][1][mappa[1][1]-'0'] = 0;
            DPpills[1][1][mappa[1][1]-'0'] = 1;
	  }
        }
        else {
	  for(int b = 0; b <= MAXBLUE; b++) {
	    DPexists[i%2][j][b] = 0;
	    DPghosts[i%2][j][b] = 0;
	    DPpills[i%2][j][b] = MAXM+MAXN; 
	  }
	  switch (mappa[i%2][j]) {
	    case '#': 
	    break;
     
	    case '+': 
	    for(int b = 0; b < MAXBLUE; b++) {
	      if(DPexists[(i-1)%2][j][b+1] == 1) {
		DPexists[i%2][j][b] = 1;
	        DPghosts[i%2][j][b] = DPghosts[(i-1)%2][j][b+1];
                DPpills[i%2][j][b] = DPpills[(i-1)%2][j][b+1];
	      }
	      if(DPexists[i%2][j-1][b+1]) {
		DPexists[i%2][j][b] = 1;
		if( (DPghosts[i%2][j-1][b+1] >= DPghosts[i%2][j][b]) && ( (DPghosts[i%2][j-1][b+1] > DPghosts[i%2][j][b]) || (DPpills[i%2][j-1][b+1] < DPpills[i%2][j][b]) ) ) {	
		  DPghosts[i%2][j][b] = DPghosts[i%2][j-1][b+1];
		  DPpills[i%2][j][b] = DPpills[i%2][j-1][b+1];
		}
	      }
            }
	    if(DPexists[(i-1)%2][j][0]) {
	      DPexists[i%2][j][0] = 1;
	      if( (DPghosts[(i-1)%2][j][0] >= DPghosts[i%2][j][0]) && ( (DPghosts[(i-1)%2][j][0] > DPghosts[i%2][j][0]) || (DPpills[(i-1)%2][j][0] < DPpills[i%2][j][0]) ) ) {	
	        DPghosts[i%2][j][0] = DPghosts[(i-1)%2][j][0];
                DPpills[i%2][j][0] = DPpills[(i-1)%2][j][0];
	      }
	    }
	    if(DPexists[i%2][j-1][0]) {
	      DPexists[i%2][j][0] = 1;
	      if( (DPghosts[i%2][j-1][0] >= DPghosts[i%2][j][0]) && ( (DPghosts[i%2][j-1][0] > DPghosts[i%2][j][0]) || (DPpills[i%2][j-1][0] < DPpills[i%2][j][0]) ) ) {	
	        DPghosts[i%2][j][0] = DPghosts[i%2][j-1][0];
                DPpills[i%2][j][0] = DPpills[i%2][j-1][0];
	      }
	    }
	    break;
     
	    case '*': 
	    DPexists[i%2][j][MAXBLUE] = 0;
	    for(int b = 0; b < MAXBLUE; b++) {
	      if(DPexists[(i-1)%2][j][b+1]) {
		DPexists[i%2][j][b] = 1;
		DPghosts[i%2][j][b] = DPghosts[(i-1)%2][j][b+1] +1;
		DPpills[i%2][j][b] = DPpills[(i-1)%2][j][b+1];
	      }
	      if(DPexists[i%2][j-1][b+1]) {
		DPexists[i%2][j][b] = 1;
		if( (DPghosts[i%2][j-1][b+1] +1 >= DPghosts[i%2][j][b]) && ( (DPghosts[i%2][j-1][b+1]+1 > DPghosts[i%2][j][b]) || (DPpills[i%2][j-1][b+1] < DPpills[i%2][j][b]) ) ) {	
		  DPghosts[i%2][j][b] = DPghosts[i%2][j-1][b+1] +1;
		  DPpills[i%2][j][b] = DPpills[i%2][j-1][b+1];
		}
	      }
            }
	    break;
     
	    default:
	    int blue = mappa[i%2][j] - '0';
	    for(int b = blue+1; b < MAXBLUE; b++) {
	      if(DPexists[(i-1)%2][j][b+1]) {
		DPexists[i%2][j][b] = 1;
		DPghosts[i%2][j][b] = DPghosts[(i-1)%2][j][b+1];
		DPpills[i%2][j][b] = DPpills[(i-1)%2][j][b+1] +1;
	      }
	      if(DPexists[i%2][j-1][b+1]) {
		DPexists[i%2][j][b] = 1;
		if( (DPghosts[i%2][j-1][b+1] >= DPghosts[i%2][j][b]) && ( (DPghosts[i%2][j-1][b+1] > DPghosts[i%2][j][b]) || (DPpills[i%2][j-1][b+1] +1 < DPpills[i%2][j][b]) ) ) {	
		  DPghosts[i%2][j][b] = DPghosts[i%2][j-1][b+1];
		  DPpills[i%2][j][b] = DPpills[i%2][j-1][b+1] +1;
		}
	      }	      
	    }
	    for(int b = 0; b < blue; b++) {
	      DPexists[i%2][j][b] = 0;
	    }	    
	    DPexists[i%2][j][blue] = 0;
	    DPghosts[i%2][j][blue] = 0;
	    DPpills[i%2][j][blue] = MAXM+MAXN; 
	    for(int b = 0; b <= blue+1; b++) if(b <= MAXBLUE) {
	      if(DPexists[(i-1)%2][j][b]) {
		DPexists[i%2][j][blue] = 1;
		if( (DPghosts[(i-1)%2][j][b] >= DPghosts[i%2][j][blue]) && ( (DPghosts[(i-1)%2][j][b] > DPghosts[i%2][j][blue]) || (DPpills[(i-1)%2][j][b] +1 < DPpills[i%2][j][blue]) ) ) {	
		  DPghosts[i%2][j][blue] = DPghosts[(i-1)%2][j][b];
		  DPpills[i%2][j][blue] = DPpills[(i-1)%2][j][b] +1;
		}
	      }
	      if(DPexists[i%2][j-1][b]) {
		DPexists[i%2][j][blue] = 1;
		if( (DPghosts[i%2][j-1][b] >= DPghosts[i%2][j][blue]) && ( (DPghosts[i%2][j-1][b] > DPghosts[i%2][j][blue]) || (DPpills[i%2][j-1][b] +1 < DPpills[i%2][j][blue]) ) ) {	
		  DPghosts[i%2][j][blue] = DPghosts[i%2][j-1][b];
		  DPpills[i%2][j][blue] = DPpills[i%2][j-1][b] +1;
		}
	      }
	    }
	  }
	  for(int b = 0; b <= MAXBLUE; b++) { 
	    if( (DPexists[i%2][j][b]) && (DPghosts[i%2][j][b] >= max_ghosts) && ( (DPghosts[i%2][j][b] > max_ghosts) || (DPpills[i%2][j][b] < min_pills) ) ) {	
	      max_ghosts = DPghosts[i%2][j][b];
	      min_pills = DPpills[i%2][j][b];
	    }
  
	    if(DEBUG) 
	      fprintf(stderr, "[i=%d, j=%d, b=%d]: DPexists = %d, DPghosts = %d, DPpills = %d\n", i, j, b, DPexists[i%2][j][b], DPghosts[i%2][j][b], DPpills[i%2][j][b]); 
          } 
	}
      } // for j
    } // for i

    int exists = 0, max_ghosts_exists = 0, min_pills_exists = MAXM+MAXN;
    for(int b = 0; b <= MAXBLUE; b++)
      if(DPexists[M%2][N][b]) {
	exists = 1;
	if( (DPghosts[M%2][N][b] >= max_ghosts_exists) && ( (DPghosts[M%2][N][b] > max_ghosts_exists) || (DPpills[M%2][N][b] < min_pills_exists) ) ) {	
	  max_ghosts_exists = DPghosts[M%2][N][b];
	  min_pills_exists = DPpills[M%2][N][b];
	}
      }
    if(exists)
      printf("1 %d %d\n",max_ghosts_exists,min_pills_exists);
    else
      printf("0 %d %d\n",max_ghosts,min_pills);
    
    return 0;
}
