#include "boardview.h"

#include <algorithm>

using namespace std;

SDL_Color clr(uint32_t c) {
  return SDL_Color{(Uint8)(c >> 24), (Uint8)((c >> 16) & 0xff),
                   (Uint8)((c >> 8) & 0xff), (Uint8)(c & 0xff)};
}

BoardView::BoardView() {
  flippedBoard = dragging = animating = lastMove = false;
  pieces = nullptr;
  human = White;

  move = Mix_LoadWAV("move.wav");
  capture = Mix_LoadWAV("capture.wav");
}

BoardView::~BoardView() {
  if (pieces != nullptr) SDL_DestroyTexture(pieces);
}

void BoardView::reset(Board brd) {
  dragging = animating = lastMove = false;
  board=brd;
}

void BoardView::resize(SDL_Rect scr) {
  rect = scr;
  boardDim = max(min(scr.w, scr.h), 500);
  squareSize = boardDim / 8.0;
  pieceOffs = boardDim * pieceMargin / 8.0;
  boardDim = 8 * squareSize;
  rect.w = rect.h = boardDim;
  markSize = 0.2 * squareSize;
  winSize = 4 * markSize;
  dirtyMarks = true;
}

void BoardView::resetMarks(SDL_Renderer* renderer) {
  TTF_Font* font = TTF_OpenFont("Montserrat-Bold.ttf", markSize);
  const uint32_t markClr = 0xeceff1ff;
  const char* files[] = {"a", "b", "c", "d", "e", "f", "g", "h"};
  const char* ranks[] = {"1", "2", "3", "4", "5", "6", "7", "8"};

  for (int i = 0; i < 8; i++)
    fileMark[i].init(renderer, font, files[i], clr(markClr));
  for (int i = 0; i < 8; i++)
    rankMark[i].init(renderer, font, ranks[i], clr(markClr));
  TTF_CloseFont(font);

  TTF_OpenFont("Montserrat-Bold.ttf", winSize);
  const uint32_t winClr = 0xffa000ff;
  winText[1].init(renderer, font, "čierny vyhral", clr(winClr));
  winText[0].init(renderer, font, "biely vyhral", clr(winClr));
  TTF_CloseFont(font);

  dirtyMarks = false;
}

SDL_Rect BoardView::pieceBox(int f, int r) {
  int rr = 7 - r, ff = f;
  if (flippedBoard) {
    rr = r;
    ff = 7 - f;
  }
  return SDL_Rect{ff * squareSize + pieceOffs, rr * squareSize + pieceOffs,
                  squareSize - 2 * pieceOffs, squareSize - 2 * pieceOffs};
}

SDL_Rect BoardView::pieceBox(const Square& s) { return pieceBox(s.f, s.r); }

SDL_Rect BoardView::squareBox(const Square& s) {
  int rr = 7 - s.r, ff = s.f;
  if (flippedBoard) {
    rr = s.r;
    ff = 7 - s.f;
  }
  return SDL_Rect{ff * squareSize, rr * squareSize, squareSize, squareSize};
}

Square BoardView::squareAt(int x, int y) {
  x -= rect.x;
  y -= rect.y;
  uint8_t f = x / squareSize, r = 7 - y / squareSize;
  if (flippedBoard) {
    f = 7 - f;
    r = 7 - r;
  }
  return Square{f, r};
}

