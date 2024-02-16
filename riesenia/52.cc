#include <iostream>

using namespace std;

int n;
int a[10000], m[10000];
bool sol[10000];

int main() {
  cin >> n;
  for (int i = 0; i < n; i++) cin >> a[i];

  m[n] = -1;
  m[n - 1] = a[n - 1];
  sol[n - 1] = true;
  for (int i = n - 2; i >= 0; i--) {
    int x = a[i] + m[i + 2], y = m[i + 1];
    if (x > y) {
      m[i] = x;
      sol[i] = true;
    } else {
      m[i] = y;
      sol[i] = false;
    }
  }

  cout << m[0] << endl;
  for (int i = 0; i < n; i++)
    if (sol[i]) {
      cout << a[i] << " ";
      i++;
    }
  cout << endl;
}
