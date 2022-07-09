#include <iostream>
#include <vector>
using namespace std;
const int vela = 1 << 30;

bool test(int lim, int k, vector<int>& a, vector<int>& sol) {
  sol.clear();
  sol.resize(k, 0);
  int s = 0, pos = k - 1;
  for (int i = a.size() - 1; i > 0; i--) {
    sol[pos]++;
    s += a[i];
    if (a[i - 1] + s > lim) {
      pos--;
      s = 0;
      if (i == 1) break;
      if (pos < 0) {
        return false;
      }
    }
  }
  int z = 0;
  for (int i = 0; i < k; i++)
    if (sol[i] == 0) {
      sol[i] = 1;
      z++;
    }
  for (int i = 0; i < k && z > 0;)
    if (sol[i] > 1) {
      sol[i]--;
      z--;
    } else
      i++;

  return true;
}

int max(vector<int>& a) {
  int res = a[1];
  for (int i = 2; i < a.size(); i++)
    if (a[i] > res) res = a[i];
  return res;
}

int sum(vector<int>& a) {
  int res = a[1];
  for (int i = 2; i < a.size(); i++) res += a[i];
  return res;
}

int main() {
  int n, k;
  vector<int> a, sol;
  cin >> n >> k;
  a.resize(n + 1);
  a[0] = vela;
  for (int i = 0; i < n; i++) cin >> a[i + 1];

  int l = max(a), r = sum(a), m;
  while (l < r - 1) {
    m = (r + l) / 2;
    if (test(m, k, a, sol))
      r = m;
    else
      l = m;
  }
  if (!test(l, k, a, sol)) test(r, k, a, sol);

  int b = 0;
  for (int i = 0; i < k; i++) {
    for (int j = 0; j < sol[i]; j++) {
      if (j > 0) cout << " ";
      cout << a[++b];
    }
    if (i < k - 1) cout << " / ";
  }
  cout << endl;
}
