#include <SDL2/SDL.h>
#include <random>

using namespace std;

SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;
mt19937 rnd{random_device{}()};

int main() {

  SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_AUDIO);

  window = SDL_CreateWindow("prvy pokus", SDL_WINDOWPOS_CENTERED,
                            SDL_WINDOWPOS_CENTERED, 800, 600,
                            SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN);
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

  SDL_SetRenderDrawColor(renderer, 250, 180, 0, 255);
  SDL_RenderClear(renderer);

  SDL_Rect r{.x=300,.y=200,.w=200,.h=200};
  SDL_SetRenderDrawColor(renderer, 20, 30, 180, 255);
  SDL_RenderFillRect(renderer, &r);

  SDL_RenderPresent(renderer);

  SDL_Delay(2000);

  SDL_DestroyWindow(window);
  SDL_Quit();
}
