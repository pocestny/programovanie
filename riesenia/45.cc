#include <iostream>
using namespace std;

int main() {
  int n;
  cin >> n;
  int a[n];
  int i, max = 0;
  for (i = 0; i < n; i++) cin >> a[i];
  int s[n], m = 0;
  // zásobník a jeho veľkosť
  for (i = 0; i < n; i++) {  // skúšame každého klauna
    int h = 0;
    // koľko zásahov dostal
    while (m > 0 &&
           s[m - 1] < a[i]) {  // prechádzame zásobníkom až kým neprídeme
      // na začiatok alebo na vyššieho klauna
      h++;  // zarátame zásah
      m--;  // vyhodíme zo zásobníka
    }
    s[m] = a[i];  // pridáme i-čka do zásobníka
    m++;
    if (h > max) max = h;  // aktualizujeme zásahy
  }
  cout << max << endl;
}
