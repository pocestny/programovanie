#include <SDL2/SDL.h>
using namespace std;

SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;

int main() {
  int ww = 800, wh = 600;

  SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_AUDIO);

  window = SDL_CreateWindow("prvy pokus", SDL_WINDOWPOS_CENTERED,
                            SDL_WINDOWPOS_CENTERED, ww, wh,
                            SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN);
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

  bool running = true, dragging = false;
  SDL_Rect r{.x = 100, .y = 100, .w = 100, .h = 100};

  while (running) {
    SDL_Event e;

    SDL_WaitEvent(&e);
    if (e.type == SDL_WINDOWEVENT &&
        e.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
      ww = e.window.data1;
      wh = e.window.data2;
      r.x = min(r.x, max(0, ww - 100));
      r.y = min(r.y, max(0, wh - 100));
    } else if (e.type == SDL_QUIT)
      running = false;
    else if (e.type == SDL_MOUSEBUTTONDOWN) {
      if (abs(e.button.x - r.x - 50) < 50 && abs(e.button.y - r.y - 50) < 50)
        dragging = true;
    } else if (e.type == SDL_MOUSEBUTTONUP)
      dragging = false;
    else if (e.type == SDL_MOUSEMOTION) {
      if (dragging) {
        r.x = min(max(e.motion.x - 50, 0), ww - 100);
        r.y = min(max(e.motion.y - 50, 0), wh - 100);
      }
    } else if (e.type == SDL_KEYDOWN) {
      SDL_Keysym k = e.key.keysym;
      if (k.sym == SDLK_q && ((k.mod & (KMOD_LCTRL | KMOD_RCTRL)) != 0))
        running = false;
    }

    SDL_SetRenderDrawColor(renderer, 250, 180, 0, 255);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 20, 30, 180, 255);
    SDL_RenderFillRect(renderer, &r);
    SDL_RenderPresent(renderer);
  }

  SDL_DestroyWindow(window);
  SDL_Quit();
}
