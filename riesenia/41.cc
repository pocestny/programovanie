#include <iostream>
using namespace std;

int a[1000][1000];
int r, s;

void fill(int i, int j) {
  if (i < 0 || i >= r || j < 0 || j >= s) return;
  if (a[i][j] == 0) {
    a[i][j] = 1;
    fill(i - 1, j);
    fill(i + 1, j);
    fill(i, j - 1);
    fill(i, j + 1);
  }
}

int main() {
  int i, j;
  cin >> r >> s;
  for (i = 0; i < r; i++)
    for (j = 0; j < s; j++) cin >> a[i][j];
  cin >> i >> j;
  fill(i, j);
  for (i = 0; i < r; i++) {
    for (j = 0; j < s; j++) cout << a[i][j] << " ";
    cout << endl;
  }
}
