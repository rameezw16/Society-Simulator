#pragma once
#include <vector>
#include <numeric>
#include <random>
#include <algorithm>
#include <math.h>
#include <SDL2/SDL.h>

struct vector2 {
	float x, y;
};


//This is adapted from https://en.wikipedia.org/wiki/Perlin_noise
class Perlin {
 public:
	//constructors
	Perlin(unsigned int seed = 1985); //seed perlin noise

	//get noise value

	void add_octave(Uint32* Pixels, const int win_width, const int win_height, const double freq, const double depth) const;

 private:
	std::vector<int> permutation;
	int block_noise(const int x, const int y) const;
	double lerp(const double x, const double y, const double m) const ;
	double smooth_lerp(const double x, const double y, double m) const;
	double noise_2d(const double x, const double y) const;
	double perlin_2d(const double x, const double y, const double freq, const double depth) const; //try to step through time

	
	
	std::mt19937 mt{}; //mersenne twister
	int seed;

};
