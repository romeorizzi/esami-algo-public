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

  vector< pair<int,int> > turni;
  pair<int,int> p;
  for (int i = 0; i < n; i++) {
    cin >> p.first >> p.second;
    turni.push_back(p);
  }
  
  sort(turni.begin(), turni.end(), sortlex_nd_ni); // ordine crescente sulla sola prima componente
  //for (int i = 0; i < n; i++)
    //cout << "turni[" << i << "] = [" << turni[i].first <<","<< turni[i].second << "]" << endl;

  int x = 0; // numero di giorni lasciati scoperti
  int m = 0; // numero di intervali presi
  int new_start = 0; // first day yet to be covered or to be accounted as uncoveed 
  int cur_m_left_upper_bound = turni[0].first;
  int last_a = turni[0].first; //grows monotonically
  int last_b = turni[0].second; //grows monotonically
  for(int i = 1; i < n; i++) {
    if(turni[i].second <= last_b)  continue;
    if(turni[i].first > cur_m_left_upper_bound) {
      //cout << "add interval [" << last_a << "," << last_b << "]" << endl;
      m += 1;
      if(last_a > new_start)
	x += last_a - new_start;
      new_start = last_b+1;
      cur_m_left_upper_bound = new_start;
    }
    last_a = turni[i].first;
    last_b = turni[i].second;
  }
  if(new_start <= last_b) {
    //cout << "add interval [" << last_a << "," << last_b << "]" << endl;
    m += 1;
    if(last_a > new_start)
      x += last_a - new_start;
  }
  x += k-1-last_b;
    
  if(t==1)
    cout << m << endl;
  if(t==0)
    cout << x << endl;
}
