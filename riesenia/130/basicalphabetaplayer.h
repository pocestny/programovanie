#ifndef __BASIC_ALPHABETA_PLAYER__
#define __BASIC_ALPHABETA_PLAYER__

#include <random>

#include "board.h"

struct BasicAlphaBetaPlayer {
  struct MoveValue {
    Move m;
    float val;
  };

  std::mt19937 rnd;
  BasicAlphaBetaPlayer();
  Move findMove(const Board& b);
  MoveValue search(const Board& b, int hlbka, double alpha, double beta);
  float eval(const Board& b);
};

#endif
