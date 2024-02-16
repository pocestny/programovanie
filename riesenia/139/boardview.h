#ifndef __BOARDVIEW_H__
#define __BOARDVIEW_H__
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

#include "board.h"
#include "text.h"
#include "widgets.h"
#include <functional>

struct BoardView : Widget {
  Board board;          // aktuálna pozícia
  SDL_Texture* pieces;  // textúra s bielym a čiernym kameňom
  Mix_Chunk* move, *capture;
  Mix_Music* test;

  std::function<void(Move)> moveAvailable = [](Move){};

  uint8_t human;      // človek je Biely(0) / Čierny (1)
  bool flippedBoard;  // zobrazujem šachovnicu z pohľadu čierneho

  bool dragging, animating;  // ťahá hráč / počítač
  Square dragOrig;           // odkiaľ hráč začal ťah
  Move aMove;                // počítačový ťah, ktorý sa animuje
  const int animLen = 200;   // dľžka animácie (ms)
  uint32_t animEndTime;      // kedy skončí aktuálna animácia

  const double pieceMargin = 0.15;  // (relatívna) medzera na kraji kameňa
  int boardDim;                     // rozmer šachovnice
  int squareSize, pieceOffs;  // veľkosť políčka, (absolútna) medzera na kraji
  int markSize;               // veľkosť fontu na značenie
  Text fileMark[8], rankMark[8];  // vyrenderované značenia na šachovnici
  int winSize;
  Text winText[2];
  bool dirtyMarks;    // treba pregenerovat fileMark a rankMark
  bool lastMove; // zvýrazniť aMove

  BoardView();  // konštruktor
  ~BoardView();

  void reset(Board brd);
  void resize(SDL_Rect scr);        // nastaví všetko potrebné pri zmene okna
  SDL_Rect pieceBox(int f, int r);  // kam sa renderuje políčko (f,r)
  SDL_Rect pieceBox(const Square& s);
  SDL_Rect squareBox(const Square& s);
  Square squareAt(int x, int y);  // aké je políčko na (x,y)
  void resetMarks(SDL_Renderer *r);

  void render(SDL_Renderer *renderer);

  void operator+=(const Move& m);

  void onMouseDown(SDL_MouseButtonEvent& e);
  void onMouseUp(SDL_MouseButtonEvent& e);
};

#endif
