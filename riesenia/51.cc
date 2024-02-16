#include <iostream>
using namespace std;

char a[100000];
int p[100000];

int decode(int i, int dir) {
  for (int j = p[i] + dir; j != i; j += dir) {
    if (p[j] != -1)
      j = decode(j, -dir);
    else
      cout << a[j];
  }
  return p[i];
}

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
  decode(0, -1);
  cout<<endl;
}
