#ifndef __ALPHABETA_PLAYER__
#define __ALPHABETA_PLAYER__

#include <random>
#include <unordered_map>
#include <thread>
#include <semaphore>
#include <mutex>

#include "board.h"

struct AlphaBetaPlayer {
  struct MoveValue {
    Move m;
    float val;
    bool operator<(const MoveValue& x) { return val < x.val; }
  };

  struct TTableEntry {
    float ub = 100, lb = -100;
    int hlbka = -1;
    Move m;
  };

  std::mt19937 rnd;
  std::unordered_map<Board, TTableEntry> tt;

  AlphaBetaPlayer();
  ~AlphaBetaPlayer();

  bool running;
  std::counting_semaphore<1> sem;
  std::thread worker;
  Move foundMove;
  Board startingBoard;
  std::mutex mtx;

  void startThinking(const Board& b);
  Move getMove();

  Move findMove(const Board& b);
  MoveValue search(const Board& b, int hlbka, float alpha, float beta);
  float eval(const Board& b);
};

#endif
