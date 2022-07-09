#include <iostream>
using namespace std;

int dlzka(int x) {
  int res = 0;
  while (x > 0) {
    res++;
    x = x / 10;
  }
  return res;
}

int main() {
  int n;
  cin >> n;

  int najviac = 1;
  for (int j = 0; j < n - 1; j++) najviac *= n;
  int d = dlzka(najviac);

  for (int i = 2; i <= n; i++) {
    int x = 1;
    for (int j = 0; j < n; j++) {
      for (int m = d - dlzka(x); m >= 0; m--) cout << " ";
      cout << x;
      x = x * i;
    }
    cout << endl;
  }
}
