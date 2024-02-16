#include <algorithm>
#include <cmath>
#include <iostream>

#include "data.h"
#include "network.h"
#include "obrazok.h"
using namespace std;

const int dim = 300;

void saveImg(const string &fname, const Matrix &m) {
  int n = dim;
  uint8_t buf[4 * n * n + 7];
  double step = 2.0 / (double)n;
  int k = 0;
  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++) {
      double v = max(-1.0, min(1.0, m(0, i * n + j)));
      uint8_t c = (uint8_t)((v + 1.0) * 0.5 * 255.0);
      for (int _ : {0, 1, 2}) buf[k++] = c;
      buf[k++] = 255;
    }
  zapis_rgba_png(n, n, buf, fname);
}

int main() {
  Pattern pat(heartPattern(), dim);
  Network net{2, 80, 60, 1};
  net.randomInit(-1e-2, 1e-2);

  double step = 0.09;
  int epoch = 0;
  while (++epoch < 500) {
    InOut data = pat.sample(40);
    for (int c = 0; c < 200; c++) {
      net.backPropagation(data.in, data.out);
      cout << epoch << "  " << net.error(net.output(), data.out) << endl;
      auto g = net.gradient(data.in);
      net.apply(step, g);
    }
  }
  net.save("net");

  InOut data = pat.sample(-1);
  saveImg("pat.png", data.out);
  net.feed(data.in);
  saveImg("net.png", net.output());
}
