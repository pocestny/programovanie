#include "text.h"

Text::Text() {
  surf = nullptr;
  txt = nullptr;
}

Text::Text(SDL_Renderer* renderer, TTF_Font* font, const char* text,
           SDL_Color color) {
  surf = nullptr;
  txt = nullptr;
  init(renderer, font, text, color);
}

void Text::init(SDL_Renderer* renderer, TTF_Font* font, const char* text,
                SDL_Color color) {
  if (txt) SDL_DestroyTexture(txt);
  if (surf) SDL_FreeSurface(surf);
  surf = TTF_RenderUTF8_Blended(font, text, color);
  box.h = surf->h;
  box.w = surf->w;
  txt = SDL_CreateTextureFromSurface(renderer, surf);
}

void Text::render(SDL_Renderer* renderer, int x, int y) {
  box.x = x;
  box.y = y;
  SDL_RenderCopy(renderer, txt, nullptr, &box);
}

Text::~Text() {
  if (txt) SDL_DestroyTexture(txt);
  if (surf) SDL_FreeSurface(surf);
}
