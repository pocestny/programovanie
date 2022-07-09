struct Eroder {
  Tabulka<double> H;
  int n;

  const double zotrvacnost = 0.2;
  const double rozpustnost = 13;  // kapacita: kolko vie moda odniest
  const double usadzanie = 0.2;   // rychlost usadzania
  const double erozia = 0.5;
  const double gravitacia = 5;
  const double odparovanie = 0.0013;
  const double min_sklon = 0.1;
  const int lifetime = 150;    // kolko krokov simulujem jednu kvapku
  const int numkvap = 350000;  // pocet kvapiek

  static const int r = 1;             // polomer erozie
  double vahy[2 * r + 1][2 * r + 1];  // vahy erozie

  // konstruktor: vyrobim si "stetec" s vahami pre eroziu
  Eroder(const Tabulka<double>& _H) : H(_H), n(H.n) {
    double sum = 0;
    for (int dx = 0; dx < 2 * r + 1; dx++)
      for (int dy = 0; dy < 2 * r + 1; dy++) {
        double dist = sqrt((r - dx) * (r - dx) + (r - dy) * (r - dy)) / (r + 1);
        double w = 0;
        if (dist < 1) w = (1 - dist);
        vahy[dx][dy] = w;
        sum += w;
      }
    for (int dx = 0; dx < 2 * r + 1; dx++)
      for (int dy = 0; dy < 2 * r + 1; dy++) vahy[dx][dy] /= sum;
  }

  // simulacia jednej kvapky
  void kvap() {
    Vec pos{rnd() * n, rnd() * n};  // nahodna pozicia kvapky
    Vec dir{0, 0};                  // pociatocny smer

    double rychlost = 1;  // rychlost
    double voda = 1;      // objem vody
    double bahno = 0;     // objem usadeniny

    for (int t = 0; t < lifetime; t++) {  // hlavny cyklus
                                          //
      int ix = pos.x, iy = pos.y;
      Vec p{pos.x - ix, pos.y - iy};  // pozicia v ramci gridu

      Vec3 e[4];  // normaly v krajnych bodoch
      for (int dx = 0; dx < 2; dx++)
        for (int dy = 0; dy < 2; dy++)
          e[dx + 2 * dy] = normala(H, ix + dx, iy + dy);

      // normala je biliearna interpolacia
      Vec3 norm = bilinear(e[0], e[1], e[2], e[3], p);

      Vec g{norm.x, norm.y};  // priemet normaly je gardient
      g = g.normalize();

      dir = lerp(g, dir, zotrvacnost);
      if (dir.length() < 1e-25) break;  // kvapka sa zastavila
      dir.normalize();

      double h = vyska(pos);      // povodna vyska
      pos += dir;                 // pohni kvapku
      double h_new = vyska(pos);  // nova vyska

      // ak sme vysli za okraj, zastan
      if (pos.x < 1 || pos.x >= n - 2 || pos.y < 1 || pos.y >= n - 2) break;

      double delta = h_new - h;

      // kolko bahna sa da usadit zavisi od sklonu, rychlosti a mnozstva vody
      double dasausadit =
          max(-delta, min_sklon) * rychlost * voda * rozpustnost;

      if (bahno > dasausadit || delta > 0) {
        // ak tecie do kopca, snazi sa vyplnit rozdiel bahnom, ak ho ma dost
        // inak usadi cast bahna

        double usadit;
        if (delta > 0)
          usadit = min(delta, bahno);
        else
          usadit = (bahno - dasausadit) * usadzanie;
        bahno -= usadit;

        // rozdistribuj bahno bilinearne do susednych vrcholov
        for (int dx = 0; dx < 2; dx++)
          for (int dy = 0; dy < 2; dy++) {
            H(ix + dx, iy + dy) += usadit * (dx * p.x + (1 - dx) * (1 - p.x)) *
                                   (dy * p.y + (1 - dy) * (1 - p.y));
          }
      } else {
        // ak ma v sebe malo bahna, odoberie cast z okolia
        double urvat = min((dasausadit - bahno) * erozia, -delta);

        // odoberie zo sirsieho okolia podla toho, ako su nastavene vahy
        for (int dx = 0; dx < 2 * r + 1; dx++)
          for (int dy = 0; dy < 2 * r + 1; dy++) {
            int i = ix - r + dx, j = iy - r + dy;
            double kusok = urvat * vahy[dx][dy];
            H(i, j) -= kusok;
            bahno += kusok;
          }
      }

      // upravime rychlost
      if (delta < 0) delta *= -1;
      rychlost = sqrt(rychlost * rychlost + delta * gravitacia);

      // nieco sa odpari
      voda *= (1 - odparovanie);
    }
  }

  // najdi interpolovanu vysku
  double vyska(Vec pos) {
    int ix = pos.x, iy = pos.y;
    Vec p{pos.x - ix, pos.y - iy};
    double w[4];
    for (int dx = 0; dx < 2; dx++)
      for (int dy = 0; dy < 2; dy++) w[dx + 2 * dy] = H(ix + dx, iy + dy);
    return bilinear(w[0], w[1], w[2], w[3], p);
  }
};
