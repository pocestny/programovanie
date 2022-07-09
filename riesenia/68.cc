#include <iostream>
#include <string>
using namespace std;

int cislo(string s) {
  int i, res = 0;
  for (i = 0; i < s.size(); i++) res = 10 * res + (s[i] - '0');
  return res;
}

int main() {
  string s;
  cin >> s;
  cout << cislo(s) << endl;
}
