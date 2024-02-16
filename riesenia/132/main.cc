#include <SDL2/SDL.h>

#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

#include "gradient.h"

using namespace std;

SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;

uint32_t lastFrame = 0, FPS = 80;
uint32_t msPerFrame = 1000 / FPS;

struct Stvorec {
  int cx = 100, cy = 100, w = 100, h = 100;
  Gradient gradient;
  Stvorec(const Gradient& _g) : gradient{_g} {}
  void render(SDL_Renderer* renderer);
  bool contains(int x, int y) {
    return (abs(x - cx) < w / 2 && abs(y - cy) < h / 2);
  }
};

void Stvorec::render(SDL_Renderer* renderer) {
  uint32_t now = SDL_GetTicks();
  Vec3 clr = gradient((double)(now % 10000) / 10000.0L);
  SDL_SetRenderDrawColor(renderer, 255 * clr.x, 255 * clr.y, 255 * clr.z, 255);

  SDL_Rect r;
  double a = 0.8 * (1.0 + sin(2.0 * M_PI * (double)(now % 340) / 340.0L));
  r.x = cx - w / 2 + a;
  r.y = cy - h / 2 + a;
  r.w = w - 2 * a;
  r.h = h - 2 * a;

  SDL_RenderFillRect(renderer, &r);
}

int main() {
  int ww = 800, wh = 600;

  SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_AUDIO);

  window = SDL_CreateWindow("prvy pokus", SDL_WINDOWPOS_CENTERED,
                            SDL_WINDOWPOS_CENTERED, ww, wh,
                            SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN);
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

  bool running = true, dragging = false;
  Stvorec r(Gradient("blue.gpf"));
  r.gradient.symmetrize(); 

  while (running) {
    SDL_Event e;

    while (SDL_PollEvent(&e)) {
      switch (e.type) {
        case SDL_WINDOWEVENT:
          switch (e.window.event) {
            case SDL_WINDOWEVENT_SIZE_CHANGED:
              ww = e.window.data1;
              wh = e.window.data2;
              r.cx = min(r.cx, max(r.w / 2, ww - r.w / 2));
              r.cy = min(r.cy, max(r.h / 2, wh - r.w / 2));
              break;
          }
          break;

        case SDL_QUIT:
          running = false;
          break;

        case SDL_MOUSEBUTTONDOWN:
          if (r.contains(e.button.x, e.button.y)) dragging = true;
          break;

        case SDL_MOUSEBUTTONUP:
          dragging = false;
          break;

        case SDL_MOUSEMOTION:
          if (dragging) {
            r.cx = min(max(e.motion.x, r.w / 2), ww - r.w / 2);
            r.cy = min(max(e.motion.y, r.h / 2), wh - r.h / 2);
          }
          break;

        case SDL_KEYDOWN:
          SDL_Keysym k = e.key.keysym;
          if (k.sym == SDLK_q && ((k.mod & (KMOD_LCTRL | KMOD_RCTRL)) != 0))
            running = false;
      }
    }
    SDL_SetRenderDrawColor(renderer, 250, 180, 0, 255);
    SDL_RenderClear(renderer);
    r.render(renderer);
    SDL_RenderPresent(renderer);

    uint32_t now = SDL_GetTicks();
    if (now < lastFrame + msPerFrame) SDL_Delay(lastFrame + msPerFrame - now);
    lastFrame = now;

  }

  SDL_DestroyWindow(window);
  SDL_Quit();
}
