#include <cmath>
#include <iostream>
using namespace std;

int w, h;             // rozmery obrazka
double px, py, smer;  // pozicia a smer
bool penup;           // ci je momentalne pero hore

struct Prikaz {
  char t;       // typ prikazu
  int r, g, b;  // pre prikaz 'c'
  double x;     // pre prikazy 'l' 'r' 'f'
  int i, cnt;   // pre prikaz 'r'
  int addr;     // pre prikaz 'e'
};

Prikaz prog[100000];
int n;  // pocet prikazov

void execute() {
  int pc = 0;
  while (pc < n) {
    if (prog[pc].t == 'u') {
      penup = true;
      pc++;
    } else if (prog[pc].t == 'd') {
      penup = false;
      pc++;
    } else if (prog[pc].t == 'f') {
      if (penup)
        cout << "m ";
      else
        cout << "l ";
      px += prog[pc].x * cos(smer);
      py += prog[pc].x * sin(smer);
      cout << px << " " << py << endl;
      pc++;
    } else if (prog[pc].t == 'c') {
      cout << "c " << prog[pc].r << " " << prog[pc].g << " " << prog[pc].b
           << endl;
      pc++;
    } else if (prog[pc].t == 'l') {
      smer += prog[pc++].x;
      while (smer > 2 * M_PI) smer -= 2 * M_PI;
    } else if (prog[pc].t == 'r') {
      smer -= prog[pc++].x;
      while (smer < 0) smer += 2 * M_PI;
    } else if (prog[pc].t == 'R') {
      prog[pc++].i++;
    } else if (prog[pc].t == 'E') {
      int jmp = prog[pc].addr;
      if (prog[jmp].i == prog[jmp].cnt) {
        prog[jmp].i = 0;
        pc++;
      } else {
        pc = jmp;
      }
    }
  }
}

int main() {
  char prikaz[100];
  n = 0;

  int stack[100000];
  int m = 0;

  while (1) {
    cin >> prikaz;
    if (prikaz[0] == 'i') {
      cin >> w >> h;
      cout << "i " << w << " " << h << endl;
      px = (double)w / 2.0;
      py = (double)h / 2.0;
      smer = M_PI / 2.0;
      penup = false;
      cout << "m " << px << " " << py << endl;
    } else if (prikaz[0] == 'u')
      prog[n++].t = 'u';
    else if (prikaz[0] == 'd')
      prog[n++].t = 'd';
    else if (prikaz[0] == 'f') {
      prog[n].t = 'f';
      cin >> prog[n++].x;
    } else if (prikaz[0] == 'c') {
      prog[n].t = 'c';
      cin >> prog[n].r >> prog[n].g >> prog[n].b;
      n++;
    } else if (prikaz[0] == 's') {
      execute();
      cin >> prikaz;
      cout << "s " << prikaz << endl;
      break;
    } else if (prikaz[0] == 'l') {
      prog[n].t = 'l';
      cin >> prog[n].x;
      prog[n].x *= 2 * M_PI / 360.0;
      n++;
    } else if (prikaz[0] == 'r') {
      prog[n].t = 'r';
      cin >> prog[n].x;
      prog[n].x *= 2 * M_PI / 360.0;
      n++;
    } else if (prikaz[0] == 'R') {
      prog[n].t = 'R';
      cin >> prog[n].cnt;
      prog[n].i = 0;
      stack[m++] = n++;
    } else if (prikaz[0] == 'E') {
      prog[n].t = 'E';
      m--;
      prog[n].addr = stack[m];
      prog[stack[m]].addr = n++;
    }
  }
}
