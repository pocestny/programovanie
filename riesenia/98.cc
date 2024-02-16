#include <iostream>
#include <string>
#include "aatree.h"

using namespace std;

int main() {
  Tree t;
  while (true) {
    string s;
    int x;
    cin >> s;
    if (s[0] == '#') break;
    cin >> x;
    bool jetam = t.find(x);
    if (s[0] == '?') {
      if (!jetam) cout << "ne";
      cout << "svieti" << endl;
    } else {
      if (jetam) t.erase(x);
      else t.insert(x);
    }
  }

}

