#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <iostream>
#include <string>

int main() {
  const int height = 400;
  const int width = 400;

  SDL_Window *w;

  SDL_Point window_position = {SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED};

  SDL_Point window_size = {600, 600};

  SDL_Point mouse_pos;
  SDL_Init(SDL_INIT_VIDEO);

  w = SDL_CreateWindow("test", window_position.x, window_position.y,
                       window_size.x, window_size.y, SDL_WINDOW_OPENGL);
  int x, y;
  SDL_Renderer *r = SDL_CreateRenderer(w, -1, SDL_RENDERER_PRESENTVSYNC);

  SDL_SetRenderDrawColor(r, 0xff, 0xff, 0xff, 0xff);

  bool quit = false;
  SDL_Event e;
  while (!quit) {
    while (SDL_PollEvent(&e) > 0) {

			switch(e.type) {
												case SDL_QUIT:
													quit = true;
                          break;
			};

      SDL_RenderClear(r);

      SDL_RenderDrawPoint(r, x, y);

      SDL_RenderPresent(r);
    };
  };
}
