#include <iostream>
using namespace std;

int main() {
  int r, s, d, i, j, k, l;
  bool found;
  cin >> r >> s >> d;
  int a[r][s];
  for (i = 0; i < r; i++)
    for (j = 0; j < s; j++) cin >> a[i][j];
  found = false;
  for (i = 0; !found && i <= r - d; i++)
    for (j = 0; !found && j <= s - d; j++) {
      bool ok = true;
      for (k = i; ok && k < i + d; k++)
        for (l = j; ok && l < j + d; l++)
          if (a[k][l] != 0) ok = false;
      if (ok) found = true;
    }
  if (!found) cout << "nie ";
  cout << "je tam" << endl;
}
