#include <iostream>
using namespace std;
int main() {
  int min, max, pos_min, pos_max, x, n, i;
  cin >> n;
  cin >> x;
  min = x;
  max = x;
  pos_min = 0;
  pos_max = 0;
  for (i = 1; i < n; i++) {
    cin >> x;
    if (x > max) {
      max = x;
      pos_max = i;
    } else if (x < min) {
      min = x;
      pos_min = i;
    }
  }
  int vzd = pos_min - pos_max;
  if (vzd < 0) vzd = -vzd;
  cout << vzd << endl;
}
