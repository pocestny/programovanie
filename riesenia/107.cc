#include <ctime>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

unsigned long mod(string s, unsigned long p) {
  ifstream f(s, ios::binary);
  f.seekg(0, ios::end);
  int n = f.tellg();
  f.seekg(0, ios::beg);

  unsigned long mod = 0;
  unsigned char x;
  for (unsigned long i = 0; i < n; i++) {
    f.read((char *)&x, 1);
    mod = ((mod << 8) | x) % p;
  }
  return mod;
}

int main() {
  string s;
  unsigned long p;
  cin >> s >> p;
  cout << mod(s, p) << endl;
}
