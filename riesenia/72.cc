#include <iostream>
#include <vector>
using namespace std;

int c;
vector<int> a;

void merge(vector<int> &a, vector<int> &b, vector<int> &p) {
  int i = 0, j = 0;
  int n = a.size(), m = b.size();
  p.resize(n + m);
  for (int k = 0; k < n + m; k++)
    if (i < n && (j == m || a[i] < b[j])) {
      p[k] = a[i];
      i++;
    } else {
      p[k] = b[j];
      j++;
    }
}

void sort(vector<int> &a) {
  int n = a.size();
  if (n <= 1) return;
  int x = n / 2, y = n - x;
  vector<int> b(x), c(y);
  for (int i = 0; i < x; i++) b[i] = a[i];
  for (int i = 0; i < y; i++) c[i] = a[i + x];
  sort(b);
  sort(c);
  merge(b, c, a);
}

int najdi(vector<int> &a, int x) {
  int n = a.size();
  int l = 0, r = n - 1, m;
  if (a[l] >= x) return l;
  if (a[r] < x) return -1;
  while (l < r - 1) {
    m = (l + r) / 2;
    if (a[m] >= x)
      r = m;
    else
      l = m;
  }
  if (a[l] >= x) return l;
  return r;
}

bool test(int d) {
  int p = a[0];

  for (int i = 0; i < c - 1; i++) {
    int f = najdi(a, p + d);
    if (f == -1) return false;
    p = a[f];
  }
  return true;
}

int main() {
  int n;
  cin >> n >> c;

  a.resize(n);
  for (int i = 0; i < n; i++) cin >> a[i];
  sort(a);

  int u = (a[n - 1] - a[0]) / (c - 1);
  if (test(u))
    cout << u << endl;
  else {
    int l = 0;
    while (u > l + 1) {
      int m = (u + l) / 2;
      if (test(m))
        l = m;
      else
        u = m;
    }
    cout << l << endl;
  }
}
