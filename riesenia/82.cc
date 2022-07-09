#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int main() {
  int n;
  cin >> n;
  vector<int> a(n);
  for (int i = 0; i < n; i++) cin >> a[i];
  sort(a.begin(), a.end());
  a.push_back(a[a.size() - 1] + 10);  // zarazka
  n++;
  int max_pocet = 0, max_cislo;
  for (int i = 0; i < n;) {
    int j;
    for (j = i; j < n && a[j] == a[i]; j++)
      ;
    int cnt = j - i;
    if (cnt > max_pocet) {
      max_pocet = cnt;
      max_cislo = a[i];
    }
    i = j + 1;
  }
  cout << max_cislo << endl;
}
