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
  bool operator==(const Square &s) { return f == s.f && r == s.r; }
};

struct Move {
  Square from, to;
  bool operator==(const Move &m) { return from == m.from && to == m.to; }
};

struct Board {
  Board();  // konštruktor - nastaví začiatočnú pozíciu

  bool operator==(const Board &b) const;
  uint64_t idx(int f, int r) const;     // bit v mape zodpovedajúci políčku
  uint8_t get(int f, int r) const;      // kto má kameň na políčku
  void set(int f, int r, uint8_t val);  // nastav políčko

  int winner() const;                    // má už pozícia víťaza?
  bool legal(Move m) const;              // je m prípustný ťah?
  std::vector<Move> legalMoves() const;  // vráť všetky prípustné ťahy
  Board &operator+=(Move m);             // urob ťah m

  int toPlay() const;  // -1 alebo 1, podľa toho, kto je na ťahu

  int ply;           // číslo polťahu
  uint64_t pmap[2];  // mapa kameňov bieleho a čierneho
                     
  bool safe(const Square s) const;
};

template <>
struct std::hash<Board> {
  uint64_t murmur64(uint64_t) const;
  uint64_t operator()(const Board &b) const;
};

std::ostream &operator<<(std::ostream &, const Square &);
std::ostream &operator<<(std::ostream &, const Move &);
std::ostream &operator<<(std::ostream &, const Board &);

std::istream &operator>>(std::istream &, Move &);
std::istream &operator>>(std::istream &, Square &);
std::istream &operator>>(std::istream &, Board &);
#endif
