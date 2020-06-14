#include <cstdio>

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

  bool valid = true;
  scanf("%d", &row[0]);
  for(int j = 1; j < N; j++) {
    scanf("%d", &col[j]);
  }
  for(int i = 1; i < M; i++) {
    scanf("%d", &row[i]);
    for(int j = 1; j < N; j++) {
      int temp;
      scanf("%d", &temp);
      valid &= (temp == (row[i] ^ col[j]));
    }
  }

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
}