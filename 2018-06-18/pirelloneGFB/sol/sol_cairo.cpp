#include <cstdio>
#include <cassert>

const int DIM = 5000;

int M, N, B;
int col[DIM+2];
int row[DIM+2];

int main() {
#ifdef EVAL
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
#endif

  scanf("%d%d%d", &M, &N, &B);

  assert(M >= 0 && N >= 0 && B >= 0);

  int temp;
  bool valid = true;
  scanf("%d", &temp);
  col[0] = 0;
  row[0] = (B-temp)%B;
  for(int j = 1; j < N; j++) {
    scanf("%d", &temp);
    col[j] = (B - temp + B - row[0]) % B;
  }
  for(int i = 1; i < M; i++) {
    scanf("%d", &temp);
    row[i] = (B-temp)%B;
    for(int j = 1; j < N; j++) {
      scanf("%d", &temp);
      valid &= ((temp + row[i] + col[j])%B) == 0;
    }
  }

  for(int i = 0; i < M; i++) {
    // fprintf(stderr, "%d ", row[i]);
  }
  // fprintf(stderr, "\n");

  for(int j = 0; j < N; j++) {
    // fprintf(stderr, "%d ", col[j]);
  }
  // fprintf(stderr, "\n");

  if(valid) {
    for(int i = 0; i < M; i++) {
      printf("%d ", row[i]);
    }
    printf("\n");
    for(int j = 0; j < N; j++) {
      printf("%d ", col[j]);
    }
    printf("\n");
  } else {
    for(int i = 0; i < M; i++) {
      printf("%d ", 0);
    }
    printf("\n");
    for(int j = 0; j < N; j++) {
      printf("%d ", 0);
    }
    printf("\n");
  }

  return 0;
}