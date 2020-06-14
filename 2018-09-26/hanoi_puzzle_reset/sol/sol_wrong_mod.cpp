/**
 *  File: sol_wrong_mod.cpp
 *  Partial solution to hanoi_tower_reset
 *  Returns wrong number of moves (mod B) for big numbers since it computes the mod only at the end
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
int nMovesMod[MAXN];
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
    if(basicActionOnDisk==&spostaDisco)
      makeTowerOnPole(n-1, target_pole, basicActionOnDisk);
    else {
      assert(basicActionOnDisk==&conta_spostamentiDisco);
      numMoves = numMoves + nMovesMod[n-1];
      for(int i = n-1; i >= 1; i--)
        pole[i] = target_pole;
    }  
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
      for(int i = 1; i<= N; i++)
        nMovesMod[i] = ( (nMovesMod[i-1] + 1) % BASE + nMovesMod[i-1]) % BASE;
      makeTowerOnPole(N, 'A', &conta_spostamentiDisco);
      printf("%d", numMoves);
    }  
    printf("\n");
        
    return 0;
}

