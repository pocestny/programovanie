#include <iostream>
using namespace std;

int main() {
  char s[10000], c;
  int n = 0;
  while (true) {
    cin >> c;
    if (c == '$') {
      if (n == 0)
        cout << "ano" << endl;
      else
        cout << "nie" << endl;
      break;
    }
    if (c == ')' || c == ']' || c == '}') {
      char x;
      if (c == ')')
        x = '(';
      else if (c == ']')
        x = '[';
      else
        x = '{';
      if (n == 0 || s[n - 1] != x) {
        cout << "nie" << endl;
        break;
      }
      n--;
    } else {
      s[n] = c;
      n++;
    }
  }
}
