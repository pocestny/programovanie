#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <algorithm>
#include <cmath>
#include <random>
#include <vector>

using namespace std;

SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;
SDL_Texture* penguin = nullptr;
int ww = 800, wh = 600;  // okno

// velkost vlocky
int vs() { return min(25, max(10, (ww * 20) / 800)); }

// pocet vlociek
int tr() { return (ww * wh) / (9 * vs() * vs()); }

mt19937 rnd{random_device{}()};

uint32_t lastFrame = 0, FPS = 80;
uint32_t msPerFrame = 1000 / FPS;

struct Vlocka {
  uint32_t start, end;
  double x, y;

  Vlocka() {
    uniform_real_distribution<> dis(0.0, 1.0);
    start = SDL_GetTicks();
    end = start + 10000 + rnd() % 10000;
    x = dis(rnd);
  }

  void render(SDL_Renderer* r) {
    SDL_Rect src{.x = 722, .y = 0, .w = 40, .h = 40}, dst{.w = vs(), .h = vs()};
    double t = (double)(SDL_GetTicks() - start) / (double)(end - start);
    dst.y = wh * t;
    dst.x = x * ww;
    y = dst.y;
    SDL_RenderCopy(renderer, penguin, &src, &dst);
  }
};

vector<Vlocka> sneh;

int main() {
  SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_AUDIO);
  SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "2");

  window = SDL_CreateWindow("prvy pokus", SDL_WINDOWPOS_CENTERED,
                            SDL_WINDOWPOS_CENTERED, ww, wh,
                            SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN);
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
  IMG_Init(IMG_INIT_PNG);
  penguin = IMG_LoadTexture(renderer, "penguin.png");

  bool running = true;

  while (running) {
    if (sneh.size() < tr() && (sneh.size() < 10 || rnd() % ww < 150))
      sneh.resize(sneh.size() + 1);

    SDL_Event e;
    while (SDL_PollEvent(&e)) {
      switch (e.type) {
        case SDL_WINDOWEVENT:
          switch (e.window.event) {
            case SDL_WINDOWEVENT_SIZE_CHANGED:
              ww = e.window.data1;
              wh = e.window.data2;
              if (sneh.size() > tr()) sneh.resize(tr());
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
    }
    SDL_SetRenderDrawColor(renderer, 250, 180, 0, 255);
    SDL_RenderClear(renderer);

    {  // pozadie
      SDL_SetRenderDrawColor(renderer, 10, 80, 160, 255);
      int h = 0.7 * wh;
      SDL_Rect r{.x = 0, .y = 0, .w = ww, .h = h};
      SDL_RenderFillRect(renderer, &r);
    }

    // vlocky
    for (auto& v : sneh) v.render(renderer);

    // vyhodit tie co dopadli
    for (int i = 0; i < sneh.size(); i++)
      if (sneh[i].y > 0.7 * wh) {
        swap(sneh[i], sneh.back());
        sneh.pop_back();
      }

    {  // tucniak
      SDL_Rect src{.x = 0, .y = 0, .w = 722, .h = 1002};
      double scale = 0.8 * min((double)ww / 722.0, (double)wh / 1002.0);
      int nw = scale * 722, nh = scale * 1002;
      SDL_Rect dst{
          .x = (ww - nw) / 2, .y = (int)(0.9 * wh) - nh, .w = nw, .h = nh};
      SDL_RenderCopy(renderer, penguin, &src, &dst);
    }

    SDL_RenderPresent(renderer);

    uint32_t now = SDL_GetTicks();
    if (now < lastFrame + msPerFrame) SDL_Delay(lastFrame + msPerFrame - now);
    lastFrame = now;
  }

  SDL_DestroyWindow(window);
  IMG_Quit();
  SDL_Quit();
}
