#include <cstdio>
#include <vector>

int main() {
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);

  int N;
  scanf("%d", &N);
  int v[N];
  for(int i = 0; i < N; i++) {
    scanf("%d", &v[i]);
  }

  std::vector<int> s;
  s.push_back(0);

  int sol = 0;
  for(int i = 0; i < N; i++) {
    while(s.back() > v[i]) {
      s.pop_back();
      sol++;
    }
    if(s.back() < v[i]) s.push_back(v[i]);
  }

  sol += s.size()-1;

  printf("%d\n", sol);
}
