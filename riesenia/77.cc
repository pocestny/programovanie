#include <iostream>
#include <vector>

using namespace std;

vector<int> C;
int n, k;

bool test(int r) {
  int sum = 0;
  for (int i = 0; i < k; i++) sum += C[i] / r;
  return sum >= n;
}

void search(int l, int r) {
  if (r - l < 10) {
    for (int i = r - 1; i >= l; i--)
      if (test(i)) {
        cout << i << endl;
        exit(0);
      }
  } else {
    int m = (l + r) / 2;
    if (test(m))
      search(m, r);
    else
      search(l, m);
  }
}

int main() {
  cin >> n >> k;
  C.resize(k);
  for (int i = 0; i < k; i++) cin >> C[i];
  if (test(n))
    cout << n << endl;
  else
    search(1, n);
}
