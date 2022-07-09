#include <algorithm>
#include <functional>
#include <iostream>
#include <map>
#include <set>
#include <vector>

#include "bitwriter.h"

using namespace std;

struct Item {
  unsigned char val;
  int par = -1, freq = 0;
  int l = -1, r = -1;
};

template <typename T>
int pop(T &heap) {
  int u = *heap.begin();
  heap.erase(heap.begin());
  return u;
}

void writeDict(int v, vector<Item> &items, BitWriter<> &out) {
  if (items[v].l == -1) {
    out << true << (unsigned char)(items[v].val);
  } else {
    out << false;
    writeDict(items[v].l, items, out);
    writeDict(items[v].r, items, out);
  }
}

void compress(const string &src, const string &dst) {
  vector<unsigned char> text;
  {
    ifstream f(src, ios::in | ios::binary);
    f.seekg(0, ios::end);
    int len = f.tellg();
    f.seekg(0, ios::beg);
    text.resize(len);
    f.read((char *)(text.data()), len);
  }

  vector<int> freq(256, 0);
  for (unsigned char c : text) freq[c]++;

  vector<Item> items;
  multiset<int, function<bool(int, int)>> heap(
      [&items](int i, int j) { return items[i].freq < items[j].freq; });

  vector<int> idx(256, -1);
  for (int i = 0; i < 256; i++)
    if (freq[i] > 0) {
      int n = items.size();
      items.push_back({(unsigned char)i, -1, freq[i], -1, -1});
      heap.insert(n);
      idx[i] = n;
    }

  int n_chars = items.size();

  while (heap.size() > 1) {
    int i = pop(heap);
    int j = pop(heap);
    int n = items.size();
    items.push_back({0, -1, items[i].freq + items[j].freq});
    items[i].par = items[j].par = n;
    heap.insert(n);
  }

  for (int i = 0; i < items.size(); i++)
    if (items[i].par != -1) {
      if (items[items[i].par].l == -1)
        items[items[i].par].l = i;
      else
        items[items[i].par].r = i;
    }

  vector<vector<bool>> code(n_chars);
  for (int i = 0; i < n_chars; i++)
    for (int j = i; items[j].par != -1; j = items[j].par)
      if (items[items[j].par].l == j)
        code[i].push_back(true);
      else
        code[i].push_back(false);

  for (auto &x : code) reverse(x.begin(), x.end());

  BitWriter<> out(dst);
  writeDict(*heap.begin(), items, out);
  for (auto c : text)
    for (bool x : code[idx[c]]) out << x;
}

struct Node {
  unsigned char val;
  Node *l, *r;
  Node() : l(nullptr), r(nullptr) {}
  ~Node() {
    if (l) delete l;
    if (r) delete r;
  }
};

Node *readTree(BitReader<> &in) {
  bool v;
  in >> v;
  Node *res = new Node;
  if (v)
    in >> (res->val);
  else {
    res->l = readTree(in);
    res->r = readTree(in);
  }
  return res;
}

void decompress(const string &src, const string &dst) {
  BitReader<> in(src);
  ofstream dstf(dst, ios::out | ios::binary);
  Node *root = readTree(in);
  for (Node *p = root; in;) {
    bool v;
    in >> v;
    if (v)
      p = p->l;
    else
      p = p->r;
    if (p->l == nullptr) {
      dstf.write((char *)&(p->val), 1);
      p = root;
    }
  }
}

void help(char **argv) {
  cout << argv[0] << " [-d] vstup vystup" << endl;
  exit(-1);
}

int main(int argc, char **argv) {
  if (argc < 3) help(argv);
  if (string(argv[1]) == "-d") {
    if (argc < 4) help(argv);
    decompress(argv[2], argv[3]);
  } else {
    compress(argv[1], argv[2]);
  }
}
