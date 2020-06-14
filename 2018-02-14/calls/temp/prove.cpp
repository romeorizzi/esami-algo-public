/**
 *  Elaborazioni e test relativi al problema calls
 *
 *  Autore: Romeo Rizzi, 2018-02-12
 *
 */

#include <cassert>
#include <cstdio>

#include <map>
#include <utility>

using namespace std;

void f(int a, int b, int c) {
    if(a<=b)
      printf("ciao\n");
    else {
      f(a-1, b, 0);
      f(a-1, b, 1);
      f(a-5, b + 5, 0);
    }
}

int num_prints1(int a, int b, int c) {
  // deve fare 10 punti, arriva fino a 20 < a-b < 30
    if(a<=b) return 1;
    return
      num_prints1(a-1, b, 0) +
      num_prints1(a-1, b, 1) +
      num_prints1(a-5, b + 5, 0) % 1000000;
}

int num_prints2(int a, int b) {
  // deve fare 10+20 punti, arriva fino a 100 < a-b < 120
    if(a<=b) return 1;
    return
      (2*num_prints2(a-1, b ) + num_prints2(a-5, b + 5) ) % 1000000;
}

#define MAXa 1000
#define MAXb 1000
int memoRisp2[MAXa +1][MAXb +1];
int num_prints2memo(int a, int b) {
    // deve fare 10+20+20 punti, problemi di vario genere per memoria quando a e b grandi, anche con a-b contenuto
  if(a<=b)  return 1;
  if( memoRisp2[a][b] == 0 ) {
     memoRisp2[a][b] =
       (2*num_prints2memo(a-1, b) + num_prints2memo(a-5, b + 5) ) % 1000000;
  }
  return memoRisp2[a][b];
}

map<pair<int, int>, int> memoHash;
int num_prints2hashmemo(int a, int b) {
  // deve fare 10+20+20+20 punti
  if( memoHash.find( make_pair(a, b) ) == memoHash.end() ) {
    if(a<=b)  memoHash[ make_pair(a, b) ] = 1;
    else memoHash[ make_pair(a, b) ] =
	   (2*num_prints2hashmemo(a-1, b) + num_prints2hashmemo(a-5, b + 5) ) % 1000000;
  }
  return memoHash[ make_pair(a, b) ];
}

int num_prints3(int a, int b, int a_minus_b) {
    assert( a_minus_b == a - b );
    if(a_minus_b <= 0) return 1;
    return
      (2*num_prints3(a-1, b, a-1 -b) + num_prints3(a-5, b + 5, a-5 -b - 5) ) % 1000000;
}

int num_prints4(int a_minus_b) {
    if(a_minus_b <= 0) return 1;
    return
      (2*num_prints4(a_minus_b -1) + num_prints4(a_minus_b -10) ) % 1000000;
}

#define MAXa_minus_b 250000
int memoRisp4[MAXa_minus_b +1];
int num_prints4memo(int a_minus_b) {
  // deve fare 10+20+20+20+30 punti, arriva fino a a-b = 250000
  if(a_minus_b <= 0) return 1;
  if( memoRisp4[a_minus_b] == 0 )
    memoRisp4[a_minus_b] =
      (2*num_prints4memo(a_minus_b -1) + num_prints4memo(a_minus_b -10) ) % 1000000;
  return memoRisp4[a_minus_b];
}



int main() {
#ifdef EVAL
    assert( freopen("input.txt", "r", stdin) );
    assert( freopen("output.txt", "w", stdout) );
#endif
    int a, b, c;
    assert ( scanf("%d %d %d", &a, &b, &c) > 0 );

    printf("num_prints4memo = %d\n", num_prints4memo(a - b));
    // deve fare 10+20+20+20+30 punti, arriva fino a a-b = 250000

    printf("num_prints2hashmemo = %d\n", num_prints2hashmemo(a, b));
    // deve fare 10+20+20+20 punti, arriva fino a 5000 < a-b < 7000

    printf("num_prints2memo = %d\n", num_prints2memo(a, b));
    // deve fare 10+20+20 punti, problemi di vario genere per memoria quando a e b grandi, anche con a-b contenuto

    // printf("num_prints2 = %d\n", num_prints2(a, b));
    // deve fare 10+20 punti, arriva fino a 100 < a-b < 120

    // printf("num_prints1 = %d\n", num_prints1(a, b, c));
    // deve fare 10+10 punti, arriva fino a 20 < a-b < 30

    //f(a, b, c);

    return 0;
}
