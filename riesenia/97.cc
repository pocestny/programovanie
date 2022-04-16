#include <iostream>
#include <string>
#include <map>
#include <set>

using namespace std;

int main() {
  map<string,set<string>> m;
  while(true) {
    string podmet;
    cin>>podmet;
    if (podmet[0]=='!') break;
    string in;
    cin>>in;
    if (in=="nie") {
      cin>>in>>in;
    } else {
      cin>>in;
      m[podmet].insert(in.substr(0,in.find('.')));
    }
  }
  for(auto &x:m) {
    cout<<x.first<<" je ";
    int i=0;
    for(auto &s:x.second) {
      if (i>0) {
        if (i<x.second.size()-1) cout<<", ";
        else cout<<" a ";
      }
      cout<<s;
      i++;
    }
    cout<<"."<<endl;
  }
}
