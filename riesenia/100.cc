#include <algorithm>
#include <iostream>
#include <set>
#include <sstream>
#include <string>

using namespace std;

int main() {
  int w, h, n;
  string line;

  getline(cin, line);
  stringstream ss(line);
  ss >> w >> h >> n;

  multiset<int> d[2];
  set<int> x[2];
  // 0 - x, 1 - y

  d[0].insert(w);
  d[1].insert(h);
  x[0].insert(0);
  x[0].insert(w);
  x[1].insert(0);
  x[1].insert(h);

  while (n-- > 0) {
    getline(cin, line);
    int j = 0;
    if (line[0] == 'H') j = 1;
    stringstream ss(line.substr(2));
    int i;
    ss >> i;
    auto tmp = x[j].lower_bound(i);
    int i2 = *tmp;
    tmp--;
    int i1 = *tmp;
    d[j].erase(d[j].find(i2 - i1));
    d[j].insert(i - i1);
    d[j].insert(i2 - i);
    x[j].insert(i);
    auto xx = d[0].end(), yy = d[1].end();
    xx--;
    yy--;
    cout << (*xx) * (*yy) << endl;
  }
}
