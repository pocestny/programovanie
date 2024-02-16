#include <iostream>
#include <string>
#include <vector>
using namespace std;

vector<int> a, b, c;
int n;

int max(int x, int y) {
  if (x > y) return x;
  return y;
}

int main() {
  string c1, c2;
  cin >> c1 >> c2;

  a.resize(c1.size());
  for (int i = 0; i < c1.size(); i++) a[i] = c1[c1.size() - i - 1] - '0';
  b.resize(c2.size());
  for (int i = 0; i < c2.size(); i++) b[i] = c2[c2.size() - i - 1] - '0';
  c.resize(a.size() + b.size() + 2);
  for (int i = 0; i < a.size(); i++) {
    vector<int> x(i);
    int prenos = 0;
    for (int j = 0; j < b.size(); j++) {
      int s = a[i] * b[j] + prenos;
      x.push_back(s % 10);
      prenos = s / 10;
    }
    while (prenos > 0) {
      x.push_back(prenos % 10);
      prenos = prenos / 10;
    }
    prenos = 0;
    x.resize(max(c.size(), x.size()));
    c.resize(max(c.size(), x.size()));
    for (int j = 0; j < x.size(); j++) {
      int s = c[j] + x[j] + prenos;
      c[j] = s % 10;
      prenos = s / 10;
    }
    if (prenos > 0) c.push_back(prenos);
  }
  int i = c.size() - 1;
  while (c[i] == 0) i--;
  while (i >= 0) {
    cout << c[i];
    i--;
  }
  cout << endl;
}
