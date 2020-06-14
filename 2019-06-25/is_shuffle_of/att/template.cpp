// template di soluzione per il problema is_shuffle_of
#include <cassert>
#include <fstream>

using namespace std;

const int MAXN = 200000;
const int MAXM = 200000;

int main() {
  ifstream fin("input.txt");
  assert(fin);
  int m,n,with_cert;
  fin >> m >> n >> with_cert;
  ofstream fout("output.txt");
  fout << 0 << endl;
  fin.close();
  fout.close();
  return 0;
}
