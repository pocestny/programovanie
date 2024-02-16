#ifndef __MATRIX_H__
#define __MATRIX_H__

#include <initializer_list>
#include <ostream>
#include <string>
#include <vector>

using Num = double;

struct Matrix {
  int n;
  int m;
  int size;

  Matrix(int _n = 1, int _m = 1, Num init = (Num)(0));
  Matrix(int _n, int _m, const std::vector<Num>&);
  Matrix(int _n, int _m, std::initializer_list<Num> v);

  Matrix(const Matrix&);
  Matrix(Matrix&&);

  Matrix& operator=(const Matrix&);
  Matrix& operator=(Matrix&&);

  constexpr Num& operator()(int i, int j) { return _data[i * m + j]; }
  constexpr const Num& operator()(int i, int j) const {
    return _data[i * m + j];
  }
  ~Matrix();

  template <typename F>
  Matrix& fill(F f) {
    for (int i = 0; i < n; i++)
      for (int j = 0; j < m; j++) (*this)(i, j) = f(i, j);
    return *this;
  }

  template <typename F>
  Matrix& apply(F f) {
    for (int i = 0; i < size; i++) _data[i] = f(_data[i]);
    return *this;
  }

  Matrix& operator+=(const Matrix& b);
  Matrix& operator-=(const Matrix& b);
  Matrix& addMultiple(Num delta, const Matrix& b);
  Matrix& addRow(const Matrix& b);     
  Matrix& addColumn(const Matrix& b);  
  Matrix transposed() const;

  Num* _data;
};

void multInto(const Matrix& a, const Matrix& b, Matrix& res);
Matrix operator*(const Matrix& a, const Matrix& b);
Matrix operator+(const Matrix& a, const Matrix& b);
std::ostream& operator<<(std::ostream& str, const Matrix& m);

#endif
