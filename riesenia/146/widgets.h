#ifndef __WIDGETS_H__
#define __WIDGETS_H__

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <vector>
#include <functional>
#include "text.h"
#include <string>
#include <functional>
#include "gradient.h"
#include "data.h"

SDL_Color clr(uint32_t c);

struct Widget {
  static SDL_Point mouse;

  SDL_Rect rect;
  int fixedHeight = 0;
  int fixedWidth = 0;
  int padding = 0;

  virtual ~Widget(){}

  virtual void resize(SDL_Rect _rect);
  virtual void render(SDL_Renderer *r){}
  virtual void onMouseMotion(SDL_MouseMotionEvent& e){}
  virtual void onMouseDown(SDL_MouseButtonEvent& e){}
  virtual void onMouseUp(SDL_MouseButtonEvent& e){}
};

struct Layout : Widget {
  std::vector<Widget *> children;
  std::vector<SDL_Rect> rects;

  ~Layout();
  void render(SDL_Renderer *r);

  Layout& operator<<(Widget *w);

  void onMouseMotion(SDL_MouseMotionEvent& e);
  void onMouseDown(SDL_MouseButtonEvent& e);
  void onMouseUp(SDL_MouseButtonEvent& e);


};

struct HLayout : Layout {
  void resize(SDL_Rect _rect);
};

struct VLayout : Layout {
  void resize(SDL_Rect _rect);
};

struct Button : Widget {
  static TTF_Font *font;

  Text label, labelDisabled;
  std::string txt;
  bool clicked;
  bool disabled;
  std::function<void(void)> onClick = [](){};

  SDL_Color bgNormal, bgHovered, bgClicked, bgDisabled, fgNormal, fgDisabled;

  Button(const std::string &_txt=" ");
  
  void render(SDL_Renderer *r);
  void onMouseMotion(SDL_MouseMotionEvent& e);
  void onMouseDown(SDL_MouseButtonEvent& e);
  void onMouseUp(SDL_MouseButtonEvent& e);

};

// grid for painting
struct Canvas : Widget {
  static constexpr int dim = 70;
  int pxdim, spacing;
  Data::Bytes img;
  bool painting;
  SDL_Point lastMouse;

  Canvas();  // konštruktor
  ~Canvas();

  void clear();
  SDL_Point imgCoord(SDL_Point);
  void dot(SDL_Point); // in img coordinates
  void line(SDL_Point,SDL_Point); // in screen coordinates

  void resize(SDL_Rect scr);        // nastaví všetko potrebné pri zmene okna
  void render(SDL_Renderer *renderer);

  void onMouseDown(SDL_MouseButtonEvent& e);
  void onMouseUp(SDL_MouseButtonEvent& e);
};


// colorful button
struct Bulb : Button {
  static const Gradient g;
  Bulb(const std::string &_txt) ;
  void set(double val) ;
};


#endif
