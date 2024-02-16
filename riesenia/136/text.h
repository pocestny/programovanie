#ifndef __TEXT_H__
#define __TEXT_H__

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

struct Text {
  SDL_Surface* surf;
  SDL_Texture* txt;
  SDL_Rect box;

  Text();
  Text(SDL_Renderer* renderer, TTF_Font* font, const char* text,
       SDL_Color color);

  Text(Text&&) = default;
  Text& operator=(Text&&) = default;
  Text(const Text&) = delete;
  Text& operator=(const Text&) = delete;

  void init(SDL_Renderer* renderer, TTF_Font* font, const char* text,
            SDL_Color color);
  void render(SDL_Renderer* renderer, int x, int y);
  ~Text();
};

#endif
