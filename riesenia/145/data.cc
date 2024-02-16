#include <algorithm>
#include <fstream>
#include <sstream>
#include "avir.h"
#include "data.h"

using namespace std;

avir::CImageResizer<> imageResizer(8);

Data::Point &Data::Point::operator=(const Data::Point &a) {
  for (int i : {0, 1}) _p[i] = a[i];
  return *this;
}

Data::Point &Data::Point::operator+=(const Data::Point &p) {
  for (int i : {0, 1}) _p[i] += p[i];
  return *this;
}

Data::Point &Data::Point::operator*=(double a) {
  for (int i : {0, 1}) _p[i] *= a;
  return *this;
}

Data::Point operator+(const Data::Point &a,
                           const Data::Point &b) {
  Data::Point p = a;
  p += b;
  return p;
}

Data::Point operator*(double a, const Data::Point &q) {
  Data::Point p = q;
  p *= a;
  return p;
}

ostream &operator<<(ostream &str, const Data::Point &p) {
  str << "[" << p.x() << ", " << p.y() << "]";
  return str;
}

Data::Box &Data::Box::expand(const Data::Point &q) {
  p[0] = Point{min(p[0][0], q[0]), min(p[0][1], q[1])};
  p[1] = Point{max(p[1][0], q[0]), max(p[1][1], q[1])};
  return *this;
}

u8 &Data::Bytes::operator()(int x, int y) {
  if (x < 0 || y < 0 || x >= d || y >= d) return sentinel;
  return a[x + y * d];
}

u8 Data::Bytes::operator()(int x, int y) const {
  if (x < 0 || y < 0 || x >= d || y >= d) return 0;
  return a[x + y * d];
}

Data::Point Data::Bytes::cog() const {
  Point p{0, 0};
  int s = 0;
  for (int i = 0; i < d * d; i++) {
    u8 v = 255 - a[i];
    Point q = v * pos(i);
    s += v;
    p += q;
  }
  for (int i : {0, 1}) p[i] = (int)((double)(p[i]) / (double)s);
  return p;
}

Data::Box Data::Bytes::bbox() const {
  Box b{Point{n, n}, Point{0, 0}};
  for (int i = 0; i < n; i++)
    if (a[i] == 0) b.expand(pos(i));
  return b;
}

Data::Point Data::Box::center() const { return 0.5 * (p[0] + p[1]); }

void Data::processImage(Data::Bytes &in,
                             Data::Bytes &out) {
  Box bb = in.bbox();
  int d = 1 + max(bb.x(), bb.y());
  Point o{bb[0].x() - (d - bb.x()) / 2, bb[0].y() - (d - bb.y()) / 2};
  Bytes crop(d);
  int t = 0;
  for (int i = 0; i < d; i++)
    for (int j = 0; j < d; j++) {
      in.sentinel = 0xff;
      crop.a[t++] = in(o.x() + j, o.y() + i);
    }
  Bytes rsz(sc);
  imageResizer.resizeImage(crop.a.data(), d, d, 0, rsz.a.data(), sc, sc, 1, 0);
  Point c = rsz.cog();
  o = Point{dim / 2 - c.x(), dim / 2 - c.y() - 1};

  for (int i = 0; i < sc; i++)
    for (int j = 0; j < sc; j++)
        out(o.x() + j, o.y() + i) = rsz(j, i);
}

void Data::loadDataset() {
  dataset.resize(10);
  for (int num = 0; num < 10; num++) {
    dataset[num].clear();
    stringstream ss;
    ss<<binDir<<"/"<<num<<".bin";
    ifstream f(ss.str(), ios::binary);
    u32 x;
    f.read((char *)&x, sizeof(u32));
    while (x-- > 0) dataset[num].emplace_back(dim);
    for (auto &d : dataset[num]) f.read((char *)(d.a.data()),  dim * dim);
  }
}

vector<int> Data::size() const {
  vector<int> res(10);
  for (int i = 0; i < 10; i++) res[i] = dataset[i].size();
  return res;
}

void Data::setTrainSizes(double ratio) {
  trainSizes.resize(10);
  for (int i = 0; i < 10; i++)
    trainSizes[i] = ratio * (double)dataset[i].size();
}

void Data::shuffle() {
  for (int i = 0; i < 10; i++)
    ::shuffle(dataset[i].begin(), dataset[i].end(), rnd);
}

void Data::addCol(InOut &res, int c, int num, int n) {
  for (int i = 0; i < dim * dim; i++)
    res.in(i, c) = 1.0 - 2.0 * (double)dataset[num][n].a[i] / 255.0;
  for (int i = 0; i < 10; i++) res.out(i, c) = (i == num) ? 1.0 : -1.0;
}

InOut Data::test() {
  int n = 0;
  for (int i = 0; i < 10; i++) n += dataset[i].size() - trainSizes[i];
  InOut res(dim * dim, 10, n);
  int c = 0;
  for (int i = 0; i < 10; i++)
    for (int j = trainSizes[i]; j < dataset[i].size(); j++)
      addCol(res, c++, i, j);
  return res;
}

InOut Data::sample(int s) {
  if (s == -1) s = 100;

  InOut res(dim * dim, 10, s);
  for (int i = 0; i < s; i++) {
    int num = rnd() % 10;
    int n = rnd() % trainSizes[num];
    addCol(res, i, num, n);
  }
  return res;
}

