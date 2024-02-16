#include <random>

#include "board.h"

using namespace std;

struct RandomPlayer {
  mt19937 rnd;

  RandomPlayer() : rnd(random_device{}()) {}

  Move findMove(const Board& b) {
    auto ms = b.legalMoves();
    return ms[rnd() % ms.size()];
  }
};

int main() {
  Board b;
  RandomPlayer p;

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
