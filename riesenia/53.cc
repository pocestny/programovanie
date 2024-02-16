#include <iostream>
using namespace std;

// riesenie O(n^2) s pouzitim <set> sa da vylepsit na O(n log n)

int a[1000], m[1000];

int main() {
  int n;
  cin >> n;
  for (int i = 0; i < n; i++) cin >> a[i];
  int k = 1;
  m[0] = 1;
  for (int i = 1; i < n; i++) {
    m[i] = 1;
    for (int j = 0; j < i; j++)
      if (a[j] < a[i] && m[j] + 1 > m[i]) m[i] = m[j] + 1;
    if (m[i] > k) k = m[i];
  }

  int mx = a[0];
  for (int i = 1; i < n; i++)
    if (a[i] > mx) mx = a[i];
  mx++;

  int sol[k];
  int c = k;
  for (int i = n - 1; i >= 0; i--)
    if (a[i] < mx && m[i] == c) {
      c--;
      sol[c] = a[i];
      mx = a[i];
    }

  for (int i = 0; i < k; i++) cout << sol[i] << " ";
  cout << endl;
}
