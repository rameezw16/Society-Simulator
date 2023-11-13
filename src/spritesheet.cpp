#include "../include/spritesheet.hpp"

Spritesheet::Spritesheet(char const* path) {
	this->spritesheet_image = IMG_Load(path);

	//size of one sprite in pixels
	clip.w = 10;// spritesheet_image->w / col;
	clip.h = 10;//spritesheet_image->h / row;
};

Spritesheet::~Spritesheet() { SDL_FreeSurface(spritesheet_image); };

void Spritesheet::draw_sprite(const int n,  SDL_Rect* position, SDL_Renderer* renderer, SDL_Texture* texture) {
	//get coords on grid
	int x = n % spritesheet_image->w; //only need offset post wrapping
	int y = n / spritesheet_image->h ; //need to know how many times is wrapped

	//get coords in pixels		
	clip.x = x * spritesheet_image->w; 
	clip.y = y * spritesheet_image->h;

	SDL_RenderCopy(renderer, texture, &clip, position);


};




												 
