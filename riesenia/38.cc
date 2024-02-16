#include <iostream>
using namespace std;

char c;

int vyraz() {
  char op;
  if (c >= '0' && c <= '9') {
    int val = 0;
    while (c >= '0' && c <= '9') {
      val = 10 * val + (c - '0');
      cin >> c;
    }
    return val;
  }
  cin >> c;
  int v1 = vyraz();  // rekurzivne volanie
  op = c;            // operator
  cin >> c;
  int v2 = vyraz();  // druhe rekurzivne volanie
  int vysledok;
  if (op == '+')
    vysledok = v1 + v2;
  else
    vysledok = v1 * v2;
  cin >> c;  // zatvaracia zatvorka
  return vysledok;
}

int main() {
  cin >> c;
  cout << vyraz() << endl;
}
