/*
  The idea is to sort the intervals in non-decreasing order of their left endpoint. The algorithm will then consider the intervals one by one deciding which ones to take and which ones to leave out.
  Before strarting this main loop, set variable new_start = 0. This variable indicates the leftmost point (day in the problem) that is neither covered by the already taken intervals nor yet discovered to be uncovered.
  The idea is to always take, among the intervals which can still cover it, the one stretching rightmost. Or, if no interval can cover it, then we take the first interval that opens to the right of that point.
*/
#include <cassert>
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Driver function to sort the vector elements by
// 1. first component non-decreasing
// 2. second component non-increasing
bool sortlex_nd_ni(const pair<int,int> &a,
                   const pair<int,int> &b)
{
  return a.first<b.first || ( a.first==b.first && a.second>b.second);
}

int main () {
  int t, n, k;
  cin >> t >> k >> n;
  assert(0 <= t && t <= 1);
  assert(2 <= k && k <= 100000000);
  assert(2 <= n && n <= 100000);

  pair<int,int> p;
  vector< pair<int,int> > turni;
  for (int i = 0; i < n; i++) {
    cin >> p.first >> p.second;
    turni.push_back(p);
  }
  
  sort(turni.begin(), turni.end(), sortlex_nd_ni); // ordine crescente sulla sola prima componente
  //for (int i = 0; i < n; i++)
  //  cout << "turni[" << i << "] = [" << turni[i].first <<","<< turni[i].second << "]" << endl;

  vector< pair<int,int> > intervalli_presi, intervalli_scoperti;
  intervalli_presi.push_back(turni[0]);
  int x = turni[0].first; // numero di giorni lasciati scoperti
  if(x>0)
    intervalli_scoperti.push_back(make_pair(0,turni[0].first-1));
  pair<int,int> best_next = turni[0]; // non abbiamo ancora incontrato un vero candidato per il next interval da prendere 
  for(int i = 1; i < n; i++) {
    //cout << "consider turni[" << i << "]=[" << turni[i].first << "," << turni[i].second << "] with best_next=[" << best_next.first << "," << best_next.second << "]" << endl;
    if(turni[i].second <= best_next.second)  continue;
    if(turni[i].first <= intervalli_presi.back().second +1)
      best_next = turni[i];
    else {
      if(best_next.second > intervalli_presi.back().second) { //se abbiamo un vero candidato
	if(best_next.first > intervalli_presi.back().second +1) {
	  x += best_next.first-intervalli_presi.back().second -1;
	  intervalli_scoperti.push_back(make_pair(intervalli_presi.back().second +1,best_next.first-1));
	}
        intervalli_presi.push_back(best_next);
      }
      best_next = turni[i];
    }
  }
  if(best_next.second > intervalli_presi.back().second) {
    if(best_next.first > intervalli_presi.back().second +1) {
      x += best_next.first-intervalli_presi.back().second -1;
      intervalli_scoperti.push_back(make_pair(intervalli_presi.back().second +1,best_next.first-1));
    }
    intervalli_presi.push_back(best_next);
  }
  if(intervalli_presi.back().second < k-1) {
    intervalli_scoperti.push_back(make_pair(intervalli_presi.back().second +1,k-1));
    x += k-1-intervalli_presi.back().second;
  }
    
  if(t==0) {
    cout << x << endl;
  }
  else {
    cout << intervalli_presi.size() << endl;
  }

  /* DISPLAY
  for (int i = 0; i < intervalli_presi.size(); i++)
    cout << "intervalli_presi[" << i << "] = [" << intervalli_presi[i].first <<","<< intervalli_presi[i].second << "]" << endl;
  for (int i = 0; i < intervalli_scoperti.size(); i++)
    cout << "intervalli_scoperti[" << i << "] = [" << intervalli_scoperti[i].first <<","<< intervalli_scoperti[i].second << "]" << endl;
  */
  
  assert( t==0 || t==1 );
  // CHECK CONSISTENCY
  // gli scoperti non si intersecano tra loro nè con i presi. Ogni giorno {0,...,k} ricade in un qualche intervallo di scoperti o di presi.
  int i,j,check_x; i=j=check_x=0;
  int last_uncovered = -1; // last day already classified as uncovered
  int day = 0; // first day yet to be classified as either taken or uncovered intervals
  while(day < k) {
    //cout << "-first day yet to be classified: " << day << endl;
    int next_taken_first = k;
    int next_uncovered_first = k;
    if(i < intervalli_scoperti.size()) {
      next_uncovered_first = intervalli_scoperti[i].first;
      assert(next_uncovered_first >= day);
      //cout << "Incumbent interval of uncovered days: [" << intervalli_scoperti[i].first << "," << intervalli_scoperti[i].second << "] = intervalli_scoperti[" << i << "]" << endl;
    }
    if(j < intervalli_presi.size()) {
      next_taken_first = intervalli_presi[j].first;
      assert(next_taken_first > last_uncovered);
      //cout << "Incumbent taken interval: [" << intervalli_presi[j].first << "," << intervalli_presi[j].second << "] = intervalli_presi[" << j << "]" << endl;
    }
    assert(min(next_uncovered_first,next_taken_first) <= day);
    if(next_taken_first <=  day) {
      assert(next_uncovered_first > day);
      day = intervalli_presi[j].second +1;
      //cout << "Next comes a taken interval: [" << intervalli_presi[j].first << "," << intervalli_presi[j].second << "]" << endl;
      j++;
    }
    else {
      assert(next_uncovered_first ==  day);
      //cout << "Next comes an interval of uncovered days: [" << intervalli_scoperti[i].first << "," << intervalli_scoperti[i].second << "]" << endl;
      day = intervalli_scoperti[i].second +1;
      check_x += intervalli_scoperti[i].second - intervalli_scoperti[i].first +1;
      i++;
    }
  }
  //cout << "check_x, x= " << check_x << " " << x << endl;
  assert(check_x == x);
  // Next: verifica non ci sia nessuna intersezione tra intervalli scoperti e intervalli originari (turni)
  // sia turni che intervalli_scoperti sono ordinati (non_decrescente) su prima componente 
  for(int i,j=0; i<intervalli_scoperti.size(); i++) {
    for( ; j<turni.size(); j++) {
      if(turni[j].second < intervalli_scoperti[i].first) continue;
      assert(turni[j].first > intervalli_scoperti[i].second);
    }
  }
}
