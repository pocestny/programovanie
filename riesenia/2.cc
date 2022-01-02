#include <iostream>
using namespace std;
int main() {
  int a;
  int b;
  int c;
  cin >> a;
  cin >> b;
  cin >> c;
  if (a > b) {
    if (b > c)
      cout << b << endl;
    else {
      if (a > c)
        cout << c << endl;
      else
        cout << a << endl;
    }
  } else {
    if (a > c)
      cout << a << endl;
    else {
      if (b > c)
        cout << c << endl;
      else
        cout << b << endl;
    }
  }
}
