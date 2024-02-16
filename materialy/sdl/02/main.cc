#include <SDL2/SDL.h>
#include <iostream>

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

  bool running = true;
  SDL_Rect r{.x = 100, .y = 100, .w = 100, .h = 100};

  while (running) {
    SDL_Event e;
    SDL_WaitEvent(&e);

    if (e.type == SDL_WINDOWEVENT &&
        e.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
      ww = e.window.data1;
      wh = e.window.data2;
      cout << "velkost okna: " << ww << " x " << wh << endl;
    } else if (e.type == SDL_QUIT)
      running = false;
    else if (e.type == SDL_KEYDOWN) {
      SDL_Keysym k = e.key.keysym;
      cout << "stlacene: " << SDL_GetKeyName(k.sym) << ", mod " << hex << k.mod
           << dec << endl;
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
