#include <iostream>
using namespace std;

int main() {
  int n, z = 0;
  cin >> n;
  while (n > 1) {
    for (int i = 5; i <= n; i = i * 5)
      if (n % i == 0) z++;
    n--;
  }
  cout << z << endl;
}
