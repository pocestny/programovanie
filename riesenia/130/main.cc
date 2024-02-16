#include <random>

#include "alphabetaplayer.h"
#include "basicalphabetaplayer.h"

using namespace std;

template <typename P1, typename P2>
int duel() {
  P1 p1;
  P2 p2;
  Board b;
  cout << "duel\n";
  while (true) {
    Move m = p1.findMove(b);
    b += m;
    cout << b << endl;
    if (b.winner() == White) return 1;
    m = p2.findMove(b);
    b += m;
    cout << b << endl;
    if (b.winner() == Black) return -1;
  }
}

int main() {
  int s[2] = {0, 0};

  for (int cnt = 0; cnt < 10; cnt++) {
    int res = duel<AlphaBetaPlayer, BasicAlphaBetaPlayer>();
    if (res == 1)
      s[0]++;
    else
      s[1]++;
  }
  cout << s[0] << " : " << s[1] << endl;
}
