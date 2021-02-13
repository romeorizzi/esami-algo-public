#include <cassert>
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <deque>
using namespace std;

// idea: per trovare il minimo numero di colori cercheremo la massima clique, ossia in massimo numero di intervalli che si overlappano. La prima cosa sarà ordinare gli intervalli in ordine non-decrescnte di right endpoint. Questo ordine permette di affrontare entrambi i problemi (sia max-indpendent set che massima clique) semplicemente considerando gli intervalli uno ad uno (un algoritmo greedy che trova sempre l'ottimo). I grafii intervallo sono una sottoclasse dei grafi cordali.
// certificato che al più t independent intervals: t stubbing points such that every interval contains at least one stubbing point.

// Driver function to sort the vector elements by
// second element of pair in non decreasing order
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

  vector< pair<int,int> > interval;
  pair<int,int> p;
  if(t==0) { // maximum number of independent intervals
    for (int i = 0; i < n; i++) {
      cin >> p.first >> p.second;
      interval.push_back(p);
    }
    sort(interval.begin(), interval.end(), sortbysec_nd);
    //  for (int i = 0; i < n; i++)
    //    cout << "interval[" << i << "] = [" << interval[i].first <<","<< interval[i].second << "]" << endl;

    //cout << "add interval [" << interval[0].first << "," << interval[0].second << "]" << endl;
    vector< pair<int,int> >  max_independent_set;
    max_independent_set.push_back( interval[0] );
    vector<int> stabbing_points;
    stabbing_points.push_back( interval[0].second ); // stabbing_points.back() is the rightmost point occupied by intervals in max_independent_set 
    for(int i = 1; i < n; i++) {
      if(interval[i].first <= stabbing_points.back())  continue;
      max_independent_set.push_back( interval[i] );
      //cout << "add interval [" << interval[i].first << "," << interval[i].second << "]" << endl;
      stabbing_points.push_back( interval[i].second );
    }
    cout << max_independent_set.size() << endl;
    // OPTIMALITY CHECK:
    assert(max_independent_set.size() == stabbing_points.size());
    int stab_indx = 0;
    for(int i = 0; i < n; i++) {
      assert(interval[i].second >= stabbing_points[stab_indx]);
      if(interval[i].first > stabbing_points[stab_indx]) {
	stab_indx++;      
        assert(stab_indx < stabbing_points.size());
        assert(interval[i].first <= stabbing_points[stab_indx]);
        assert(interval[i].second >= stabbing_points[stab_indx]);
      }
    }    
    // FEASIBILITY CHECK:
    for(int i = 1; i < max_independent_set.size(); i++)
      assert(max_independent_set[i-1].second <= max_independent_set[i].first);
  }
  else { // t=1, minimum number of colors
    vector< pair<int,int> > event;  
    for (int i = 0; i < n; i++) {
      int a, b;
      cin >> a >> b;
      event.push_back( make_pair(2*a, 1) );  // +1=event di apertura intervallo
      event.push_back( make_pair(2*b+1, -1) ); // -1=event di chiusura intervallo
      interval.push_back( make_pair(a,b) );
    }
    sort(event.begin(), event.end()); // ordine crescente sulla sola prima componente

    int sum = 0;
    int max_open = 0;
    int stab_point;
    for(int i = 0; i < 2*n; i++) {
      sum += event[i].second;
      if(sum>max_open) { 
        max_open = sum;
	stab_point = event[i].first/2;
      }
      //cout << "event[" << i << "] = [" << event[i].first <<","<< event[i].second << "] => sum = " << sum << ", max_open = " << max_open << endl;
    }
    cout << max_open << endl;
    // OPTIMALITY CHECK:
    int num_stabbed = 0;
    for(int i = 0; i < n; i++)
      if(interval[i].first <= stab_point && stab_point <= interval[i].second)
	num_stabbed++;
    //cout << "stab_point=" << stab_point << ", num_stabbed=" << num_stabbed << ", max_open=" << max_open << endl;
    assert(num_stabbed==max_open);
    // FEASIBILITY CHECK:
    vector<int> available_colors;
    for(int i = 1; i <= max_open; i++)
      available_colors.push_back(i);
    deque< pair<int,int> > closing_endpoint_frees_col; // monotone non-dcreasing on closing endpoint 
    sort(interval.begin(), interval.end(), sortbysec_nd); // ordine non-decrescente sulla chiusura degli intervalli
    for(int i = 0, j = 0; i < n; i++) {
      assert(j>=i); // prima li apriamo, solo successivamente li chiudiamo 
      while(j<n && interval[j].first <= interval[i].second) {
	assert(available_colors.size()>0);
	int col = available_colors.back();
	available_colors.pop_back();
	closing_endpoint_frees_col.push_back(make_pair(interval[j].second,col));
	j++;
      }
      available_colors.push_back(closing_endpoint_frees_col.front().second);
      closing_endpoint_frees_col.pop_front();
    }
  }    
}
