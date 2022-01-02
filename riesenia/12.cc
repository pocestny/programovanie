#include <iostream>
using namespace std;

int main() {
  int i, j, n;
  cin >> n;
  for (i = 0; i < n; i++) 
    cout << 1;
  cout << endl;
  for (i = 0; i < n - 2; i++) {
    cout << 1;
    for (j = 0; j < n - 2; j++) 
      cout << 0;
    cout << 1 << endl;
  }
  for (i = 0; i < n; i++) 
    cout << 1;
  cout << endl;
}
