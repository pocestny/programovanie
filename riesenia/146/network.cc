#include "network.h"

#include <cmath>
#include <fstream>

using namespace std;

double mse(const Matrix &data, const Matrix &truth) {
  const int n = truth.n, m = truth.m;
  Num mse = 0;
  for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++) {
      Num tmp = truth(i, j) - data(i, j);
      mse += tmp * tmp;
    }
  mse /= (Num)(n * m);
  return mse;
}

void diffMse(const Matrix &data, const Matrix &truth, Matrix &D) {
  const int n = truth.n, m = truth.m;
  if (D.n != n || D.m != m) D = Matrix(n, m);
  for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++)
      D(i, j) = -2.0 / (Num)(n * m) * (truth(i, j) - data(i, j));
}

Layer::Layer(int _n0, int _n1)
    : s{1},
      n1{_n1},
      n0{_n0},
      W(n1, n0),
      b{n1, 1},
      U(n1, 1),
      dU(1, 1),
      Y(n1, 1) {}

void Layer::activate() {
  Y = U;
  Y.apply([](Num x) { return tanh(x); });
}

void Layer::feed(const Matrix &x) {
  if (x.m != s) {
    s = x.m;
    U = Matrix(n1, s);
  }
  multInto(W, x, U);
  U.addColumn(b);
}

void Layer::backPropagation(const Layer &nxt) {
  Matrix Z = (nxt.W.transposed()) * nxt.dU;
  dU = U;
  dU.apply([this](Num x) {
    Num tmp = cosh(x);
    return 1.0 / (tmp * tmp);
  });
  dU.fill([this, &Z](int i, int j) { return dU(i, j) * Z(i, j); });
}

LayerData Layer::gradient(const Matrix &Y) {
  LayerData res{dU * Y.transposed(), Matrix(n1, 1)};
  for (int j = 0; j < n1; j++) {
    res.db(j, 0) = 0;
    for (int k = 0; k < s; k++) res.db(j, 0) += dU(j, k);
  }
  return res;
}

Network::Network(initializer_list<int> v)
    : rnd{random_device{}()}, h{v.size() - 1}, n{v} {
  layers.reserve(h);
  for (int i = 0; i < h; i++) layers.emplace_back(n[i], n[i + 1]);
}

Network::Network(const vector<int> &v)
    : rnd{random_device{}()}, h{v.size() - 1}, n{v} {
  layers.reserve(h);
  for (int i = 0; i < h; i++) layers.emplace_back(n[i], n[i + 1]);
}

void Network::randomInit(Num lo, Num hi) {
  uniform_real_distribution<> dis(lo, hi);
  auto noise = [&dis, this](int, int) { return dis(rnd); };
  for (int i = 0; i < h; i++) {
    layers[i].W.fill(noise);
    layers[i].b.fill([](int, int) { return 0; });
  }
}

Matrix &Network::feed(const Matrix &input) {
  const Matrix *x = &input;
  for (int i = 0; i < h - 1; i++) {
    layers[i].feed(*x);
    layers[i].activate();
    x = &layers[i].Y;
  }
  layers[h - 1].feed(*x);
  return layers[h - 1].U;
}

Num Network::error(const Matrix &output, const Matrix &truth) {
  return mse(output, truth);
}

void Network::backPropagation(const Matrix &input, const Matrix &truth) {
  feed(input);
  diffMse(layers[h - 1].U, truth, layers[h - 1].dU);
  for (int i = h - 2; i >= 0; i--) layers[i].backPropagation(layers[i + 1]);
}

Network::Gradient Network::gradient(const Matrix &input) {
  Gradient res(h);
  for (int i = h - 1; i > 0; i--)
    res[i] = std::move(layers[i].gradient(layers[i - 1].Y));
  res[0] = std::move(layers[0].gradient(input));
  return res;
}

void Network::apply(Num a, const Network::Gradient &g) {
  for (int t = 0; t < h; t++) {
    layers[t].W.addMultiple(-a, g[t].dW);
    layers[t].b.addMultiple(-a, g[t].db);
  }
}

void Network::addNoise(unsigned int seed, int sgn, double val) {
  mt19937 rnd;
  uniform_real_distribution<> dis(-val, val);
  rnd.seed(seed);
  for (auto &l : layers)
    for (auto m : {&l.W, &l.b})
      m->apply([&](double x) { return x + sgn * dis(rnd); });
}

void Network::save(const string &fname) const {
  ofstream f(fname, ios::out|ios::binary);
  for(auto &l:layers) {
    f.write((char*)l.W._data,l.W.size*sizeof(Num));
    f.write((char*)l.b._data,l.b.size*sizeof(Num));
  }
}

void Network::load(const string &fname)  {
  ifstream f(fname, ios::out|ios::binary);
  for(auto &l:layers) {
    f.read((char*)l.W._data,l.W.size*sizeof(Num));
    f.read((char*)l.b._data,l.b.size*sizeof(Num));
  }
}



