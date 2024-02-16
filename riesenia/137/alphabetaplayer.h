#ifndef __ALPHABETA_PLAYER__
#define __ALPHABETA_PLAYER__

#include <random>

#include "board.h"

struct AlphaBetaPlayer {
  struct MoveValue {
    Move m;
    float val;
    bool operator<(const MoveValue& x) { return val < x.val; }
  };

  struct State {
    Board b;
    int hlbka;
    double alpha, beta;
    MoveValue res;
    std::vector<MoveValue> moves;
    int currentMove;

    State(const Board& _b, int _h, double _alpha = -1e20, double _beta = 1e20);
    bool set(float v); // set value for currentMove, true = res is final
  };

  std::mt19937 rnd;
  std::vector<State> states;
  bool thinking,finished;

  AlphaBetaPlayer();

  void startThinking(const Board& b);
  void step();
  void pop();
  Move getResult();

  float eval(const Board& b);
};

#endif
