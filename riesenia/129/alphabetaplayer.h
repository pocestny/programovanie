#ifndef __ALPHABETA_PLAYER__
#define __ALPHABETA_PLAYER__

#include <random>

#include "board.h"

struct AlphaBetaPlayer {
  struct MoveValue {
    Move m;
    float val;
  };

  std::mt19937 rnd;
  AlphaBetaPlayer();
  Move findMove(const Board& b);
  MoveValue search(const Board& b, int hlbka, double alpha, double beta);
  float eval(const Board& b);
};

#endif
