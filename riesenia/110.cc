#ifndef __TABULKA_H__
#define __TABULKA_H__

template <typename T>
struct Tabulka {
  Tabulka() : m{0}, n{0}, data{nullptr} {}

  Tabulka(int _m, int _n) : m{_m}, n{_n}, data{nullptr} {
    realokuj(m, n);
    zmen([](int, int) { return T(); });
  }

  Tabulka(const Tabulka& x) : data{nullptr} {
    realokuj(x.m, x.n);
    zmen([&x](int i, int j) { return x(i, j); });
  }

  Tabulka& operator=(const Tabulka& x) {
    realokuj(x.m, x.n);
    zmen([&x](int i, int j) { return x(i, j); });
    return *this;
  }

  Tabulka& operator=(Tabulka&& x) {
    m = x.m;
    n = x.n;
    data = x.data;
    x.data = nullptr;
    return *this;
  }

  ~Tabulka() {
    if (data != nullptr) delete[] data;
  }

  T& operator()(int r, int s) {
    sentinel = T{};
    if (r >= 0 && r < m && s >= 0 && s < n)
      return data[r * n + s];
    else
      return sentinel;
  }

  T operator()(int r, int s) const {
    if (r >= 0 && r < m && s >= 0 && s < n)
      return data[r * n + s];
    else
      return T{};
  }

  Tabulka& operator+=(const Tabulka& t) {
    zmen([&t, this](int i, int j) { return (*this)(i, j) + t(i, j); });
    return *this;
  }

  Tabulka& operator-=(const Tabulka& t) {
    zmen([&t, this](int i, int j) { return (*this)(i, j) - t(i, j); });
    return *this;
  }

  Tabulka& operator*=(double v) {
    zmen([v, this](int i, int j) { return (*this)(i, j) * v; });
    return *this;
  }

  int m, n;
  T* data;
  T sentinel;

  template <typename F>
  void zmen(F f) {
    for (int i = 0; i < m; i++)
      for (int j = 0; j < n; j++) data[i * n + j] = f(i, j);
  }

 private:
  void realokuj(int _m, int _n) {
    m = _m;
    n = _n;
    if (data != nullptr) delete[] data;
    data = new T[m * n];
  }
};

template <typename T>
Tabulka<T> operator+(const Tabulka<T>& a, const Tabulka<T>& b) {
  Tabulka<T> res{a};
  res += b;
  return res;
}

template <typename T>
Tabulka<T> operator-(const Tabulka<T>& a, const Tabulka<T>& b) {
  Tabulka<T> res{a};
  res -= b;
  return res;
}

template <typename T>
Tabulka<T> operator*(const Tabulka<T>& a, double b) {
  Tabulka<T> res{a};
  res *= b;
  return res;
}

template <typename T>
Tabulka<T> operator*(double b, const Tabulka<T>& a) {
  Tabulka<T> res{a};
  res *= b;
  return res;
}

#endif
