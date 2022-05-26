#include <chrono>
#include <iostream>

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
  cout << meraj([]() {
    int x;
    for (int i = 0; i < 1000000000; i++) x++;
  }) << endl;
}
