#include <iostream>
using namespace std;

int main() {
  int n, i;
  cin >> n;
  int x[n];
  for (i = 0; i < n; i++) cin >> x[i];
  int a, cnt = 0;
  cin >> a;
  for (i = 0; i < n; i++)
    if (x[i] == a) cnt++;
  cout << cnt << endl;
}
