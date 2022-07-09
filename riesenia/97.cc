#include <iostream>
#include <set>
using namespace std;

int main() {
  multiset<int> s;
  int n;
  cin >> n;
  while (n-- > 0) {
    int x;
    cin >> x;
    s.insert(x);
  }
  int sum = 0;
  while (s.size() > 1) {
    int a = *s.begin();
    s.erase(s.begin());
    int b = *s.begin();
    s.erase(s.begin());
    sum += a + b;
    s.insert(a + b);
  }
  cout << sum << endl;
}
