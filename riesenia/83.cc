#include <iostream>
using namespace std;
using Int = unsigned long int;

int main() {
  Int N, R;
  cin >> R >> N;
  double cx, cy;

  while (true) {
    cin >> cx >> cy;
    if (cx == 0 && cy == 0) break;
    Int iter = 0;
    double x = cx, y = cy;
    while (x * x + y * y <= R * R && iter < N) {
      double nx = x * x - y * y + cx;
      y = 2 * x * y + cy;
      x = nx;
      iter++;
    }
    if (iter >= N) cout << "ne";
    cout << "ujde" << endl;
  }
}
