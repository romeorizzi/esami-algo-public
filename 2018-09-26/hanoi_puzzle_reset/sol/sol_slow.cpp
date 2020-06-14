/**
 *  File: sol_slow.cpp
 *  Partial solution to hanoi_tower_reset
 *  Takes exponential time: too slow to solve instances with many disks.
 *  Author: Romeo Rizzi, 2018-09-21
 *
 */

#include <cassert>
#include <cstdio>

const int BASE = 1000000;
const int MAXN = 30;

int N;
char pole[MAXN +1];
int numMoves = 0;

void spostaDisco(int n, char from, char to) {
  assert(pole[n]==from);
  printf("Muovi il disco %d dal piolo %c al piolo %c\n", n, from, to);
  pole[n] = to;
}

void conta_spostamentiDisco(int n, char from, char to) {
  assert(pole[n]==from);
  numMoves = (numMoves + 1) % BASE;
  pole[n] = to;
}  

char other_pole(char p1, char p2) {
  return 'A'+ (3 - (p1-'A') - (p2-'A') );
}

void makeTowerOnPole(int n, char target_pole, void (*basicActionOnDisk) (int,char,char) ) {
  if(n <= 0) return;
  if(pole[n] == target_pole)
    makeTowerOnPole(n-1, target_pole, basicActionOnDisk);
  else {
    char third_pole = other_pole(pole[n], target_pole);
    makeTowerOnPole(n-1, third_pole, basicActionOnDisk);
    (*basicActionOnDisk)(n, pole[n], target_pole);
    makeTowerOnPole(n-1, target_pole, basicActionOnDisk);
  }
}  


int main() {
#ifdef EVAL
    assert( freopen("input.txt", "r", stdin) );
    assert( freopen("output.txt", "w", stdout) );
#endif
    scanf("%d", &N);
    for(int i = 1; i <= N; i++) {
       do
          scanf("%c", &pole[i]);
       while( pole[i] < 'A' || pole[i] > 'C');
    }   
    if(N<=10)
      makeTowerOnPole(N, 'A', &spostaDisco);
    else {
      makeTowerOnPole(N, 'A', &conta_spostamentiDisco);
      printf("%d", numMoves);
    }  
    printf("\n");
        
    return 0;
}

