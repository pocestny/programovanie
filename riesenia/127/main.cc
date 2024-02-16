#include <random>

#include "board.h"

using namespace std;

int value(const Board &b) {
  int side = b.toPlay();  // 1, -1 podľa toho, kto je na ťahu
  int w = b.winner();
  if (w == White)
    return side;  // ak vyhral biely a je na ťahu, tak 1
                  // ak je na ťahu čierny, tak -1
  if (w == Black) return -side;

  auto ms = b.legalMoves();  // vyrobím všetky prípustné ťahy
  int mx = -1;               // hodnota z pohľadu toho, kto je na ťahu

  for (int i = 0; i < ms.size(); i++) {
    Board bb = b;
    bb += ms[i];
    int v = -value(bb);  // rekurzívne vyrátaj hodnotu nasledovníka
                         // výsledok je z pohľadu protivníka,
                         // z môjho pohľadu je preto opačný
    if (v > mx) mx = v;
    if (mx == 1) break;  // lepšie už nemôže byť, netreba pokračovať
  }
  return mx;
}

int main() {
  Board b;
  cin >> b;

  while (b.winner() == Empty) {
    cout << b << endl << b.toPlay() * value(b) << endl;
    auto ms = b.legalMoves();
    for (int i = 0; i < ms.size(); i++) {
      Board bb = b;
      bb += ms[i];
      cout << ms[i] << ": " << bb.toPlay() * value(bb) << endl;
    }
    cout << ": ";
    Move m;
    cin >> m;
    b += m;
  }
}
