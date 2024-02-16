#include "minimaxplayer.h"

#include <algorithm>
#include <vector>

using namespace std;

MinimaxPlayer::MinimaxPlayer() : rnd(random_device{}()) {}

Move MinimaxPlayer::findMove(const Board& b) {
  auto ms = b.legalMoves();
  int n = ms.size();
  vector<MoveValue> mv(n);
  for (int i = 0; i < n; i++) {
    mv[i].m = ms[i];
    Board bb = b;
    bb += ms[i];
    mv[i].val = -minimax(bb, 4).val;
  }
  sort(mv.begin(), mv.end(),
       [](const MoveValue& a, const MoveValue& b) { return a.val > b.val; });
  int nbest;
  for (nbest = 1; nbest < n && mv[nbest].val == mv[0].val; nbest++)
    ;
  return mv[rnd() % nbest].m;
}

MinimaxPlayer::MoveValue MinimaxPlayer::minimax(const Board& b, int hlbka) {
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
  auto ms = b.legalMoves();
  res.val = -2;

  for (int i = 0; i < ms.size(); i++) {
    Board bb = b;
    bb += ms[i];
    float v = -minimax(bb, hlbka - 1).val;

    if (v > res.val) {
      res.val = v;
      res.m = ms[i];
    }
  }
  return res;
}

float MinimaxPlayer::eval(const Board& b) {
  int num[3] = {0, 0, 0};

  for (int f = 0; f < 8; f++)
    for (int r = 0; r < 8; r++) num[b.get(f,r)]++;
  return (float)(num[White] - num[Black]) / 16.0;
}
