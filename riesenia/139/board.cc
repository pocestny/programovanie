#include "board.h"

#include <cstdlib>
#include <sstream>
#include <string>

using namespace std;

bool Square::legal() {
  if (r < 0 || r > 7) return false;
  if (f < 0 || f > 7) return false;
  return true;
}

Board::Board() {
  ply = 0;
  pmap[0] = 0x303030303030303ULL;
  pmap[1] = 0xc0c0c0c0c0c0c0c0ULL;
}

bool Board::operator==(const Board &b) const {
  return pmap[0] == b.pmap[0] && pmap[1] == b.pmap[1] && ply == b.ply;
}

uint64_t Board::idx(int f, int r) const {
  return (uint64_t)1 << ((uint8_t)((f << 3) | r));
}

uint8_t Board::get(int f, int r) const {
  uint64_t i = idx(f, r);
  for (int s = 0; s < 2; s++)
    if (pmap[s] & i) return s;
  return Empty;
}

void Board::set(int f, int r, uint8_t val) {
  uint64_t i = idx(f, r);
  for (int z = 0; z < 2; z++)
    if (val == z)
      pmap[z] |= i;
    else
      pmap[z] &= ~i;
}

int Board::winner() const {
  if (pmap[0] == 0 || pmap[1] & 0x0101010101010101ULL) return Black;
  if (pmap[1] == 0 || pmap[0] & 0x8080808080808080ULL) return White;
  return Empty;
}

bool Board::legal(Move m) const {
  if (!(m.from.legal() && m.to.legal())) return false;
  if (get(m.from.f, m.from.r) != ply % 2) return false;
  int tr = m.from.r;
  if (ply % 2 == 0)
    tr++;
  else
    tr--;
  if (m.to.r != tr) return false;
  if (abs(m.from.f - m.to.f) > 1) return false;
  if (get(m.to.f, m.to.r) == Empty) return true;
  if (m.to.f != m.from.f && get(m.to.f, m.to.r) != ply % 2) return true;
  return false;
}

vector<Move> Board::legalMoves() const {
  vector<Move> res;
  int dr = 1;
  if (ply % 2 == 1) dr = -1;
  for (int f = 0; f < 8; f++)
    for (int r = 0; r < 8; r++)
      if (get(f, r) == ply % 2) {
        Square src{(uint8_t)f, (uint8_t)r};
        for (int df = -1; df < 2; df++) {
          Square dst{(uint8_t)(f + df), (uint8_t)(r + dr)};
          Move m{src, dst};
          if (legal(m)) res.push_back(m);
        }
      }
  return res;
}

Board &Board::operator+=(Move m) {
  if (!legal(m)) return *this;
  set(m.from.f, m.from.r, Empty);
  set(m.to.f, m.to.r, ply % 2);
  ply++;
  return *this;
}

int Board::toPlay() const {
  if (ply % 2) return -1;
  return 1;
}

void delim(ostream &str) {
  str << "+";
  for (int r = 0; r < 8; r++) str << "---+";
  str << endl;
}

void files(ostream &str) {
  str << " ";
  for (int f = 0; f < 8; f++) str << "   " << (char)('a' + f);
  str << endl;
}

ostream &operator<<(ostream &str, const Square &s) {
  str << (char)('a' + s.f) << s.r + 1;
  return str;
}

ostream &operator<<(ostream &str, const Move &m) {
  str << m.from << "-" << m.to;
  return str;
}

ostream &operator<<(ostream &str, const Board &b) {
  files(str);
  str << "  ";
  delim(str);
  for (int r = 7; r >= 0; r--) {
    str << r + 1 << " |";
    for (int f = 0; f < 8; f++) {
      char c = ' ';
      if (b.get(f, r) == White) c = 'X';
      if (b.get(f, r) == Black) c = 'O';
      str << " " << c << " |";
    }
    str << " " << (int)(r + 1) << std::endl << "  ";
    delim(str);
  }
  files(str);
  return str;
}

istream &operator>>(istream &str, Square &sq) {
  string s;
  str >> s;
  if (s.size() >= 2) {
    sq.f = s[0] - 'a';
    sq.r = s[1] - '1';
  }
  return str;
}

istream &operator>>(istream &str, Move &m) {
  string s;
  str >> s;
  if (s.size() >= 5) {
    m.from.f = s[0] - 'a';
    m.from.r = s[1] - '1';
    m.to.f = s[3] - 'a';
    m.to.r = s[4] - '1';
  }
  return str;
}

istream &operator>>(istream &str, Board &b) {
  b.pmap[0] = b.pmap[1] = 0;
  string s;
  for (int i = 0; i < 2; i++) {
    getline(str, s, ';');
    stringstream ss(s);
    Square sq;
    while (ss >> sq) b.set(sq.f, sq.r, i);
  }
  str >> b.ply;
  return str;
}

uint64_t std::hash<Board>::murmur64(uint64_t x) const {
  x ^= x >> 27;
  x *= 0x3C79AC492BA7B653ULL;
  x ^= x >> 33;
  x *= 0x1C69B3F74AC4AE35ULL;
  x ^= x >> 27;
  return x;
}

uint64_t std::hash<Board>::operator()(const Board &b) const {
  return murmur64(b.pmap[0] ^ 0xFEEDDADBEEFull) ^ murmur64(b.pmap[1]) ^
         murmur64(b.ply);
}

bool Board::safe(const Square s) const {
  int sd = get(s.f, s.r);
  uint8_t nf, f = s.f, rAtk = s.r + 1 - 2 * sd, rDef = s.r - 1 + 2 * sd;
  if (rAtk > 7) return true;
  int nAtk = 0, nDef = 0;
  for (int d : {-1, 1}) {
    nf = (uint8_t)(f + d);
    if (nf < 8 && get(nf, rAtk) == (1 - sd)) nAtk++;
    if (rDef < 8 && nf < 8 && get(nf, rDef) == sd) nDef++;
  }

  return nDef >= nAtk;
}
