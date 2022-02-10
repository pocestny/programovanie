#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main() {
  int n;
  cin >> n;
  vector<bool> a(n + 1, false);
  while (true) {
    string s;
    int x;
    cin >> s;
    if (s[0] == '#') break;
    cin >> x;
    if (s[0] == '?') {
      if (!a[x]) cout << "ne";
      cout << "svieti" << endl;
    } else
      a[x] = !a[x];
  }
}
