#include "../include/perlin.h"
#include <random>

Perlin Perlin::set_window(SDL_Window* win) {
	this->window = win;
	return *this;
};

Perlin Perlin::set_renderer(SDL_Renderer* renderer) {
	this->renderer = renderer;
	return *this;
};

Perlin Perlin::set_texture(SDL_Texture* texture) {
	this->texture = texture;
	return *this;
};

Perlin Perlin::set_grid(Uint32* Pixels) {
	this->Pixels = Pixels;
	return *this;
};



Perlin::Perlin(unsigned int seed) {
	permutation.resize(256);
	std::iota(permutation.begin(),permutation.end(),0); //fill 0 to 255
	this->seed = seed;
	this->mt.seed(this->seed); //reseed seed
	std::shuffle(permutation.begin(), permutation.end(),this->mt);
	//permutation.insert(permutation.end(), permutation.begin(), permutation.end());
	this->seed = seed;
};

int Perlin::block_noise(const int x, const int y) const {
	int yindex = (y + this->seed) % 256;
	if (yindex < 0) yindex += 256; //basically forcing positive

	int xindex = (this->permutation[yindex] + x) % 256;
	if (xindex < 0) xindex += 256;

	const int result = this->permutation[xindex];
	return result;
};

double Perlin::lerp(const double x, const double y, const double m) const {
	return x + m * (y-x);
};

double Perlin::smooth_lerp(const double x, const double y, const double m) const {
	return lerp(x, y, m * m * ( 3-2 * m) ); // 3m^2 - 2m^3 is used as gradient
};

double Perlin::noise_2d(const double x, const double y) const {
	const int x_int = floor(x);
	const int y_int = floor(y);
	const double x_frac = x - x_int;
	const double y_frac = y - y_int;

	const int s = block_noise(x_int, y_int);
	const int t = block_noise(x_int+1, y_int);
	const int u = block_noise(x_int, y_int+1);
	const int v = block_noise(x_int+1, y_int+1);


	const double low = smooth_lerp(s, t, x_frac);
	const double high = smooth_lerp(u, v, x_frac);
	const double result = smooth_lerp(low, high, y_frac);
	return result;
};


double Perlin::perlin_2d(const double x, const double y, const double freq, const double depth) const {
	double xa = x * freq;
	double ya = y * freq;
	double amp = 1.0;
	double fin = 0;
	double div = 0.0;

	for (int i = 0; i < depth; i++) {
		div += 256*amp;
		fin += noise_2d(xa,ya) * amp;
		amp /= 2;
		xa*=2;
		ya*=2;
	};
	return fin/div;
};

void Perlin::add_octave(const double freq, const double depth) const {
	int win_height, win_width;
	SDL_GetWindowSize(window,&win_height,&win_width);
	int xOrg = 100;
	int yOrg = xOrg;
	const int scale = 10;
	SDL_PixelFormat *pixFormat = SDL_AllocFormat(SDL_PIXELFORMAT_RGBA8888);
	for (int y = 0; y < win_height; y++) {
		for (int x = 0; x < win_width; x++) {
			float xCoord = xOrg + x / ((float)win_width) * scale; // coarseness
			float yCoord = yOrg + y / ((float)win_height) * scale;
			float perlin = perlin_2d(yCoord, xCoord, freq, depth);
			Uint8 color = 255 * perlin;
			Pixels[y * win_width + x] += perlin;
					SDL_MapRGBA(pixFormat, color, color, color, 255); // grayscale
		};
	};
};




																								


