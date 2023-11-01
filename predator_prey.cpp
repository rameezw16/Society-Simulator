#include <SDL2/SDL_events.h>
#include <SDL2/SDL_render.h>
#include <string>
#include <SDL2/SDL.h>
#include <iostream>





int main() {
	const int height = 400;
	const int width = 400;

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		return 1;
		std::cout << "init failed" << "\n";
	}

	SDL_Window *w = SDL_CreateWindow("test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);

	if (w == nullptr) {
		std::cout << "window error";
		return 1;
	};

	SDL_Renderer * r = SDL_CreateRenderer(w,0,SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	int x = width /2;
	int y = height /2;

	bool quit = false;
	SDL_Event event;

	while (!quit) {

		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				quit = true;
			}
		}
		
		SDL_RenderClear(r);
		SDL_SetRenderDrawColor(r, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderDrawPoint(r, x, y);
		SDL_SetRenderDrawColor(r, 0x00, 0x00, 0x00, 0xFF);
		SDL_RenderPresent(r);

	}


	SDL_DestroyWindow(w);
	SDL_DestroyRenderer(r);
	SDL_Quit();

}

