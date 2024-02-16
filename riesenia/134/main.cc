#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <algorithm>

using namespace std;

SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;

int ww = 800, wh = 600;  // okno

uint32_t lastFrame = 0, FPS = 80;
uint32_t msPerFrame = 1000 / FPS;

struct Sprite {
  SDL_Texture* sheet;
  uint32_t lastTime;
  double posX, posY;
  double speed = 0.22;  // px / ms
  SDL_Rect src;
  int dir;

  Sprite() : src{.w = 64, .h = 64} {
    sheet = IMG_LoadTexture(renderer, "spritesheet.png");
    lastTime = SDL_GetTicks();
    posX = ww / 2.0;
    posY = wh / 2.0;
    dir = 2;
  }

  ~Sprite() { SDL_DestroyTexture(sheet); }

  void update() {
    uint32_t now = SDL_GetTicks();
    const uint8_t* keys = SDL_GetKeyboardState(nullptr);
    int arrows[4] = {SDL_SCANCODE_UP, SDL_SCANCODE_LEFT, SDL_SCANCODE_DOWN,
                     SDL_SCANCODE_RIGHT};
    int ord[4] = {0, 2, 1, 3};
    bool moving = false;
    double d = speed * (now - lastTime);

    for (int i = 0; i < 4; i++)
      if (keys[arrows[ord[i]]]) {
        moving = true;
        dir = ord[i];
        switch (ord[i]) {
          case 0:
            posY -= d;
            break;
          case 1:
            posX -= d;
            break;
          case 2:
            posY += d;
            break;
          case 3:
            posX += d;
            break;
        }
      }

    posX = max(-64.0, min((double)ww - 64.0, posX));
    posY = max(-64.0, min((double)wh - 64.0, posY));

    if (moving)
      src.x = 64 * (1 + (now / 80) % 8);
    else
      src.x = 0;
    src.y = 64 * (8 + dir);

    lastTime = now;
  }

  void render() {
    SDL_Rect dst{.x = (int)(posX), .y = (int)(posY), .w = 128, .h = 128};
    SDL_RenderCopy(renderer, sheet, &src, &dst);
  }
};

int main() {
  SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_AUDIO);
  SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "2");

  window = SDL_CreateWindow("prvy pokus", SDL_WINDOWPOS_CENTERED,
                            SDL_WINDOWPOS_CENTERED, ww, wh,
                            SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN);
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
  IMG_Init(IMG_INIT_PNG);

  Sprite dude;
  bool running = true;

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

    dude.update();

    SDL_SetRenderDrawColor(renderer, 250, 180, 0, 255);
    SDL_RenderClear(renderer);

    dude.render();

    SDL_RenderPresent(renderer);

    uint32_t now = SDL_GetTicks();
    if (now < lastFrame + msPerFrame) SDL_Delay(lastFrame + msPerFrame - now);
    lastFrame = now;
  }

  SDL_DestroyWindow(window);
  IMG_Quit();
  SDL_Quit();
}
