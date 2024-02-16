#include "alphabetaplayer.h"

#include <algorithm>
#include <chrono>
#include <vector>


using namespace std;

AlphaBetaPlayer::AlphaBetaPlayer() : rnd(random_device{}()), thinking{false} {}

AlphaBetaPlayer::State::State(const Board& _b, int _h, double _alpha, double _beta) {
  b = _b;
  hlbka = _h;
  alpha = _alpha;
  beta = _beta;
  res.val = -2e20;
  auto ms = b.legalMoves();
  moves.resize(ms.size());
  for (int i = 0; i < moves.size(); i++) moves[i].m = ms[i];
  currentMove = 0;
}

bool AlphaBetaPlayer::State::set(float v) {
  moves[currentMove].val = v;
  if (v > res.val) {
    res.val = v;
    res.m = moves[currentMove].m;
  }
  if (res.val > alpha) alpha = res.val;
  currentMove++;
  return (alpha>beta)  || (currentMove == moves.size());
}

void AlphaBetaPlayer::startThinking(const Board& b) {
  finished = false;
  thinking = true;
  states.clear();
  states.push_back(State(b, 5));
}

void AlphaBetaPlayer::step() {
  State& s = states.back();

  if (s.hlbka == 0) {
    s.res.val = s.b.toPlay() * eval(s.b);
    pop();
    return;
  }

  Move m = s.moves[s.currentMove].m;
  Board bb = s.b;
  bb += m;

  int side = bb.toPlay();
  int w = bb.winner();
  if (w == White) {
    if (s.set(-side)) pop();
    return;
  }
  if (w == Black) {
    if (s.set(side)) pop();
    return;
  }

  states.push_back(State(bb, s.hlbka - 1, -s.beta, -s.alpha));
}

void AlphaBetaPlayer::pop() {
  if (states.size() == 1) {
    finished = true;
    return;
  }
  float v = -states.back().res.val;
  states.pop_back();
  if (states.back().set(v)) pop();
}

Move AlphaBetaPlayer::getResult() {
  State& s = states.back();
  
  sort(s.moves.begin(), s.moves.begin() + s.currentMove,
       [](const MoveValue& a, const MoveValue& b) { return a.val > b.val; });
  int nbest;
  for (nbest = 1; nbest < s.currentMove && s.moves[nbest].val == s.moves[0].val;
       nbest++)
    ;
  thinking = false;

  return s.moves[rnd() % nbest].m;
}


float AlphaBetaPlayer::eval(const Board& b) {
  constexpr static int8_t boardVal[8][8] = {
      {5, 15, 15, 5, 5, 15, 15, 5},     {2, 3, 3, 3, 3, 3, 3, 2},
      {4, 6, 6, 6, 6, 6, 6, 4},         {7, 10, 10, 10, 10, 10, 10, 7},
      {11, 15, 15, 15, 15, 15, 15, 11}, {16, 21, 21, 21, 21, 21, 21, 16},
      {20, 28, 28, 28, 28, 28, 28, 20}, {36, 36, 36, 36, 36, 36, 36, 36}};

  int16_t nump[2]{0, 0}, pv[2]{0, 0};

  for (int s : {0, 1})
    for (uint8_t f = 0; f < 8; f++)
      for (uint8_t r = 0; r < 8; r++)
        if (b.get(f, r) == s) {
          nump[s]++;
          uint8_t rr = r;
          if (s == 1) rr = 7 - r;
          int8_t v = boardVal[rr][f];
          if (b.safe({f, r})) v += v >> 1;
          pv[s] += v;
        }
  nump[0] -= nump[1];
  if (nump[0] > 0)
    pv[0] += 10 * nump[0];
  else
    pv[1] += -10 * nump[0];
  return (float)(pv[0] - pv[1]) / 1234.0;
}
