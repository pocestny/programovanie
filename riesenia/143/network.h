#ifndef __NETWORK_H__
#define __NETWORK_H__

#include <functional>
#include <random>
#include <string>

#include "matrix.h"

struct LayerData {
  Matrix dW, db;
};

struct Layer {
  int s;        // current batch size
  int n1;       // size of the layer
  int n0;       // size of previous layer
  Matrix W, b;  // W: n1 x n0 w_ij = weight from j-th previous to i-th
                // b: column n1 x 1

  Matrix U, Y;  // n1 x s : values (before and after activation)
  Matrix dU;    // d Loss / d U

  Layer(int _n0 = 1, int _n1 = 1);
  void feed(const Matrix&);  // feed input, set U
  void activate();
  void backPropagation(const Layer& nxt);  // set dU
  LayerData gradient(const Matrix& Y);     // get dW, dB based on dU
};

struct Network {
  std::mt19937 rnd;
  const size_t h;            // layers
  const std::vector<int> n;  // input size, dimensions of layers
  std::vector<Layer> layers;

  using Gradient = std::vector<LayerData>;

  Network(std::initializer_list<int>);
  Network(const std::vector<int>&);
  void randomInit(Num, Num);
  Matrix& feed(const Matrix&);
  Matrix& output() { return layers[h - 1].U; }
  Num error(const Matrix& output, const Matrix& truth);

  void backPropagation(const Matrix& input,
                       const Matrix& truth);  // feed input, and setup dUs
  Gradient gradient(const Matrix& input);     // get gradient, based on backProp

  void apply(Num a, const Gradient& g);
  void addNoise(unsigned int seed, int sgn = 1, double val = 1e-3);
};

#endif
