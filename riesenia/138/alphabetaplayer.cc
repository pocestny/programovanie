#include "alphabetaplayer.h"

#include <algorithm>
#include <chrono>
#include <vector>

using namespace std;

AlphaBetaPlayer::AlphaBetaPlayer()
    : rnd(random_device{}()), running{true}, sem(0), worker([this]() {
        while (true) {
          sem.acquire();
          Board b;
          {
            lock_guard g(mtx);
            if (!running) return;
            b = startingBoard;
          }
          Move m = findMove(b);
          {
            lock_guard g(mtx);
            foundMove = m;
          }
        }
      }) {}

AlphaBetaPlayer::~AlphaBetaPlayer() {
  {
    lock_guard g(mtx);
    running = false;
  }
  sem.release();
  worker.join();
}

void AlphaBetaPlayer::startThinking(const Board& b) {
  {
    lock_guard g(mtx);
    startingBoard = b;
    foundMove = Move{{9, 9}, {9, 9}};
  }
  sem.release();
}

Move AlphaBetaPlayer::getMove() {
  lock_guard g(mtx);
  Move m = foundMove;
  foundMove = Move{{9, 9}, {9, 9}};
  return m;
}

Move AlphaBetaPlayer::findMove(const Board& b) {
  using namespace chrono;
  auto start = system_clock::now();
  auto ms = b.legalMoves();
  int n = ms.size();
  vector<MoveValue> mv(n);
  for (int h = 2; h <= 5; h++)
    for (int i = 0; i < n; i++) {
      mv[i].m = ms[i];
      Board bb = b;
      bb += ms[i];
      mv[i].val = -search(bb, h, -1e20, 1e20).val;
    }

  sort(mv.begin(), mv.end(),
       [](const MoveValue& a, const MoveValue& b) { return a.val > b.val; });
  int nbest;
  for (nbest = 1; nbest < n && mv[nbest].val == mv[0].val; nbest++)
    ;
  auto end = system_clock::now();
  cout << "AlphaBeta player:" << endl;
  cout << "   time:    " << duration_cast<milliseconds>(end - start).count()
       << endl;
  cout << "   TT size: " << tt.size() << endl;

  return mv[rnd() % nbest].m;
}

AlphaBetaPlayer::MoveValue AlphaBetaPlayer::search(const Board& b, int hlbka,
                                                   float alpha, float beta) {
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
  if (ms.size() == 0) return {Move(), 0};

  {  // skúsim nájsť v transpozičnej tabuľke
    auto it = tt.find(b);
    if (it != tt.end()) {
      auto& e = it->second;
      if (e.hlbka >= hlbka) {
        if (e.lb >= beta) return {e.m, e.lb};
        if (e.ub <= alpha) return {e.m, e.ub};
        alpha = std::max(alpha, e.lb);
        beta = std::min(beta, e.ub);
      }
    }
  }
  float alphaOrig = alpha;

  {  // utriedim ťahy
    vector<MoveValue> tmp;
    tmp.reserve(ms.size());
    for (auto m : ms) {
      Board bb = b;
      bb += m;
      float val = bb.toPlay() * eval(bb);

      auto it = tt.find(bb);
      if (it != tt.end())
        val = std::min(it->second.ub, std::max(it->second.lb, val));
      tmp.push_back(MoveValue{m, val});
    }
    sort(tmp.begin(), tmp.end());
    for (int i = 0; i < ms.size(); i++) ms[i] = tmp[i].m;
  }

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

  {
    // aktualizujem transpozičnú tabuľku
    if (tt.size() > 10000000) tt.clear();
    auto& e = tt[b];
    if (e.hlbka <= hlbka) {
      e = TTableEntry();
      e.hlbka = hlbka;
      e.m = res.m;
      if (res.val <= alphaOrig)
        e.ub = res.val;
      else if (res.val >= beta)
        e.lb = res.val;
      else
        e.ub = e.lb = res.val;
    }
  }

  return res;
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
