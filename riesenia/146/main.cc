#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

#include <fstream>
#include <iostream>
#include <sstream>

#include "data.h"
#include "network.h"
#include "widgets.h"

using namespace std;

SDL_Window *window = nullptr;
SDL_Renderer *renderer = nullptr;

const int dim = 26;

const Gradient Bulb::g("gradient.gpf");
int ww = 800, wh = 700;  // okno
uint32_t lastFrame = 0, FPS = 80;
uint32_t msPerFrame = 1000 / FPS;
uint32_t lastRun = 0;
bool running = true;

Canvas *canvas = nullptr;
Bulb *bulbs[10];
Network net{676, 300, 100, 10};

void run_net() {
  auto &inp = canvas->img;
  InOut res(dim * dim, 10, 1);
  Data::Bytes tmp(inp.d);
  int d = inp.d;
  inp.sentinel = 0xff;
  for (int i = 0; i < d; i++)
    for (int j = 0; j < d; j++) {
      int v = 0;
      for (int di : {-1, 0, 1})
        for (int dj : {-1, 0, 1}) v += inp(i + di, j + dj);
      tmp(i, j) = u8(v / 9);
    }

  Data::Bytes img(dim);
  Data::processImage(tmp, img);

  for (int i = 0; i < dim * dim; i++)
    res.in(i, 0) = 1.0 - 2.0 * (double)img.a[i] / 255.0;
  auto &out = net.feed(res.in);

  for (int i = 0; i < 10; i++) bulbs[i]->set(tanh(out(i, 0)));
}

int main(int argc, char **argv) {
  SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_AUDIO);
  SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "2");

  window = SDL_CreateWindow("MNIST digits dataset", SDL_WINDOWPOS_CENTERED,
                            SDL_WINDOWPOS_CENTERED, ww, wh,
                            /*SDL_WINDOW_RESIZABLE |*/ SDL_WINDOW_SHOWN);
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
  IMG_Init(IMG_INIT_PNG);
  TTF_Init();

  net.load("network.data");

  VLayout mainWindow;
  canvas = new Canvas();
  auto topBar = new HLayout();
  topBar->fixedHeight = 52;
  auto mainArea = new HLayout();
  auto buttonArea = new VLayout();
  buttonArea->fixedWidth = 150;
  Button *quitButton = new Button("koniec");
  Button *clearButton = new Button("znovu");

  for (int i = 0; i < 10; i++) {
    bulbs[i] = new Bulb(to_string(i));
    (*topBar) << bulbs[i];
  }

  quitButton->onClick = []() { running = false; };
  clearButton->onClick = [&]() {
    canvas->clear();
    run_net();
  };

  mainWindow << topBar << mainArea;
  (*mainArea) << canvas << buttonArea;
  (*buttonArea) << new Widget() << clearButton << quitButton;

  mainWindow.resize(SDL_Rect{0, 0, ww, wh});

  while (running) {
    SDL_Event e;

    while (SDL_PollEvent(&e)) {
      switch (e.type) {
        case SDL_WINDOWEVENT:
          switch (e.window.event) {
            case SDL_WINDOWEVENT_SIZE_CHANGED:
              ww = e.window.data1;
              wh = e.window.data2;
              mainWindow.resize(SDL_Rect{0, 0, ww, wh});
              break;
          }
          break;
        case SDL_QUIT:
          running = false;
          break;
        case SDL_MOUSEMOTION:
          Widget::mouse = SDL_Point{e.motion.x, e.motion.y};
          mainWindow.onMouseMotion(e.motion);
          break;
        case SDL_MOUSEBUTTONDOWN:
          mainWindow.onMouseDown(e.button);
          break;
        case SDL_MOUSEBUTTONUP:
          mainWindow.onMouseUp(e.button);
          run_net();
          break;
        case SDL_KEYDOWN:
          SDL_Keysym k = e.key.keysym;
          if (k.sym == SDLK_q && ((k.mod & (KMOD_LCTRL | KMOD_RCTRL)) != 0))
            running = false;
          else if (k.sym == SDLK_SPACE) {
            canvas->clear();
            run_net();
          }
      }
    }

    SDL_SetRenderDrawColor(renderer, 0x54, 0x6e, 0x7a, 255);
    SDL_RenderClear(renderer);
    mainWindow.render(renderer);
    SDL_RenderPresent(renderer);

    uint32_t now = SDL_GetTicks();

    lastFrame = now;
    if (!canvas->painting) lastRun = now - 299;
    if (lastRun + 300 < now) {
      run_net();
      lastRun = now;
    }
  }

  SDL_DestroyWindow(window);
  IMG_Quit();
  TTF_Quit();
  SDL_Quit();
}

