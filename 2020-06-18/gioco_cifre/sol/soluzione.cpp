#include<iostream>
using namespace std;
int main() {
    int N;
    cin >> N;
    cout << (N % 10 ? "1 " + to_string(N % 10) : "0") << endl;
    return 0;
}
