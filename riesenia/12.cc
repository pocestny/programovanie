#include <iostream>
using namespace std;

int main() {
  int i, j, n;
  cin >> n;
  i = 0;
  while (i < n) { 
    cout << 1;
    i = i + 1;
  }
  cout << endl;
  i = 0;
  while (i < n - 2) {
    cout << 1;
    j = 0;
    while (j < n - 2) { 
      cout << 0;
      j = j + 1;
    }
    cout << 1 << endl;
    i = i + 1;
  }
  i = 0;  
  while (i < n) { 
    cout << 1;
    i = i + 1;
  }
  cout << endl;
}
