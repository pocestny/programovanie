#include <iostream>
#include <vector>
using namespace std;

const int vela = 1 << 30;

int max(int a, int b) {
  if (a > b) return a;
  return b;
}
int min(int a, int b) {
  if (a < b) return a;
  return b;
}

int stredny(int n, vector<int> &a, vector<int> &b) {
  int i = n / 2;
  while (true) {
    if (max(a[i], b[n - i]) <= min(a[i + 1], b[n - i + 1]))
      return max(a[i], b[n - i]);
    if (a[i] > b[n - i])
      i = i / 2;
    else
      i = (n + i + 1) / 2;
  }
}

int main() {
  vector<int> a, b;
  int n;
  cin >> n;
  a.resize(n + 1);
  b.resize(n + 1);
  a[0] = -vela;
  b[0] = -vela;
  for (int i = 1; i <= n; i++) cin >> a[i];
  for (int i = 1; i <= n; i++) cin >> b[i];
  a.push_back(vela);
  b.push_back(vela);
  cout << stredny(n, a, b) << endl;
}
