#include <iterator>  // forward_iterator_tag

using namespace std;

struct Puch {

  struct iterator {
    using iterator_category = random_access_iterator_tag;
    using difference_type = int;
    using value_type = int;
    using pointer = int*;
    using reference = int&;

    int* x;
    Puch* par;

    int val() {
      if (x == &(par->a)) return 0;
      if (x == &(par->b)) return 1;
      if (x == &(par->c)) return 2;
      if (x == nullptr) return 3;
      return -1;
    }

    iterator(Puch* _par, int* _x) {
      par = _par;
      x = _x;
    }

    int* operator->() { return x; }

    int& operator*() { return *x; }

    iterator& operator++() {
      if (x == &(par->a))      x = &(par->b);
      else if (x == &(par->b)) x = &(par->c);
      else if (x == &(par->c)) x = nullptr;
      return *this;
    }

    iterator operator++(int) {
      iterator old = *this;
      operator++();
      return old;
    }

    iterator& operator--() {
      if (x == &(par->c))      x = &(par->b);
      else if (x == &(par->b)) x = &(par->a);
      else if (x == nullptr)   x = &(par->c);
      return *this;
    }

    iterator operator--(int) {
      iterator old = *this;
      operator--();
      return old;
    }
  };

  int a, b, c;

  Puch(int _a, int _b, int _c) {
    a = _a;
    b = _b;
    c = _c;
  }
  iterator begin() { return iterator(this, &a); }
  iterator end() { return iterator(this, nullptr); }
};

bool operator!=(Puch::iterator a, Puch::iterator b) {
  return a.val() != b.val();
}
bool operator==(Puch::iterator a, Puch::iterator b) {
  return a.val() == b.val();
}
bool operator>(Puch::iterator a, Puch::iterator b) { return a.val() > b.val(); }
bool operator<(Puch::iterator a, Puch::iterator b) { return a.val() < b.val(); }
int operator-(Puch::iterator a, Puch::iterator b) { return a.val() - b.val(); }

Puch::iterator operator+(Puch::iterator a, int x) {
  Puch::iterator res = a;
  while (x-- > 0) res++;
  return res;
}

Puch::iterator operator-(Puch::iterator a, int x) {
  Puch::iterator res = a;
  while (x-- > 0) res--;
  return res;
}

