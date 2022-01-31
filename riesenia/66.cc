#include <iostream>
#include <sstream>
#include <string>
using namespace std;

int main() {
  string s;
  stringstream in, out;
  double pi;

  out << "0.";
  while (cin.good()) {
    getline(cin, s);
    int i = 0, j;
    while ((i = s.find("#", i)) != string::npos) {
      j = s.find("#", i + 1);
      in.clear();
      in.str(s.substr(i + 1, j - i - 1));
      int n;
      for (in >> n; !in.fail(); in >> n) {
        out << n;
      }
      i = j + 1;
    }
  }
  out >> pi;
  pi = 10 * pi;
  cout << out.str() << endl;
  cout << pi << endl;
}
