#include <random>

#include "minimaxplayer.h"

using namespace std;

int main() {
  Board b;

  MinimaxPlayer p;

  while (true) {
    Move m{{9, 9}, {9, 9}};
    while (!b.legal(m)) {
      cout << b << endl << "Zadaj ťah: ";
      cin >> m;
    }
    b += m;
    cout << b << endl;
    if (b.winner() == White) {
      cout << "Vyhral si!" << endl;
      break;
    }
    m = p.findMove(b);
    b += m;
    cout << "Program zahral " << m << endl;
    if (b.winner() == Black) {
      cout << b << endl;
      cout << "Program vyhral!" << endl;
      break;
    }
  }
}
