#include "board.h"

using namespace std;

int main() {
  Board b;

  b.pmap[0] = b.pmap[1] = 0;

  b.set(1, 5, White);
  b.set(6, 5, White);
  b.set(1, 2, White);
  b.set(1, 1, White);
  b.set(2, 2, White);
  b.set(6, 1, White);

  b.set(5, 6, Black);
  b.set(7, 6, Black);
  b.set(5, 2, Black);
  b.set(6, 2, Black);

  cout << b << endl;
  auto ms = b.legalMoves();

  for (int i = 0; i < ms.size(); i++) {
    cout << ms[i] << "  ";
    if (i % 5 == 4) cout << endl;
  }
}
