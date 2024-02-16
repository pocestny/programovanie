#include <iostream>

#include "data.h"
#include "network.h"
using namespace std;

int main() {
  Data mnist;
  mnist.loadDataset();
  mnist.setTrainSizes(0.8);
  Network net{mnist.dim * mnist.dim, 300, 100, 10};
  net.randomInit(-0.01, 0.01);

  double step = 0.1;
  int epoch = 0;
  while (++epoch < 500) {
    InOut data = mnist.sample(200);
    for (int c = 0; c < 1000; c++) {
      net.backPropagation(data.in, data.out);
      cout << epoch << "  " << c << " " << net.error(net.output(), data.out)
           << endl;
      auto g = net.gradient(data.in);
      net.apply(step, g);
    }
    net.save("network.data");
  }

  {
    auto sample = mnist.test();
    auto out = net.feed(sample.in);
    int good = 0, bad = 0;
    for (int i = 0; i < sample.in.cols(); i++) {
      int truth, net;
      double netm = -1e50;
      for (int j = 0; j < sample.out.rows(); j++) {
        if (sample.out(j, i) > 0) truth = j;
        if (out(j, i) > netm) {
          netm = out(j, i);
          net = j;
        }
      }
      if (truth == net)
        good++;
      else
        bad++;
    }
    cout << "TEST SET: all = " << (good + bad) << "   good = " << good
         << "   bad = " << bad << endl;
  }
}
