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

void Spritesheet::draw_sprite(const int x, const int y, SDL_Rect* position, SDL_Texture* texture) {
	//get coords in pixels		
	clip.x = x * 10; 
	clip.y = y * 10;

	std::cout << x << " " << y << "\n";
	std::cout << width << " " << height << "\n";
	std::cout << clip.x << " " << clip.y << "\n";
	std::cout << "\n";

	clip.w = 10;
	clip.h = 10;

	SDL_RenderCopy(renderer, this->texture, &clip, position);
};
												 
