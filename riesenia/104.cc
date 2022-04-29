#include <algorithm>
#include <fstream>
#include <functional>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Data {
  int freq, val;
  bool operator<(const Data &x) {
    if (x.freq == freq) return val < x.val;
    return freq > x.freq;
  }
};

void msg(char **argv) {
  cerr << argv[0] << " [-n <len>]  [-d] infile outfile\n";
  exit(1);
}
int main(int argc, char **argv) {
  if (argc < 2) msg(argv);

  int N = 3;
  bool decode = false;

  for (int i = 1; i < argc - 2; i++)
    if (string(argv[i]) == "-n")
      N = atoi(argv[i]);
    else if (string(argv[i]) == "-d")
      decode = true;

  fstream in(argv[argc - 2], ios::in | ios::binary);
  fstream out(argv[argc - 1], ios::out | ios::binary);
  in.seekg(0, ios::end);
  int n = in.tellg();
  vector<unsigned char> a(n);
  in.seekg(0, ios::beg);
  in.read((char *)a.data(), n);

  vector<unsigned char> b(n);               // vystupny vektor
  unordered_map<string, vector<Data>> prd;  // prediktor pre jednotlive kontexty
  /*
   * Data si udrzujem utriedene podla pocetnosti
   *
   * Nechcem si pre kazdy kontext pamatat frekvencie vsetky znakov, napr. Data[256],
   * lebo by to zabralo privela pamate a bolo by to treba zakazdym inicializovat
   * aj pre kontexty, v ktorych vidim malo roznych pismeniek.
   * Namiesto toho si budem pamatat iba tie pismenka, ktore som uz videl, a ak pride
   * take, ktore som este nevidel, jeho poradie si viem dorata (pismenka s nulovou 
   * frekvenciou mam 'virtualne' utriedene podla velkosti
   */

  string ctx;
  for (int i = 0; i < min(N, n); i++) {  // zaciatok sa len skopiruje
    b[i] = a[i];
    ctx.push_back(a[i]);
  }

  for (int i = N; i < n; i++) {
    auto &v = prd[ctx];  // kontext, v ktorom sme

    if (decode) {
      /*
       * odkodovavanie
       */
      if (a[i] >= v.size()) { // bolo to pismenko, ktore som este nevidel,
                              // musim vyratat jeho poziciu
        b[i] = a[i] - v.size();
        sort(v.begin(), v.end(), [](const Data &a, const Data &b) {
          if (a.val == b.val) return a.freq > b.freq;
          return a.val < b.val;
        });
        for (auto &x : v)
          if (x.val <= b[i]) b[i]++;
        v.push_back({1,b[i]});
      } else { // pismenko som uz videl: najdem si ho a zvysim jeho frekvenciu
        b[i] = v[a[i]].val;
        v[a[i]].freq++;
      }
      sort(v.begin(), v.end());
      ctx.push_back(b[i]);
    } else {
      /*
       * zakodovavanie
       */
      int nums = 0, j;
      for (j = 0; j < v.size(); j++) { // zisti, ci som take pismeno uz videl
                                       // a pritom najdi pocet mensich
        if (v[j].val == a[i]) break;
        if (v[j].val < a[i]) nums++;
      }
      if (j == v.size()) { // ak som ho nevidel, vyratam jeho poziciu
        b[i] = v.size() + a[i] - nums;
        v.push_back({1, a[i]});
      } else { // ak som to pismenko uz videl, zvysim mu frekvenciu
               // a vratim jeho poradie (v usporiadani podla pocetnosti)
        b[i] = j;
        v[j].freq++;
      }
      sort(v.begin(), v.end()); // aktualizujem poradie
      ctx.push_back(a[i]);
    }
    ctx = ctx.substr(1); // posuniem kontext
  }
  out.write((char *)b.data(), n);
}
