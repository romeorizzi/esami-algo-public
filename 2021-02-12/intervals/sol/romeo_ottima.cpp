#include <cassert>
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// idea: per trovare il minimo numero di colori cercheremo la massima clique, ossia in massimo numero di intervalli che si overlappano. La prima cosa sarà ordinare gli intervalli in ordine non-decrescnte di right endpoint. Questo ordine permette di affrontare entrambi i problemi (sia max-indpendent set che massima clique) semplicemente considerando gli intervalli uno ad uno (un algoritmo greedy che trova sempre l'ottimo). I grafii intervallo sono una sottoclasse dei grafi cordali.    

// Driver function to sort the vector elements by
// second element of pair in ascending order
bool sortbysec_nd(const pair<int,int> &a,
                  const pair<int,int> &b)
{
       return a.second<b.second;
}

int main () {
  int t, n, k;
  cin >> t >> k >> n;
  assert(0 <= t && t <= 1);
  assert(2 <= k && k <= 100000000);
  assert(2 <= n && n <= 100000);

  vector< pair<int,int> > v;
  pair<int,int> p;
  if(t==0) { // maximum number of independent intervals
    for (int i = 0; i < n; i++) {
      cin >> p.first >> p.second;
      v.push_back(p);
    }
    sort(v.begin(), v.end(), sortbysec_nd);
    //  for (int i = 0; i < n; i++)
    //    cout << "v[" << i << "] = [" << v[i].first <<","<< v[i].second << "]" << endl;

    int s = 1; // prendiamo sempre l'intervallo che si chiude per primo
    //cout << "add interval [" << v[0].first << "," << v[0].second << "]" << endl;
    int last_eaten_away = v[0].second;
    for(int i = 1; i < n; i++) {
      if(v[i].first <= last_eaten_away)  continue;
      s++;
      //cout << "add interval [" << v[i].first << "," << v[i].second << "]" << endl;
      last_eaten_away = v[i].second;
    }
    cout << s << endl;
  }
  else { // t=1, minimum number of colors
    for (int i = 0; i < n; i++) {
      int a, b;
      cin >> a >> b;
      v.push_back( make_pair(2*a, 1) );
      v.push_back( make_pair(2*b+1, -1) );
    }
    sort(v.begin(), v.end()); // ordine crescente sulla sola prima componente

    int sum = 0;
    int max_open = 0;
    for(int i = 0; i < 2*n; i++) {
      sum += v[i].second;
      max_open = max(max_open, sum);
      //cout << "v[" << i << "] = [" << v[i].first <<","<< v[i].second << "] => sum = " << sum << ", max_open = " << max_open << endl;
    }
    cout << max_open << endl;
  }    
}
