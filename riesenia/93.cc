#include <algorithm>
#include <functional>
#include <iostream>
#include <set>
using namespace std;

set<int, function<bool(int, int)>> s([](int a, int b) { return a > b; });

int main() {
  int n;
  cin >> n;
  s.clear();
  while (n-- > 0) {
    int x;
    cin >> x;
    if (x % 2 == 0) s.insert(x);
  }
  int cnt = 0;
  while (s.size() > 0) {
    int x = (*s.begin()) / 2;
    s.erase(s.begin());
    if (x % 2 == 0) s.insert(x);
    cnt++;
  }
  cout << cnt << endl;
}
