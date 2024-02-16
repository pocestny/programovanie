#ifndef __BOARD_H__
#define __BOARD_H__

#include <iostream>
#include <vector>
#include <cstdint>

const uint8_t White = 0;
const uint8_t Black = 1;
const uint8_t Empty = 2;

struct Square {
  uint8_t f, r;
  bool legal();
};

struct Move {
  Square from, to;
};

struct Board {
  Board();  // konštruktor - nastaví začiatočnú pozíciu

  uint64_t idx(int f, int r) const;     // bit v mape zodpovedajúci políčku
  uint8_t get(int f, int r) const;      // kto má kameň na políčku
  void set(int f, int r, uint8_t val);  // nastav políčko

  int winner() const;                    // má už pozícia víťaza?
  bool legal(Move m) const;              // je m prípustný ťah?
  std::vector<Move> legalMoves() const;  // vráť všetky prípustné ťahy
  Board &operator+=(Move m);             // urob ťah m

  int ply;           // číslo polťahu
  uint64_t pmap[2];  // mapa kameňov bieleho a čierneho
};

std::ostream &operator<<(std::ostream &, const Square &);
std::ostream &operator<<(std::ostream &, const Move &);
std::ostream &operator<<(std::ostream &, const Board &);

#endif
