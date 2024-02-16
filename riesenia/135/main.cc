#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <iostream>
#include <string>

using namespace std;

SDL_Window *window = nullptr;
SDL_Renderer *renderer = nullptr;

uint32_t lastFrame = 0, FPS = 50;
uint32_t msPerFrame = 1000 / FPS;

struct Text {
  SDL_Surface *surf;
  SDL_Texture *txt;
  SDL_Rect box;

  Text(SDL_Renderer *renderer, TTF_Font *font, const char *text,
       SDL_Color color) {
    surf = TTF_RenderUTF8_Blended(font, text, color);
    box.h = surf->h;
    box.w = surf->w;
    txt = SDL_CreateTextureFromSurface(renderer, surf);
  }

  void render(SDL_Renderer *renderer, int x, int y) {
    box.x = x;
    box.y = y;
    SDL_RenderCopy(renderer, txt, nullptr, &box);
  }

  ~Text() {
    SDL_DestroyTexture(txt);
    SDL_FreeSurface(surf);
  }
};

int main() {
  string s;
  cout << "Napíš text: ";
  getline(cin, s);

  int ww = 800, wh = 600;

  SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_AUDIO);
  SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "2");

  window =
      SDL_CreateWindow("font", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                       ww, wh, SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN);
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
  IMG_Init(IMG_INIT_PNG);
  TTF_Init();

  TTF_Font *font = TTF_OpenFont("Montserrat-Medium.ttf", 50);
  Text t(renderer, font, s.data(), SDL_Color{.r = 10, .g = 80, .b = 150});

  bool running = true;
  int x = -t.box.w;

  while (running) {
    SDL_Event e;

    while (SDL_PollEvent(&e)) {
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
    }
    SDL_SetRenderDrawColor(renderer, 250, 180, 0, 255);
    SDL_RenderClear(renderer);

    t.render(renderer, x, (wh - t.box.h) / 2);
    x++;
    if (x > ww) x = -t.box.w;
    SDL_RenderPresent(renderer);

    uint32_t now = SDL_GetTicks();
    if (now < lastFrame + msPerFrame) SDL_Delay(lastFrame + msPerFrame - now);
    lastFrame = now;
  }

  IMG_Quit();
  TTF_Quit();
  SDL_DestroyWindow(window);
  SDL_Quit();
}
