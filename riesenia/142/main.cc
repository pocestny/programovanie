#include <cmath>
#include <cstdio>
#include <initializer_list>
#include <iostream>
#include <random>
#include <vector>

#include "matrix.h"

using namespace std;

struct Layer {
  int n1;       // počet neurónov vo vrstve
  int n0;       // veľkosť predchádzajúcej vrstvy (vstupu)
  Matrix W, b;  // W: n1 x n0, kde w[i,j] = váha i-teho neurónu k j-temu vstupu
                // b: stĺpec n1 x 1
  Layer(int _n0, int _n1);      // konštruktor
  Matrix eval(const Matrix &);  // vstup n0 x s, výstup n1 x s hodnoty neurónov
};

Layer::Layer(int _n0, int _n1) : n1{_n1}, n0{_n0}, W(n1, n0), b{n1, 1} {}

Matrix Layer::eval(const Matrix &X) {
  Matrix res = W * X;
  res.addColumn(b);
  // res.apply([](double x) { return (x > 0) ? 1.0 : 0.0; });
  res.apply([](double x) { return tanh(x); });
  return res;
}

struct Network {
  const unsigned long int h;  // počet vrstiev
  const vector<int> n;        // veľkosti vrstiev, n[0] je veľkosť vstupu
  vector<Layer> layers;       // vrstvy
  Network(initializer_list<int>);  // konštruktory
  Network(const vector<int> &);
  Matrix feed(const Matrix &);
  void addNoise(unsigned int seed, int sgn = 1, double val = 1e-3);
};

Network::Network(initializer_list<int> v) : h{v.size() - 1}, n{v} {
  for (int i = 0; i < h; i++) layers.emplace_back(Layer(n[i], n[i + 1]));
}

Network::Network(const vector<int> &v) : h{v.size() - 1}, n{v} {
  for (int i = 0; i < h; i++) layers.emplace_back(Layer(n[i], n[i + 1]));
}

Matrix Network::feed(const Matrix &x) {
  Matrix res(x);
  for (auto &l : layers) res = l.eval(res);
  return res;
}

void Network::addNoise(unsigned int seed, int sgn, double val) {
  mt19937 rnd;
  uniform_real_distribution<> dis(-val, val);
  rnd.seed(seed);
  for (auto &l : layers)
    for (auto m : {&l.W, &l.b})
      m->apply([&](double x) { return x + sgn * dis(rnd); });
}

double mse(const Matrix &answer, const Matrix &truth) {
  const int n = truth.n, m = truth.m;

  double err = 0;
  for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++) {
      double tmp = truth(i, j) - answer(i, j);
      err += tmp * tmp;
    }
  err /= (double)(n * m);
  return err;
}

bool prime(int n) {
  if (n < 2) return false;
  for (int i = 2; i < sqrt(n) + 2; i++)
    if (n % i == 0) return false;
  return true;
}

int main() {
  int n = 8;
  Matrix data(n, 1 << n), truth(1, 1 << n);

  for (int i = 0; i < (1 << n); i++) {
    truth(0, i) = prime(i) ? 1.0 : -1.0;
    for (int j = 0; j < n; j++) data(j, i) = (i & (1 << j)) ? 1.0 : -1.0;
  }

  Network net{n, 16, 8, 1};
  net.addNoise(random_device{}(), 1, 0.01);
  mt19937 rnd(random_device{}());

  double last_err = 1e50;
  Matrix answer;
  int cnt = 0;
  do {
    auto seed = rnd();
    net.addNoise(seed);
    answer = net.feed(data);
    auto err = mse(answer, truth);
    if (err < last_err)
      last_err = err;
    else
      net.addNoise(seed, -1);
    cout << cnt++ << " " << last_err << endl;
  } while (last_err > 5e-3);

  int numOk = 0, numBad = 0;
  for (int i = 0; i < (1 << n); i++) {
    int t = truth(0, i), out = (answer(0, i) > 0) ? 1 : -1;
    if (t == out)
      numOk++;
    else {
      cout << i << " " << t << " " << answer(0, i) << endl;
      numBad++;
    }
  }
  cout << "ok: " << numOk << "   bad: " << numBad << endl;
}