void BoardView::render(SDL_Renderer* renderer) {
  SDL_RenderSetClipRect(renderer, &rect);
  if (!SDL_PointInRect(&mouse, &rect)) dragging = false;

  if (pieces == nullptr) pieces = IMG_LoadTexture(renderer, "pieces.png");

  if (dirtyMarks) resetMarks(renderer);
  // pozadie
  SDL_SetRenderDrawColor(renderer, 0xb0, 0xbe, 0xc5, 0xff);
  SDL_RenderFillRect(renderer, &rect);

  // highlight
  if (dragging) {
    SDL_SetRenderDrawColor(renderer, 0xb3, 0xe5, 0xfc, 0x50);
    SDL_Rect r = squareBox(dragOrig);
    SDL_RenderFillRect(renderer, &r);

    SDL_SetRenderDrawColor(renderer, 0xb3, 0xe5, 0xfc, 0x90);
    r = squareBox(squareAt(mouse.x, mouse.y));
    SDL_RenderFillRect(renderer, &r);
  }
  if (lastMove) {
    SDL_SetRenderDrawColor(renderer, 0xbc, 0xaa, 0xa4, 0x30);
    SDL_Rect r = squareBox(aMove.from);
    SDL_RenderFillRect(renderer, &r);
    SDL_SetRenderDrawColor(renderer, 0xbc, 0xaa, 0xa4, 0x40);
    r = squareBox(aMove.to);
    SDL_RenderFillRect(renderer, &r);
  }

  // ciary a znacenie
  for (int i = 0; i < 9; i++) {
    int dst = i * squareSize;
    SDL_SetRenderDrawColor(renderer, 0x60, 0x7b, 0x8b, 0xff);
    SDL_RenderDrawLine(renderer, rect.x + dst, rect.y, rect.x + dst,
                       rect.y + rect.h);
    SDL_RenderDrawLine(renderer, rect.x, rect.y + dst, rect.x + rect.w,
                       rect.y + dst);
    int ff = (flippedBoard) ? 8 - i : i - 1, rr = (flippedBoard) ? i : 7 - i;

    if (ff >= 0 && ff < 8)
      fileMark[ff].render(renderer, rect.x + dst - (1 + markSize),
                          rect.y + rect.h - (8 + markSize));
    if (rr >= 0 && rr < 8)
      rankMark[rr].render(renderer, rect.x + 5, rect.y + dst + 8);
  }

  // kamene
  for (uint8_t f = 0; f < 8; f++)
    for (uint8_t r = 0; r < 8; r++) {
      Square sq{f, r};
      if (dragging && sq == dragOrig) continue;
      if (animating && sq == aMove.from) continue;
      int sd = board.get(f, r);
      if (sd == Empty) continue;
      SDL_Rect src{sd * 500, 0, 500, 500}, dst = pieceBox(f, r);
      SDL_RenderCopy(renderer, pieces, &src, &dst);
    }

  if (animating) {
    uint32_t now = SDL_GetTicks();
    if (now > animEndTime) {
      animating = false;
      board += aMove;
    } else {
      double t = 1.0 - (double)(animEndTime - now) / (double)animLen;
      SDL_Rect src{(1 - human) * 500, 0, 500, 500}, from = pieceBox(aMove.from),
                                                    to = pieceBox(aMove.to);
      from.x += t * (to.x - from.x);
      from.y += t * (to.y - from.y);
      SDL_RenderCopy(renderer, pieces, &src, &from);
    }
  }

  if (dragging) {
    SDL_Rect src{human * 500, 0, 500, 500}, dst = pieceBox(0, 0);
    dst.x = mouse.x - dst.w / 2;
    dst.y = mouse.y - dst.h / 2;
    SDL_RenderCopy(renderer, pieces, &src, &dst);
  }

  if (board.winner() != Empty)
    winText[board.winner()].render(
        renderer, rect.x + (rect.w - winText[board.winner()].box.w) / 2,
        rect.y + (rect.h - winText[board.winner()].box.h) / 2);

  SDL_RenderSetClipRect(renderer, nullptr);
}

void BoardView::operator+=(const Move& m) {
  animating = true;
  aMove = m;
  lastMove = true;
  animEndTime = SDL_GetTicks() + animLen;
  if (board.get(m.to.f, m.to.r) == Empty)
    Mix_PlayChannel(-1, move, 0);
  else
    Mix_PlayChannel(-1, capture, 0);
}

void BoardView::onMouseDown(SDL_MouseButtonEvent& e) {
  if (dragging || board.winner() != Empty) return;
  Square s = squareAt(e.x, e.y);
  if (board.get(s.f, s.r) != human) return;
  dragging = true;
  dragOrig = s;
}

void BoardView::onMouseUp(SDL_MouseButtonEvent& e) {
  if (!dragging) return;
  Move m{dragOrig, squareAt(e.x, e.y)};
  if (board.legal(m)) {
    if (board.get(m.to.f, m.to.r) == Empty)
      Mix_PlayChannel(-1, move, 0);
    else
      Mix_PlayChannel(-1, capture, 0);
    board += m;
    lastMove = false;
    moveAvailable(m);
  }
  dragging = false;
}
