#ifndef __MINIMAX_PLAYER__
#define __MINIMAX_PLAYER__

#include <random>

#include "board.h"

struct MinimaxPlayer {
  struct MoveValue {
    Move m;
    float val;
  };

  std::mt19937 rnd;
  MinimaxPlayer();
  Move findMove(const Board& b);
  MoveValue minimax(const Board& b, int hlbka);
  float eval(const Board& b);
};

#endif
