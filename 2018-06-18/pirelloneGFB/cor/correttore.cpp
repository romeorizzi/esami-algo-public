#include <cstdio>
#include <cstdlib>
#include <cassert>

#define  MaxM   5000
#define  MaxN   5000

void ex( const char *msg, float res ) {
   if (msg) fprintf(stderr, "%s\n", msg);

   printf("%f\n", res);

   exit(0);
}

int M, N, B;
int row[MaxM];
int col[MaxN];

FILE* in;
FILE* out;
FILE* an;

int leggi_interruttore() {
  int temp;
  if(fscanf(an, "%d", &temp) != 1) {
    ex("Output errato: interruttori insufficienti.", 0.0);
  }
  if(temp < 0 || temp >= B) {
    ex("Output errato: interruttore non valido.", 0.0);
  }
  return temp;
}

int main(int argc, char *argv[]) {
  in = fopen( argv[1], "r");
  out = fopen( argv[2], "r");
  an = fopen( argv[3], "r");
  
  fscanf(in, "%d%d%d", &M, &N, &B);

  if ( an == NULL ) {
    ex("File output mancante.", 0.0);
  }

  int possible = 0;
  for(int k = 0; k < N+M; k++) {
    fscanf(out, "%d", &possible);
    if(possible) break;
  }

  int possible_detected = 0;
  for(int i = 0; i < M; i++) {
    row[i] = leggi_interruttore();
    if(row[i]) possible_detected = 1;
  }
  for(int j = 0; j < N; j++) {
    col[j] = leggi_interruttore();
    if(row[j]) possible_detected = 1;
  }

  if(!possible && !possible_detected) {
    ex("Output corretto.", 1.0);
  }

  for(int i = 0; i < M; i++) {
    for(int j = 0; j < N; j++) {
      int temp;
      fscanf(in, "%d", &temp);
      // fprintf(stderr, "(%d, %d): %d [%d, %d]\n", i, j, temp, row[i], col[j]);
      temp = (temp + row[i] + col[j]) % B;
      if(temp != 0) {
        ex("Output errato: soluzione non valida.", 0.0);
      }
    }
  }

  ex("Output corretto.", 1.0);

  return 0;
}
