#ifndef __DATA_H__
#define __DATA_H__

#include <functional>
#include <random>

#include "matrix.h"

using u8 = uint8_t;
using u32 = uint32_t;

struct InOut {
  Matrix in, out;
  InOut(int inSize = 1, int outSize = 1, int batchSize = 1)
      : in(inSize, batchSize), out(outSize, batchSize) {}
};

struct Data {
  static constexpr int dim = 26;
  static constexpr int sc = 18;
  static constexpr int iDim = 128;
  static constexpr char binDir[] = "./mnist";
  std::mt19937_64 rnd;

  struct Point {
    int _p[2];
    Point &operator=(const Point &a);
    int &x() { return _p[0]; }
    int &y() { return _p[1]; }
    int x() const { return _p[0]; }
    int y() const { return _p[1]; }
    int &operator[](int i) { return _p[i]; }
    int operator[](int i) const { return _p[i]; }
    Point &operator+=(const Point &p);
    Point &operator*=(double a);
  };

  struct Box {
    Point p[2];
    Point &operator[](int i) { return p[i]; }
    Point operator[](int i) const { return p[i]; }
    int x() const { return p[1].x() - p[0].x(); }
    int y() const { return p[1].y() - p[0].y(); }
    Box &expand(const Point &q);
    Point center() const;
  };

  struct Bytes {
    std::vector<u8> a;
    int d, n;
    u8 sentinel;
    Bytes(int _d) : d{_d}, n{d * d} { a.resize(n, 0xff); }
    u8 &operator()(int x, int y);
    u8 operator()(int x, int y) const;
    Point pos(int i) const { return Point{i % d, i / d}; }
    Point cog() const;
    Box bbox() const;
  };

  Data(uint32_t _seed = std::random_device{}()) : rnd{_seed} {}

  void processImage(Bytes &in, Bytes &out);
  void loadDataset();

  std::vector<std::vector<Bytes>> dataset;
  std::vector<int> trainSizes;

  std::vector<int> size() const;
  void setTrainSizes(double ratio = 0.8);
  void shuffle();
  InOut sample(int s = -1);
  InOut test();
  void addCol(InOut &res, int c, int num, int n);
};

Data::Point operator+(const Data::Point &a, const Data::Point &b);
Data::Point operator*(double a, const Data::Point &q);
std::ostream &operator<<(std::ostream &str, const Data::Point &p);

#endif
