#include "basicalphabetaplayer.h"

#include <algorithm>
#include <chrono>
#include <vector>

using namespace std;

BasicAlphaBetaPlayer::BasicAlphaBetaPlayer() : rnd(random_device{}()) {}

Move BasicAlphaBetaPlayer::findMove(const Board& b) {
  using namespace chrono;
  auto start = system_clock::now();
  auto ms = b.legalMoves();
  int n = ms.size();
  vector<MoveValue> mv(n);
  for (int i = 0; i < n; i++) {
    mv[i].m = ms[i];
    Board bb = b;
    bb += ms[i];
    mv[i].val = -search(bb, 5, -1e20, 1e20).val;
  }
  sort(mv.begin(), mv.end(),
       [](const MoveValue& a, const MoveValue& b) { return a.val > b.val; });
  int nbest;
  for (nbest = 1; nbest < n && mv[nbest].val == mv[0].val; nbest++)
    ;
  auto end = system_clock::now();
  cout<<"BasicAlphaBeta time:" << duration_cast<milliseconds>(end - start).count() << endl;
  return mv[rnd() % nbest].m;
}

BasicAlphaBetaPlayer::MoveValue BasicAlphaBetaPlayer::search(const Board& b, int hlbka,
                                                   double alpha, double beta) {
  MoveValue res;
  int side = b.toPlay();
  int w = b.winner();
  if (w == White) {
    res.val = side;
    return res;
  }
  if (w == Black) {
    res.val = -side;
    return res;
  }

  if (hlbka == 0) {
    res.val = side * eval(b);
    return res;
  }
  res.val = -2;

  auto ms = b.legalMoves();
  for (int i = 0; i < ms.size(); i++) {
    Board bb = b;
    bb += ms[i];
    float v = -search(bb, hlbka - 1, -beta, -alpha).val;
    if (v > res.val) {
      res.val = v;
      res.m = ms[i];
    }
    if (res.val > alpha) alpha = res.val;
    if (alpha >= beta) break;
  }
  return res;
}

float BasicAlphaBetaPlayer::eval(const Board& b) {
  int num[3] = {0, 0, 0};

  for (int f = 0; f < 8; f++)
    for (int r = 0; r < 8; r++) num[b.get(f, r)]++;
  return (float)(num[White] - num[Black]) / 16.0;
}
