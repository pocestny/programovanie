#include "widgets.h"

using namespace std;

SDL_Point Widget::mouse = SDL_Point{0, 0};
TTF_Font *Button::font = nullptr;

SDL_Color clr(uint32_t c) {
  return SDL_Color{(Uint8)(c >> 24), (Uint8)((c >> 16) & 0xff),
                   (Uint8)((c >> 8) & 0xff), (Uint8)(c & 0xff)};
}

void Widget::resize(SDL_Rect _rect) {
  rect = _rect;
  rect.x += padding;
  rect.y += padding;
  if (fixedWidth) rect.w = fixedWidth;
  if (fixedHeight) rect.h = fixedHeight;
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

Canvas::Canvas() : img(dim) {
  padding = 5;
  spacing = 1;
  pxdim = 100;
  painting = false;
  clear();
}

Canvas::~Canvas() {}

SDL_Point Canvas::imgCoord(SDL_Point p) {
  p.x = (p.x - rect.x) / (pxdim + spacing);
  p.y = (p.y - rect.y) / (pxdim + spacing);
  return p;
}

void Canvas::dot(SDL_Point p) {
  for (int i = p.x - 1; i <= p.x+2; i++)
    for (int j = p.y - 1; j <= p.y+2; j++)
      if (i < dim && j < dim && i >= 0 && j >= 0) img(i,j) = 0;
}

void Canvas::line(SDL_Point p1, SDL_Point p2) {
  if (p1.x == p2.x) {
    if (p1.y > p2.y) swap(p1.y, p2.y);
    for (; p1.y <= p2.y; p1.y++) dot(imgCoord(p1));
  } else if (p1.y == p2.y) {
    if (p1.x > p2.x) swap(p1.x, p2.x);
    for (; p1.x <= p2.x; p1.x++) dot(imgCoord(p1));
  } else {
    if (p1.x > p2.x) swap(p1, p2);
    double s = (double)(p2.y - p1.y) / (double)(p2.x - p1.x);
    if (s >= -1 && s <= 1) {
      double dx = 0.5;
      for (int i = 0; i < p2.x - p1.x; i++)
        dot(imgCoord(SDL_Point{.x = (int)(p1.x + 0.5 + i),
                               .y = (int)(p1.y + (dx + i) * s)}));
    } else {
      if (p1.y > p2.y) swap(p1, p2);
      s = 1 / s;
      double dy = 0.5;
      for (int i = 0; i < p2.y - p1.y; i++)
        dot(imgCoord(SDL_Point{.x = (int)(p1.x + (dy + i) * s),
                               .y = (int)(p1.y + i + 0.5)}));
    }
  }
}

void Canvas::clear() {
  for (int i = 0; i < dim; i++)
    for (int j = 0; j < dim; j++) img(i,j) = 255;
}

void Canvas::resize(SDL_Rect scr) {
  Widget::resize(scr);
  pxdim = max(5, (min(rect.w, rect.h) - (dim - 1) * spacing) / dim);
}

void Canvas::render(SDL_Renderer *renderer) {
  SDL_RenderSetClipRect(renderer, &rect);
  if (!SDL_PointInRect(&mouse, &rect)) painting = false;

  if (painting) line(lastMouse, mouse);

  for (int i = 0; i < dim; i++)
    for (int j = 0; j < dim; j++) {
      SDL_Rect r{.x = rect.x + i * (pxdim + spacing),
                 .y = rect.y + j * (pxdim + spacing),
                 .w = pxdim,
                 .h = pxdim};
      SDL_SetRenderDrawColor(renderer, img(i,j), img(i,j), img(i,j), 0xff);
      SDL_RenderFillRect(renderer, &r);
    }

  SDL_RenderSetClipRect(renderer, nullptr);
  lastMouse = mouse;
}

void Canvas::onMouseDown(SDL_MouseButtonEvent &e) {
  painting = true;
  lastMouse = mouse;
}

void Canvas::onMouseUp(SDL_MouseButtonEvent &e) { painting = false; }

Bulb::Bulb(const string &_txt) : Button(_txt) {
  disabled = true;
  fgDisabled = clr(0xff);
  set(-1);
}

void Bulb::set(double val) {
  Vec3 v = g((1 - 0.999 * val) / 2.0);
  bgDisabled = SDL_Color{.r = (uint8_t)(v.x * 255),
                         .g = (uint8_t)(v.y * 255),
                         .b = (uint8_t)(v.z * 255)};
}

