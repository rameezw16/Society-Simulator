#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>


class Spritesheet {
public:
	Spritesheet(char const* path, SDL_Renderer* renderer);
	~Spritesheet();

	void draw_sprite(const int n, SDL_Rect* position, SDL_Texture* texture); //draw the nth sprite, will use an enum to make this easier


private:
	SDL_Rect clip;
	SDL_Texture *texture;
	SDL_Renderer *renderer;
	
	int height;
	int width;

};




