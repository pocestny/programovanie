template <typename Buffer=unsigned int>
struct BitReader {
  ifstream f;
  Buffer buff;
  int sz;
  long int len;
  const int N = sizeof(Buffer);

  BitReader(const string &fname) {
    f.open(fname, ios::in | ios::binary);
    sz = 0;
    buff = (Buffer)0;
    f.read((char *)&len, sizeof(len));
  }

  ~BitReader() { f.close(); }

  BitReader &operator>>(bool &v) {
    sz--;
    len--;
    if (sz < 0) {
      f.read((char *)&buff, N);
      sz = 8 * N - 1;
    }
    v = (buff & (1 << sz)) != 0;
    return *this;
  }

  template <typename T>
  BitReader &operator>>(T &v) {
    v = 0;
    bool b;
    for (int i = 8 * sizeof(T) - 1; i >= 0; i--) {
      (*this)>>b;
      v |= (int)b << i;
    }
    return *this;
  }

  operator bool() { return len > 0; }
};
