#include <iostream>
#include <vector>
using namespace std;
const int base = 10;

int main() {
  int n;
  vector<int> a;
  cin >> n;
  a.push_back(1);
  while (n > 1) {
    int prenos = 0;
    for (int i = 0; i < a.size(); i++) {
      int s = n * a[i] + prenos;
      a[i] = s % base;
      prenos = s / base;
    }
    while (prenos > 0) {
      a.push_back(prenos % base);
      prenos = prenos / base;
    }
    n--;
  }
  for (int i = a.size() - 1; i >= 0; i--) cout << a[i];
  cout << endl;
}
