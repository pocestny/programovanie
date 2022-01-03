#include <iostream>
using namespace std;

char a[100000];
int p[100000];

int main() {
  int n;
  cin >> n;
  int s[n];
  cin >> a;
  for (int i = 0; i < n; i++) p[i] = -1;
  int m = 0;
  for (int i = 0; i < n; i++)
    if (a[i] == '(') {
      s[m++] = i;
    } else if (a[i] == ')') {
      p[i] = s[m - 1];
      p[s[m - 1]] = i;
      m--;
    }
  for (int i = 0; i < n; i++) cout << p[i] << " ";
  cout << endl;
}
