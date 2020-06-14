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

void f(int a, int b) {
    if(a<=b)
      printf("ciao\n");
    else {
      f(a-1, b + (a-b)/4);
      f(a-1, b + (a-b)/4);
      f(a-2, b + (a-b)/4);
    }
}    

long long int num_prints1(int a, int b) {
  // deve fare 10 punti  
    if(a<=b) return 1;
    return
      num_prints1(a-1, b + (a-b)/4) +
      num_prints1(a-1, b + (a-b)/4) +
      num_prints1(a-2, b + (a-b)/4);
}    

long long int num_prints2(int a, int b) {
  // deve fare 10+10 punti  
    if(a<=b) return 1;
    return
      2*num_prints2(a-1, b + (a-b)/4) + num_prints2(a-2, b + (a-b)/4);
}    

#define MAXa 1000
#define MAXb 1000
long long int memoRisp2[MAXa +1][MAXb +1]; 
long long int num_prints2memo(int a, int b) {
  if(a<=b)  return 1;
  // deve fare 10+10+40 punti  
  if( memoRisp2[a][b] == 0 ) {
     memoRisp2[a][b] =
       2*num_prints2memo(a-1, b + (a-b)/4) + num_prints2memo(a-2, b + (a-b)/4);
  }  
  return memoRisp2[a][b];
}    

map<pair<int, int>, long long int> memoHash;
long long int num_prints2hashmemo(int a, int b) {
  // deve fare 10+10+40 punti  
  if( memoHash.find( make_pair(a, b) ) == memoHash.end() ) {
    if(a<=b)  memoHash[ make_pair(a, b) ] = 1;
    else memoHash[ make_pair(a, b) ] =
      2*num_prints2hashmemo(a-1, b + (a-b)/4) + num_prints2hashmemo(a-2, b + (a-b)/4);
  }  
  return memoHash[ make_pair(a, b) ];
}    

long long int num_prints3(int a, int b, int a_minus_b) {
    assert( a_minus_b == a - b );
    if(a_minus_b <= 0) return 1;
    return
      2*num_prints3(a-1, b + (a-b)/4, a-1 -b - (a-b)/4) + num_prints3(a-2, b + (a-b)/4, a-2 -b - (a-b)/4);
}    

long long int num_prints4(int a_minus_b) {
    if(a_minus_b <= 0) return 1;
    return
      2*num_prints4(a_minus_b -1 - (a_minus_b)/4) + num_prints4(a_minus_b -2 - (a_minus_b)/4);
}    

#define MAXa_minus_b 1000000
long long int memoRisp4[MAXa_minus_b +1]; 
long long int num_prints4memo(int a_minus_b) {
  // deve fare 10+10+40+40 punti (soluzione con memoizzazione)
  if(a_minus_b <= 0) return 1;
  if( memoRisp4[a_minus_b] == 0 )
    memoRisp4[a_minus_b] =
      2*num_prints4memo(a_minus_b -1 - (a_minus_b)/4) + num_prints4memo(a_minus_b -2 - (a_minus_b)/4);
  return memoRisp4[a_minus_b];
}    



int main() {
#ifdef EVAL
    assert( freopen("input.txt", "r", stdin) );
    assert( freopen("output.txt", "w", stdout) );
#endif
    int a, b;
    assert ( scanf("%d %d", &a, &b) > 0 );

    printf("num_prints4memo = %lld\n", num_prints4memo(a - b));

    printf("num_prints2hashmemo = %lld\n", num_prints2hashmemo(a, b));
    
    //printf("num_prints2memo = %lld\n", num_prints2memo(a, b));

    printf("num_prints2 = %lld\n", num_prints2(a, b));

    printf("num_prints1 = %lld\n", num_prints1(a, b));    
    
    //f(a, b);

    return 0;
}

