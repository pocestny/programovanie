#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <algorithm>

using namespace std;

SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;

int main() {
  int ww = 800, wh = 600;

  SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_AUDIO);
  SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "2");

  window = SDL_CreateWindow("prvy pokus", SDL_WINDOWPOS_CENTERED,
                            SDL_WINDOWPOS_CENTERED, ww, wh,
                            SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN);
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
  IMG_Init(IMG_INIT_PNG);
  SDL_Texture* penguin = IMG_LoadTexture(renderer, "penguin.png");

  bool running = true;

  while (running) {
    SDL_Event e;

    SDL_WaitEvent(&e);
    switch (e.type) {
      case SDL_WINDOWEVENT:
        switch (e.window.event) {
          case SDL_WINDOWEVENT_SIZE_CHANGED:
            ww = e.window.data1;
            wh = e.window.data2;
            break;
        }
        break;

      case SDL_QUIT:
        running = false;
        break;

      case SDL_KEYDOWN:
        SDL_Keysym k = e.key.keysym;
        if (k.sym == SDLK_q && ((k.mod & (KMOD_LCTRL | KMOD_RCTRL)) != 0))
          running = false;
    }
    SDL_SetRenderDrawColor(renderer, 250, 180, 0, 255);
    SDL_RenderClear(renderer);
    SDL_Rect src{.x = 0, .y = 0, .w = 722, .h = 1002};
    double scale = 0.9 * min((double)ww / 722.0, (double)wh / 1002.0);
    int nw = scale * 722, nh = scale * 1002;
    SDL_Rect dst{.x = (ww - nw) / 2, .y = (wh - nh) / 2, .w = nw, .h = nh};
    SDL_RenderCopy(renderer, penguin, &src, &dst);
    SDL_RenderPresent(renderer);
  }

  SDL_DestroyWindow(window);
  IMG_Quit();
  SDL_Quit();
}
