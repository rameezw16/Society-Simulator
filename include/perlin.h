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
	double perlin_2d(const double x, const double y, const double freq, const double depth) const; //try to step through time

 private:
	std::vector<int> permutation;
	int block_noise(const int x, const int y) const;
	double lerp(const double x, const double y, const double m) const ;
	double smooth_lerp(const double x, const double y, double m) const;
	double noise_2d(const double x, const double y) const;
	
	
	std::mt19937 mt{}; //mersenne twister
	int seed;

};
