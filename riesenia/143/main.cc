#include <algorithm>
#include <cmath>
#include <iostream>

#include "network.h"

using namespace std;

bool prime(int n) {
  if (n < 2) return false;
  for (int i = 2; i < min(n, (int)sqrt(n) + 2); i++)
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

  Network net{n, 8, 6, 1};
  net.randomInit(-1e-2,1e-2);
  double step = 0.6;
  int epoch = 0;
  while (++epoch) {
    net.backPropagation(data, truth);
    auto err = net.error(net.output(), truth);
    int good = 0;
    for (int i = 0; i < truth.m; i++)
      if (net.output()(0, i) * truth(0, i) > 0) good++;
    cout << epoch << " " << err << " " << good << endl;
    if (good == 1 << n) break;
    auto g = net.gradient(data);
    net.apply(step, g);
    if (epoch%5000==0) 
      net.randomInit(-1e-2,1e-2);
  }
  cout<<epoch<<endl;
}
