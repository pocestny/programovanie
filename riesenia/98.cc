#include <iostream>
#include <map>
#include <string>

using namespace std;

int main() {
  map<string, int> s;
  while (true) {
    string typ, in;
    cin >> typ;
    if (typ[0] == '!') break;
    cin >> in;
    if (typ[0] == '?') cout << s[in] << endl;
    else if (typ[0] == '*') {
      int v = stoi(in.substr(in.find("-") + 1));
      in=in.substr(0,in.find("-"));
      if (v<=s[in])
      cout << "ano" << endl;
      else
      cout << "nie" << endl;
    } else 
      s[in]++;
    
  }
}
