#include <iostream>
using namespace std;

int main() {
  int n, i;
  cin >> n;
  int x[n];
  i = 0;
  while (i < n) {
    cin >> x[i];
    i = i + 1;
  }
  int a, cnt = 0;
  cin >> a;
  i = 0;
  for (i < n) {
    if (x[i] == a) cnt = cnt + 1;
    i = i + 1;
  }
  cout << cnt << endl;
}
