#ifndef __RANDOM_PLAYER__
#define __RANDOM_PLAYER__

#include <random>

#include "board.h"

struct RandomPlayer {
  std::mt19937 rnd;
  RandomPlayer();
  Move findMove(const Board& b);
};

#endif
