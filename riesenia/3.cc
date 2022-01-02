#include <iostream>
using namespace std;
int main() {
  int mesiac;
  cin >> mesiac;
  if (mesiac >= 3 && mesiac <= 5)
    cout << 1 << endl;
  else if (mesiac >= 6 && mesiac <= 8)
    cout << 2 << endl;
  else if (mesiac >= 9 && mesiac <= 11)
    cout << 3 << endl;
  else
    cout << 4 << endl;
}
