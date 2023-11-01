#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <iostream>
#include <string>
#include <math.h>
#include <random>



class Charecter {

public: //are public just for testing at the moment
	int health = 100;
	int radius;
	bool predator;
	bool prey;

	SDL_Renderer * r;
	SDL_Rect rect;

	Charecter(SDL_Renderer * r, int x, int y, int w, int h, int radius) : r(r), radius(radius) {
		this->rect.x = x;
		this->rect.y = y;
		this->rect.w = w;
		this->rect.h = h;
	};

	void display() {
		if (this->health > 0) SDL_SetRenderDrawColor(r, 0xff, 0x00, 0x00, 0xff);
		else SDL_SetRenderDrawColor(r, 0x00, 0x00, 0xff, 0xff);
			SDL_RenderFillRect(r,&rect);
			SDL_SetRenderDrawColor(r, 0x00, 0x00, 0x00, 0xff);
	};

	bool isInRange(Charecter &other) { //checks whether the other is in range of this character

		int d1 = this->rect.x - other.rect.x;
		int d2 = this->rect.y - other.rect.y;


		if (std::sqrt(d1 * d1 + d2 * d2) < this->radius) {
			std::cout << std::sqrt(d1 * d1 + d2 * d2);
			return true;
		};
		return false;
	};

	void moveInDirection(Charecter &other) {
		int factor = 20;
		SDL_Point temp {(other.rect.x - this->rect.x)/factor, (other.rect.y - this->rect.x)/factor} ; //turn this into float tuple
		this->rect.x += temp.x;
		this->rect.y += temp.y;
	};

	void randomWalk() {
		int rad = 10;
		int angle = rand() % 360;
		float s = rad * std::cos(angle);

		this->rect.x += s;
		this->rect.y += s;


	};
};


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

  SDL_SetRenderDrawColor(r, 0x00, 0x00, 0x00, 0xff);

	Charecter predator1(r, 100, 100, 10, 10, 150);
	Charecter predator2(r, 200, 200, 10, 10, 150);
	Charecter predator3(r, 150, 100, 30, 30, 40);
	Charecter predator4(r, 200, 200, 10, 10, 90);
	Charecter predator5(r, 100, 201, 10, 10, 40);
	Charecter predator6(r, 200, 300, 10, 10, 90);

	bool quit = false;
  SDL_Event e;
  while (!quit) {
    while (SDL_PollEvent(&e) > 0) {

			switch(e.type) {
												case SDL_QUIT:
													quit = true;
                          break;
			};
		};

      SDL_RenderClear(r);
			predator1.display();
			predator2.display();
			predator3.display();
			predator4.display();
			predator5.display();
			predator6.display();




			predator1.randomWalk();
			predator2.randomWalk();
			predator3.randomWalk();
			predator4.randomWalk();
			predator5.randomWalk();
			predator6.randomWalk();

			if (predator1.isInRange(predator2)) {
				predator1.moveInDirection(predator2);
				predator2.health -= 1;
			};


      SDL_RenderPresent(r);
  };
};
