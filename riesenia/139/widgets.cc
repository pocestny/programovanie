#include "widgets.h"

using namespace std;

SDL_Point Widget::mouse = SDL_Point{0, 0};
TTF_Font *Button::font = nullptr;

void Widget::resize(SDL_Rect _rect) {
  rect = _rect;
  rect.x += padding;
  rect.y += padding;
  rect.w -= 2 * padding;
  rect.h -= 2 * padding;
}

Layout::~Layout() {
  for (auto &c : children) delete c;
}

Layout &Layout::operator<<(Widget *w) {
  children.push_back(w);
  resize(rect);
  return *this;
}

void Layout::render(SDL_Renderer *r) {
  for (auto &c : children) c->render(r);
}

void Layout::onMouseMotion(SDL_MouseMotionEvent &e) {
  for (auto &c : children)
    if (SDL_PointInRect(&mouse, &(c->rect))) c->onMouseMotion(e);
}

void Layout::onMouseDown(SDL_MouseButtonEvent &e) {
  for (auto &c : children)
    if (SDL_PointInRect(&mouse, &(c->rect))) c->onMouseDown(e);
}

void Layout::onMouseUp(SDL_MouseButtonEvent &e) {
  for (auto &c : children)
    if (SDL_PointInRect(&mouse, &(c->rect))) c->onMouseUp(e);
}

void HLayout ::resize(SDL_Rect _rect) {
  Layout::resize(_rect);
  rects.resize(children.size());
  for (int i = 0; i < children.size(); i++) {
    rects[i].y = rect.y;
    rects[i].h = rect.h;
  }

  int sumFixed = 0, numFree = 0;
  for (auto &c : children) {
    sumFixed += c->fixedWidth;
    if (c->fixedWidth == 0) numFree++;
  }

  if (sumFixed + children.size() >
      rect.w) {  // fixovane sa nezmestia. delime vsetky proporcionalne
    double w = (double)rect.w / (double)children.size();
    for (int i = 0; i < children.size(); i++) {
      rects[i].w = (int)((i + 1) * w) - (int)(i * w);
      if (i == 0)
        rects[i].x = rect.x;
      else
        rects[i].x = rects[i - 1].x + rects[i - 1].w;
    }
  } else {
    double w = (double)(rect.w - sumFixed) / (double)numFree;
    int wsum = 0;
    for (int i = 0; i < children.size(); i++) {
      if (children[i]->fixedWidth > 0)
        rects[i].w = children[i]->fixedWidth;
      else
        rects[i].w = w;
      if (i == 0)
        rects[i].x = rect.x;
      else
        rects[i].x = rects[i - 1].x + rects[i - 1].w;
      if (i == children.size() - 1) rects[i].w = rect.w - wsum;
      wsum += rects[i].w;
    }
  }
  for (int i = 0; i < children.size(); i++) children[i]->resize(rects[i]);
}

void VLayout ::resize(SDL_Rect _rect) {
  Layout::resize(_rect);
  rects.resize(children.size());
  for (int i = 0; i < children.size(); i++) {
    rects[i].x = rect.x;
    rects[i].w = rect.w;
  }

  int sumFixed = 0, numFree = 0;
  for (auto &c : children) {
    sumFixed += c->fixedHeight;
    if (c->fixedHeight == 0) numFree++;
  }

  if (sumFixed + children.size() >
      rect.h) {  // fixovane sa nezmestia. delime vsetky proporcionalne
    double h = (double)rect.h / (double)children.size();
    for (int i = 0; i < children.size(); i++) {
      rects[i].h = (int)((i + 1) * h) - (int)(i * h);
      if (i == 0)
        rects[i].y = rect.y;
      else
        rects[i].y = rects[i - 1].y + rects[i - 1].h;
    }
  } else {
    double h = (double)(rect.h - sumFixed) / (double)numFree;
    int hsum = 0;
    for (int i = 0; i < children.size(); i++) {
      if (children[i]->fixedHeight > 0)
        rects[i].h = children[i]->fixedHeight;
      else
        rects[i].h = h;
      if (i == 0)
        rects[i].y = rect.y;
      else
        rects[i].y = rects[i - 1].y + rects[i - 1].h;
      if (i == children.size() - 1) rects[i].h = rect.h - hsum;
      hsum += rects[i].h;
    }
  }
  for (int i = 0; i < children.size(); i++) children[i]->resize(rects[i]);
}

Button::Button(const string &_txt) {
  txt = _txt;
  clicked = false;
  disabled = false;
  bgNormal = clr(0xff8f00ff);
  bgHovered = clr(0xffb300ff);
  bgClicked = clr(0xffe082ff);
  bgDisabled = clr(0xbdbdbdff);
  fgNormal = clr(0x616161ff);
  fgDisabled = clr(0xeeeeeeff);
  fixedHeight = 50;
  padding = 8;
  if (!font) font = TTF_OpenFont("Montserrat-Medium.ttf", 17);
}

void Button::render(SDL_Renderer *renderer) {
  SDL_RenderSetClipRect(renderer, &rect);
  SDL_Color c = bgNormal;

  if (SDL_PointInRect(&mouse, &rect)) c = bgHovered;
  if (clicked) c = bgClicked;

  if (disabled) c = bgDisabled;

  SDL_SetRenderDrawColor(renderer, c.r, c.g, c.b, 0xff);
  SDL_RenderFillRect(renderer, &rect);

  if (!label) {
    label.init(renderer, font, txt.data(), fgNormal);
    labelDisabled.init(renderer, font, txt.data(), fgDisabled);
  }
  int xx = rect.x + (rect.w - label.box.w) / 2,
      yy = rect.y + (rect.h - label.box.h) / 2;
  if (disabled)
    labelDisabled.render(renderer, xx, yy);
  else
    label.render(renderer, xx, yy);

  SDL_RenderSetClipRect(renderer, nullptr);
}

void Button::onMouseMotion(SDL_MouseMotionEvent &e) {}

void Button::onMouseDown(SDL_MouseButtonEvent &e) {
  if (!disabled) clicked = true;
}

void Button::onMouseUp(SDL_MouseButtonEvent &e) {
  if (disabled) return;
  onClick();
  clicked = false;
}
