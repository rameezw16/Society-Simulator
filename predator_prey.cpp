#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <iostream>
#include <math.h>
#include <random>
#include <string>
#include <vector>

class Charecter {

public: // are public just for testing at the moment
  int health = 100;
  int radius;
  bool predator;
  bool prey;

  SDL_Renderer *r;
  SDL_Rect rect;

  Charecter *target = this;

  Charecter(SDL_Renderer *r, int x, int y, int w, int h, int radius)
      : r(r), radius(radius) {
    this->rect.x = x;
    this->rect.y = y;
    this->rect.w = w;
    this->rect.h = h;
  };

  void display() {
    if (this->health > 0)
      SDL_SetRenderDrawColor(r, 0xff, 0x00, 0x00, 0xff);
    else
      SDL_SetRenderDrawColor(r, 0x00, 0x00, 0xff, 0xff);
    SDL_RenderFillRect(r, &rect);
    SDL_SetRenderDrawColor(r, 0x00, 0x00, 0x00, 0xff);
  };

  bool isInRange(Charecter &other) { // checks whether the other is in range of
                                     // this character

    int d1 = this->rect.x - other.rect.x;
    int d2 = this->rect.y - other.rect.y;

    if (std::sqrt(d1 * d1 + d2 * d2) < this->radius) {
      return true;
    };
    return false;
  };

  void moveToTarget() {
    int factor = 20;
		if (this->target == nullptr) return;
    SDL_Point temp{(this->target->rect.x - this->rect.x) / factor,
                   (this->target->rect.y - this->rect.x) / factor}; // turn this into float tuple
    if (this->rect.x + temp.x < 400 and this->rect.y + temp.y < 400 and
        this->rect.x - temp.x > 0 and this->rect.y - temp.y > 0) {

				this->rect.x += temp.x;
				this->rect.y += temp.y;
		}
  };

  void randomWalk() {

    int choice = rand() % 3;
    int s = 5;
    if (this->rect.x + s < 400 and this->rect.y + s < 400 and
        this->rect.x - s > 0 and this->rect.y - s > 0) {
      switch (choice) {
      case 0:
        this->rect.x += s;
        this->rect.y += 0;
        break;
      case 1:
        this->rect.x -= s;
        this->rect.y += 0;
        break;
      case 2:
        this->rect.x += 0;
        this->rect.y += s;
        break;
      case 3:
        this->rect.x += 0;
        this->rect.y += s;
        break;
      };
    };
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

  std::vector<Charecter *> predators;
  int xpos;
  int ypos;
  int pWidth;
  int pHeight;
  int radius;
  int num = 5;

  for (int i = 0; i < num; i++) {
    xpos = width - (rand() % width);
    ypos = rand() % height;
    pWidth = rand() % 40;
    pHeight = pWidth;
    Charecter *temp = new Charecter{r, xpos, ypos, pWidth, pHeight, radius};
    predators.push_back(temp);
  };

  bool quit = false;
  SDL_Event e;
  while (!quit) {
    while (SDL_PollEvent(&e) > 0) {

      switch (e.type) {
      case SDL_QUIT:
        quit = true;
        break;
      };
    };

    SDL_RenderClear(r);

    for (int i = 0; i < num; i++) {
      predators[i]->display();
    };

    for (int i = 0; i < num; i++) {
      predators[i]->randomWalk();
    };

    for (int i = 0; i < num; i++) {
      for (int j = 0; j < num; j++) {
        if (predators[i]->isInRange(*predators[j])) {
          predators[i]->moveToTarget();
					if (predators[i]->target != nullptr) predators[i]->target->health -= 1;
        }
      }
    };

    SDL_RenderPresent(r);
    SDL_Delay(100);
  };

  for (int i = 0; i < num; i++) {
    delete predators[i];
  };
};
