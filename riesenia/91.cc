#include <iostream>
#include <map>
#include <string>
using namespace std;

int main() {
  map<string, int> m;
  int n;
  cin >> n;
  while (n-- > 0) {
    string s1, s2;
    int x;
    cin >> s1 >> s2 >> x;
    m[s1] += x;
    m[s2] -= x;
  }
  for (auto it = m.begin(); it != m.end(); it++)
    cout << it->first << ": " << it->second << endl;
}
