#include "obrazok.h"
#include <complex>
#include <iostream>
#include <string>
#include <vector>

using namespace std;
using Byte = unsigned char;
using Int = unsigned long int;
using Complex = complex<double>;

struct RGBA {
  Byte r, g, b, a;
  RGBA(Byte _r = 255, Byte _g = 255, Byte _b = 255, Byte _a = 255) {
    r = _r;
    g = _g;
    b = _b;
    a = _a;
  }

  RGBA(const char* hex) {  // #rrggbb[aa]
    unsigned int val = 0;
    for (auto s = hex + 1; *s != 0; s++) {
      Byte c;
      if (*s >= '0' && *s <= '9')
        c = (*s) - '0';
      else if (*s >= 'a' && *s <= 'f')
        c = (*s) - 'a' + 10;
      else if (*s >= 'A' && *s <= 'F')
        c = (*s) - 'A' + 10;
      val = (val << 4) | c;
    }
    if (val < (1 << 25)) val = (val << 8) | 255;
    r = (Byte)(val >> 24);
    g = (Byte)((val >> 16) & 255);
    b = (Byte)((val >> 8) & 255);
    a = (Byte)(val & 255);
  }
};

int main() {
  Int N, R;
  int width, height;
  Complex stred;
  double m;

  int ps;
  cin >> ps;
  vector<RGBA> paleta;
  for (int i = 0; i < ps; i++) {
    string s;
    cin >> s;
    paleta.push_back(RGBA(s.data()));
  }

  cin >> R >> N >> width >> height >> stred >> m;

  vector<RGBA> obrazok;
  obrazok.resize(width * height);

  double pixel = 1 / ((double)width * m);

  for (int i = 0; i < height; i++)
    for (int j = 0; j < width; j++) {
      Complex c = stred + Complex(j - width / 2, i - height / 2) * pixel;
      Int iter = 0;
      Complex z = c;
      while (norm(z) <= R * R && iter < N) {
        z = z * z + c;
        iter++;
      }
      if (iter >= N)
        obrazok[i * width + j] = RGBA(0, 0, 0);
      else
        obrazok[i * width + j] = paleta[iter % paleta.size()];
    }
  zapis_rgba_png(height, width, obrazok.data(), "93.png");
}
