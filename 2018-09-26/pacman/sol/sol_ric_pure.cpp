/**
 *  File: sol_ric_pure.cpp
 *  Soluzione di pacman (ricorsione senza memoizzazione)
 *
 *  Autore: Romeo Rizzi, 2018-09-25
 *
 */

#include <cassert>
#include <cstdio>

const int BASE = 1000000;
const int MAXBLUE = 5;
const int MAXM = 500;
const int MAXN = 500;

char mappa[MAXM+1][MAXN+1];

int M, N;

int ric(int r, int c, int b) {
  // returns the number of paths starting from cell mappa[1][1] and arriving to cell mappa[i][j] with b units of residual blue (can still eat b ghosts after leaving cell mappa[i][j] without encountering any pills)

  if( r <= 0) return 0;  
  if( c <= 0) return 0;  
  if( b > MAXBLUE) return 0;  
  if( (r == 1) && (c == 1) ) {
    if(mappa[1][1] == '+') return (b==0) ? 1 : 0;  
    else return (b==(mappa[1][1]-'0')) ? 1 : 0;
  }  
  switch (mappa[r][c]) {
    case '#':
    return 0;
     
    case '+':
    if(b == MAXBLUE)
      return 0;
    if(b == 0)
      return (
	       ( ric(r-1,c,0) + ric(r,c-1,0) ) % BASE +
	       ( ric(r-1,c,1) + ric(r,c-1,1) ) % BASE
	      ) % BASE;
    return ( ric(r-1,c,b+1) + ric(r,c-1,b+1) ) % BASE;
     
    case '*': 
    if(b == MAXBLUE)
      return 0;
    return ( ric(r-1,c,b+1) + ric(r,c-1,b+1) ) % BASE;
     
    default:
    int blue = mappa[r][c] - '0';
    if(b < blue)
      return 0;
    if(b > blue) {
      if(b < MAXBLUE)
        return ( ric(r-1,c,b+1) + ric(r,c-1,b+1) ) % BASE;
      else
        return 0;
    }
    assert(b==blue);
    int risp = 0;
    for(int b = 0; b <= blue+1; b++)
      if(b <= MAXBLUE)
        risp = ( risp + ( ric(r-1,c,b) + ric(r,c-1,b) ) % BASE ) % BASE;
    return risp;
  }
}  


int main() {
#ifdef EVAL
    assert( freopen("input.txt", "r", stdin) );
    assert( freopen("output.txt", "w", stdout) );
#endif
    scanf("%d%d", &M, &N);

    for (int j = 0; j <= M; j++)
      mappa[0][j] = '#';
    for (int i = 1; i <= M; i++) {
      mappa[i][0] = '#';
      for (int j = 1; j <= N; j++) {
	do { 
	  scanf("%c", &mappa[i][j]);
	} while(mappa[i][j] != '#' && mappa[i][j] != '+' && mappa[i][j] != '*' && ( mappa[i][j] < '1' || mappa[i][j] > '5')  );
      }
    }  
    int risp = 0;
    for(int b = 0; b <= MAXBLUE; b++)
      risp = (risp + ric(M, N, b)) % BASE;
    printf("%d\n",risp);
    return 0;
}
