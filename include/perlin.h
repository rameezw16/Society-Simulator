#pragma once
#include <vector>
#include <numeric>
#include <random>
#include <algorithm>
#include <math.h>
#include <SDL2/SDL.h>

class Perlin {
 public:
	//constructor
	Perlin(unsigned int seed = 1985); //seed perlin noise

	//setters
	Perlin set_window(SDL_Window* win);
	Perlin set_renderer(SDL_Renderer*  renderer);
	Perlin set_texture(SDL_Texture* texture);
	Perlin set_grid(Uint32* Pixels);

	//get noise value
	double perlin_2d(const double x, const double y, const double freq, const double depth) const; 
	void add_octave(const double freq, const double depth) const;

 private:
	//RNG 
	std::vector<int> permutation;
	std::mt19937 mt{}; //mersenne twister
	int seed;


	int block_noise(const int x, const int y) const;
	double lerp(const double x, const double y, const double m) const ;
	double smooth_lerp(const double x, const double y, double m) const;
	double noise_2d(const double x, const double y) const;

	
	//Displaying
	Uint32* Pixels;
	SDL_Renderer* renderer;
	SDL_Window* window;
	SDL_Texture* texture;

};
