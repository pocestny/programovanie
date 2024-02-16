#include "randomplayer.h"
using namespace std;
RandomPlayer::RandomPlayer() : rnd(random_device{}()) {}

Move RandomPlayer::findMove(const Board& b) {
  auto ms = b.legalMoves();
  return ms[rnd() % ms.size()];
}
