#include <algorithm>
#include <chrono>
#include <random>
#include <iostream>
#include <vector>

using namespace std;
using namespace chrono;

template <typename F>
int meraj(F f) {
  auto start = system_clock::now();
  f();
  auto end = system_clock::now();
  return duration_cast<milliseconds>(end - start).count();
}

int main() {
  mt19937 rnd(random_device{}());
  for (int n = 10000; n < 1000000; n += 10000) {
    vector<int> a(n);
    double t = 0;
    const double rep = 10;
    for (int cnt = 0; cnt < rep; cnt++) {
      for (int &x : a) x = rnd();
      t += meraj([&a]() { sort(a.begin(), a.end()); });
    }
    cout << n << " " << t / rep << endl;
  }
}
