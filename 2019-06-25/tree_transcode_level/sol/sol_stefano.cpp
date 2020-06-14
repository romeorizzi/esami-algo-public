#include <iostream>
#include <vector>
#include <fstream>
#include <cassert>

using namespace std;

ifstream fin;
ofstream fout;

vector<int> vec1, vec2;

int writeType_2(int deep){
  int child; fin >> child;
  int count = 1;
  fout << deep << " ";
  while(count < child) {
    count += writeType_2(deep + 1);
  }
  fout << deep << " ";
  return child;
}

int calcVec1(int index1, int index2){
  vec1.push_back(1);
  int deep; deep = vec2[index2];
  while(vec2[index2 + 2*vec1[index1]  - 1] > deep) {
    vec1[index1] += calcVec1(index1 + vec1[index1], index2 + 2*vec1[index1] - 1);
  }
  return vec1[index1];
}

void writeType_1(){
  vec2.push_back(0);
  int temp;
  fin >> temp;
  do {
    fin >> temp;
    vec2.push_back(temp);
  } while(temp > 0);
  calcVec1(0, 0);
  for(int i= 0; i < vec1.size(); i++) {
    fout << vec1[i] << " ";
  }
}


int main(){
  fin.open("input.txt");
  fout.open("output.txt");
  assert( fin );
  assert( fout );
  int type; fin >> type;
  fout << 3-type << " ";
  if(type == 1) {
      writeType_2(0);
  } else {
      writeType_1(); 
  }
  fout << endl;
  return 0;
}
