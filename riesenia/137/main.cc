#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <algorithm>
#include <iostream>
#include <vector>

#include "boardview.h"
#include "alphabetaplayer.h"
#include "text.h"

using namespace std;

SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;

int ww = 800, wh = 600;  // okno

uint32_t lastFrame = 0, FPS = 80;
uint32_t msPerFrame = 1000 / FPS;

void mainLoop() {
  bool running = true;
  BoardView bv(renderer);
  bv.resize(SDL_Rect{0, 0, ww, wh});
  AlphaBetaPlayer plr;

  while (running) {
    SDL_Event e;

    while (SDL_PollEvent(&e)) {
      switch (e.type) {
        case SDL_WINDOWEVENT:
          switch (e.window.event) {
            case SDL_WINDOWEVENT_SIZE_CHANGED:
              ww = e.window.data1;
              wh = e.window.data2;
              bv.resize(SDL_Rect{0, 0, ww, wh});
              break;
          }
          break;
        case SDL_QUIT:
          running = false;
          break;
        case SDL_MOUSEMOTION:
          bv.onMouseMotion(e.motion);
          break;
        case SDL_MOUSEBUTTONDOWN:
          bv.onMouseDown(e.button);
          break;
        case SDL_MOUSEBUTTONUP:
          if (bv.onMouseUp(e.button).from.legal() &&
              bv.board.winner() == Empty) {
            plr.startThinking(bv.board);
          }
          break;
        case SDL_KEYDOWN:
          SDL_Keysym k = e.key.keysym;
          if (k.sym == SDLK_f) bv.flippedBoard = !bv.flippedBoard;
          if (k.sym == SDLK_q && ((k.mod & (KMOD_LCTRL | KMOD_RCTRL)) != 0))
            running = false;
      }
    }

    SDL_SetRenderDrawColor(renderer, 250, 180, 0, 255);
    SDL_RenderClear(renderer);
    bv.render();
    SDL_RenderPresent(renderer);

    if (plr.thinking) {
        while (!plr.finished) {
          plr.step();
          uint32_t now = SDL_GetTicks();
          if (now >lastFrame + msPerFrame) break;
        }
       if (plr.finished) {
         Move m = plr.getResult();
         bv+=m;
       }
    }

    uint32_t now = SDL_GetTicks();
    if (now < lastFrame + msPerFrame) SDL_Delay(lastFrame + msPerFrame - now);
    lastFrame = now;
  }
}

int main() {
  SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_AUDIO);
  SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "2");

  window = SDL_CreateWindow("Breakthrough", SDL_WINDOWPOS_CENTERED,
                            SDL_WINDOWPOS_CENTERED, ww, wh,
                            SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN);
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
  IMG_Init(IMG_INIT_PNG);
  TTF_Init();

  Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024);
  Mix_AllocateChannels(4);
  Mix_MasterVolume(80);

  mainLoop();

  SDL_DestroyWindow(window);
  IMG_Quit();
  TTF_Quit();
  SDL_Quit();
}
