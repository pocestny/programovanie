#ifndef __DATA_H__
#define __DATA_H__

#include <functional>
#include <random>

#include "matrix.h"

struct InOut {
  Matrix in, out;
  InOut(int inSize = 1, int outSize = 1, int batchSize = 1)
      : in(inSize, batchSize), out(outSize, batchSize) {}
};

struct Pattern {
  using F = std::function<double(double, double)>;
  std::mt19937_64 rnd;
  F f;
  int dim;

  Pattern(F _f, int _dim = 100, uint32_t _seed = std::random_device{}())
      : rnd(_seed), f(_f), dim{_dim} {}
  InOut sample(int s = -1);
  InOut all();
};

Pattern::F verticalPattern(double h = 0);
Pattern::F squarePattern(int n = 2);
Pattern::F circlePattern(double r = 0.9);
Pattern::F heartPattern();

#endif
