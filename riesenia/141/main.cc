#include <iostream>
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

Layer::Layer(int _n0, int _n1) :  n1{_n1}, n0{_n0}, W(n1, n0), b{n1, 1} {}

Matrix Layer::eval(const Matrix &X) {
  Matrix res = W * X;
  res.addColumn(b);
  res.apply([](double x) { return (x > 0) ? 1.0 : 0.0; });
  return res;
}

int main() {
  int n;
  cin >> n;
  Matrix x(n, 1);
  Layer l1(n, n), l2(n, 1);

  for (int i = 0; i < n; i++) cin >> x(i, 0);

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) l1.W(i, j) = (i == j) ? 1 : -1;
    l1.b(i, 0) = 0;
  }

  for (int i = 0; i < n; i++) l2.W(0, i) = 2;
  l2.b(0, 0) = -1;

  auto y = l1.eval(x);
  auto z = l2.eval(y);

  cout << z(0, 0) << endl;
}
