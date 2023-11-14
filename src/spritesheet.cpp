#include "../include/spritesheet.hpp"

Spritesheet::Spritesheet(char const* path, SDL_Renderer* renderer) {
	this->texture = IMG_LoadTexture(renderer,path);
	this->renderer = renderer;

	SDL_QueryTexture(texture, NULL, NULL, &width, &height);

	//size of one sprite in pixels
	clip.w = 10;// spritesheet_image->w / col;
	clip.h = 10;//spritesheet_image->h / row;
};

Spritesheet::~Spritesheet() { SDL_DestroyTexture(texture); };

void Spritesheet::draw_sprite(const int n,  SDL_Rect* position, SDL_Texture* texture) {
	//get coords on grid
	int x = n % height; //only need offset post wrapping
	int y = n / width; //need to know how many times is wrapped

	//get coords in pixels		
	clip.x = x * height; 
	clip.y = y * width;

	std::cout << x << " " << y << "\n";
	std::cout << height << " " << width << "\n";
	std::cout << clip.x << " " << clip.y << "\n";
	std::cout << "\n";

	SDL_RenderCopy(renderer, this->texture, NULL, NULL);
};
												 
