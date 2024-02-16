#include <iostream>
using namespace std;

int main() {
  int n;
  cin >> n;
  int i, kopy[n];
  for (i = 0; i < n; i++) kopy[i] = 0;
  char prikaz[100];
  int a, b;
  while (true) {
    cin >> prikaz;
    if (prikaz[0] == 'p') {
      cin >> a >> b;
      kopy[a] = kopy[a] + b;
    } else if (prikaz[0] == 'u') {
      cin >> a >> b;
      kopy[a] = kopy[a] - b;
    } else if (prikaz[0] == 'm') {
      int max = kopy[0];
      for (i = 1; i < n; i++)
        if (kopy[i] > max) max = kopy[i];
      cout << max << endl;
    } else if (prikaz[0] == 'k')
      break;
  }
}
