#include <iostream>
using namespace std;

int vyraz() {
  char c;
  cin >> c;
  if (c >= '0' && c <= '9') return c - '0';
  int v1 = vyraz(); // rekurzivne volanie
  cin >> c;         // operator
  int v2 = vyraz(); // druhe rekurzivne volanie
  int vysledok;
  if (c == '+')
    vysledok = v1 + v2;
  else
    vysledok = v1 * v2;
  cin >> c;         // zatvaracia zatvorka
  return vysledok;
}

int main() {
  cout<<vyraz()<<endl;
}


