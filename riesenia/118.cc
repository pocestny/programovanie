struct Perlin {
  int n, d, m;  // rozmer obrazka, stride gridu, rozmer gridu
  Tabulka<double> H;
  Tabulka<Vec> G;

  Perlin(int _n, int _d) : n{_n}, d{_d}, m{1 + n / d}, H(n, n), G(m, m) {
    for (int i = 0; i < m; i++)
      for (int j = 0; j < m; j++) {
        double theta = rnd() * M_PI * 2.0;
        G(i, j) = {cos(theta), sin(theta)};
      }

    for (int i = 0; i < n; i++)
      for (int j = 0; j < n; j++) {
        // transformuj z H-gridu do G-gridu
        Vec p{(double)i / (double)d, (double)(j) / (double)d};
        int o[2] = {(int)p.x, (int)p.y};

        double dot[4];
        for (int dx = 0; dx < 2; dx++)
          for (int dy = 0; dy < 2; dy++)
            dot[dx + 2 * dy] = (p - Vec{(double)o[0] + dx, (double)o[1] + dy}) *
                               G(o[0] + dx, o[1] + dy);

        double r = fade(p.x - o[0]), s = fade(p.y - o[1]);
        double vc = lerp(v[0], v[1], r), vd = lerp(v[2], v[3], r);
        H(i, j) = lerp(vc, vd, s);
      }
  }

 private:
  double fade(double t) {
    return t;
    return t * t * t * (10 + t * (6 * t - 15));
  }
};
