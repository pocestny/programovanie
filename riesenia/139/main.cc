#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

#include <algorithm>
#include <iostream>
#include <vector>

#include "alphabetaplayer.h"
#include "boardview.h"
#include "widgets.h"

using namespace std;

SDL_Window *window = nullptr;
SDL_Renderer *renderer = nullptr;

int ww = 950, wh = 800;  // okno

uint32_t lastFrame = 0, FPS = 80;
uint32_t msPerFrame = 1000 / FPS;

AlphaBetaPlayer *plr = nullptr;

HLayout mainWindow;
BoardView *bv = nullptr;
Button *undoButton = nullptr;

bool running = true;

vector<Board> undoStack;

void reset(Board brd = Board{}) {
  delete plr;
  plr = new AlphaBetaPlayer;
  bv -> reset(brd);
  undoButton->disabled = undoStack.size()<2;
}

void mainLoop() {
  undoStack.push_back(Board{});
  plr = new AlphaBetaPlayer;

  bv = new BoardView();
  VLayout *vl = new VLayout();
  vl->fixedWidth = 150;
  mainWindow << bv << vl;

  Button *b1 = new Button("nová hra"), *b2 = new Button("otoč"),
         *b3 = new Button("koniec");
  undoButton = new Button("naspäť");
  undoButton->disabled = true;

  undoButton->onClick = [](){
    if (undoStack.size()<2) return;
    undoStack.pop_back();
    Board bb = undoStack.back();    
    reset(bb);
  };

  (*vl) << b1 << b2 << undoButton << new Widget() << b3;

  b1->onClick = []() { undoStack.clear(); undoStack.push_back(Board{}); reset(); };
  b2->onClick = []() { bv->flippedBoard = !bv->flippedBoard; };
  b3->onClick = []() { running = false; };

  bv->moveAvailable = [](Move m) {
    if (bv->board.winner() == Empty) {
      plr->startThinking(bv->board);
    }
  };

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
          Widget::mouse = SDL_Point(e.motion.x, e.motion.y);
          mainWindow.onMouseMotion(e.motion);
          break;
        case SDL_MOUSEBUTTONDOWN:
          mainWindow.onMouseDown(e.button);
          break;
        case SDL_MOUSEBUTTONUP:
          mainWindow.onMouseUp(e.button);
          break;
        case SDL_KEYDOWN:
          SDL_Keysym k = e.key.keysym;
          if (k.sym == SDLK_f) bv->flippedBoard = !bv->flippedBoard;
          if (k.sym == SDLK_q && ((k.mod & (KMOD_LCTRL | KMOD_RCTRL)) != 0))
            running = false;
      }
    }

    Move m = plr->getMove();
    if (bv->board.legal(m)) {
      (*bv) += m;
      Board bb = bv->board;
      bb += m;
      undoStack.push_back(bb);
      undoButton->disabled=false;
    }

    SDL_SetRenderDrawColor(renderer, 0x54, 0x6e, 0x7a, 255);
    SDL_RenderClear(renderer);
    mainWindow.render(renderer);
    SDL_RenderPresent(renderer);

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
                            /*SDL_WINDOW_RESIZABLE |*/ SDL_WINDOW_SHOWN);
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
