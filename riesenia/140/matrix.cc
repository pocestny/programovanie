#include "matrix.h"

#include <algorithm>
#include <cassert>
#include <cstring>
#include <iomanip>

using namespace std;

Matrix::Matrix(int _n, int _m, Num init) : n{_n}, m{_m}, size{n * m} {
  _data = (Num*)malloc(size * sizeof(Num));
  std::fill(_data, _data + size, init);
}

Matrix::Matrix(int _n, int _m, const vector<Num>& v)
    : n{_n}, m{_m}, size{n * m} {
  assert(v.size() >= size);
  _data = (Num*)malloc(size * sizeof(Num));
  copy(v.begin(), v.begin() + size, _data);
}

Matrix::Matrix(int _n, int _m, initializer_list<Num> v)
    : n{_n}, m{_m}, size{n * m} {
  assert(v.size() >= size);
  _data = (Num*)malloc(size * sizeof(Num));
  copy(v.begin(), v.begin() + size, _data);
}

Matrix::Matrix(const Matrix& a) : n{a.n}, m{a.m}, size{n * m} {
  _data = (Num*)malloc(size * sizeof(Num));
  memcpy(_data, a._data, size * sizeof(Num));
}

Matrix::Matrix(Matrix&& a) : n{a.n}, m{a.m}, size{n * m} {
  _data = a._data;
  a._data = nullptr;
}

Matrix::~Matrix() {
  if (_data) free(_data);
}

Matrix& Matrix::operator=(const Matrix& a) {
  if (n != a.n || m != a.m) {
    if (_data) free(_data);
    n = a.n;
    m = a.m;
    size = n * m;
    _data = (Num*)malloc(size * sizeof(Num));
  }
  memcpy(_data, a._data, size * sizeof(Num));
  return *this;
}

Matrix& Matrix::operator=(Matrix&& a) {
  if (this == &a) return (*this);
  n = a.n;
  m = a.m;
  if (_data) free(_data);
  _data = a._data;
  a._data = nullptr;
  return *this;
}

Matrix& Matrix::operator+=(const Matrix& b) {
  assert(b.n == n && b.m == m);
  for (int i = 0; i < size; i++) _data[i] += b._data[i];
  return *this;
}

Matrix& Matrix::operator-=(const Matrix& b) {
  assert(b.n == n && b.m == m);
  for (int i = 0; i < size; i++) _data[i] -= b._data[i];
  return *this;
}

Matrix& Matrix::addMultiple(Num delta, const Matrix& b) {
  assert(b.n == n && b.m == m);
  for (int i = 0; i < size; i++) _data[i] += delta * b._data[i];
  return *this;
}

Matrix& Matrix::addRow(const Matrix& b) {
  assert(b.n == 1 && b.m == m);
  int pos = 0;
  for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++) _data[pos++] += b._data[j];
  return *this;
}

Matrix& Matrix::addColumn(const Matrix& b) {
  assert(b.n == n && b.m == 1);
  int pos = 0;
  for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++) _data[pos++] += b._data[i];
  return *this;
}

Matrix Matrix::transposed() const {
  Matrix res(m, n);
  for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++) res(j, i) = (*this)(i, j);
  return res;
}

void multInto(const Matrix& a, const Matrix& b, Matrix& res) {
  assert(res.n == a.n && res.m == b.m && a.m == b.n);
  for (int i = 0; i < res.n; i++)
    for (int j = 0; j < res.m; j++) {
      res(i, j) = 0;
      for (int k = 0; k < a.m; k++) res(i, j) += a(i, k) * b(k, j);
    }
}

Matrix operator*(const Matrix& a, const Matrix& b) {
  Matrix res(a.n, b.m);
  multInto(a, b, res);
  return res;
}

Matrix operator+(const Matrix& a, const Matrix& b) {
  assert(a.n == b.n && a.m == b.m);
  Matrix res(a.n, a.m);
  for (int i = 0; i < a.size; i++) res._data[i] = a._data[i] + b._data[i];
  return res;
}

ostream& operator<<(ostream& str, const Matrix& m) {
  for (int i = 0; i < m.n; i++) {
    for (int j = 0; j < m.m; j++) str << setw(20) << m(i, j);
    str << endl;
  }
  return str;
}
