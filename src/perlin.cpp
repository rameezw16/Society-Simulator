#include "../include/perlin.h"
#include <random>

Perlin::Perlin(unsigned int seed) {
  permutation.resize(256);
  std::iota(permutation.begin(), permutation.end(), 0); // fill 0 to 255
  this->seed = seed;
  this->mt.seed(this->seed); // reseed seed
  std::shuffle(permutation.begin(), permutation.end(), this->mt);
  // permutation.insert(permutation.end(), permutation.begin(),
  // permutation.end());
  this->seed = seed;
};

int Perlin::block_noise(const int x, const int y) const {
  int yindex = (y + this->seed) % 256;
  if (yindex < 0)
    yindex += 256; // basically forcing positive

  int xindex = (this->permutation[yindex] + x) % 256;
  if (xindex < 0)
    xindex += 256;

  const int result = this->permutation[xindex];
  return result;
};

double Perlin::lerp(const double x, const double y, const double m) const {
  return x + m * (y - x);
};

double Perlin::smooth_lerp(const double x, const double y,
                           const double m) const {
  return lerp(x, y, m * m * (3 - 2 * m)); // 3m^2 - 2m^3 is used as gradient
};

double Perlin::noise_2d(const double x, const double y) const {
  const int x_int = floor(x);
  const int y_int = floor(y);
  const double x_frac = x - x_int;
  const double y_frac = y - y_int;

  const int s = block_noise(x_int, y_int);
  const int t = block_noise(x_int + 1, y_int);
  const int u = block_noise(x_int, y_int + 1);
  const int v = block_noise(x_int + 1, y_int + 1);

  const double low = smooth_lerp(s, t, x_frac);
  const double high = smooth_lerp(u, v, x_frac);
  const double result = smooth_lerp(low, high, y_frac);
  return result;
};

double Perlin::perlin_2d(const double x, const double y, const double freq,
                         const double depth) const {
  double xa = x * freq;
  double ya = y * freq;
  double amp = 1.0;
  double fin = 0;
  double div = 0.0;

  for (int i = 0; i < depth; i++) {
    div += 256 * amp;
    fin += noise_2d(xa, ya) * amp;
    amp /= 2;
    xa *= 2;
    ya *= 2;
  };
  return fin / div;
};

SDL_Color pickColor(double value) {
  SDL_Color arrColors[] = {
      SDL_Color{114, 239, 247, 255}, // light blue
      SDL_Color{144, 238, 144, 255}, // green
      SDL_Color{148, 175, 194},      // light grey
  };
  int temp = (int)(value * 10) % 3; // a little bit of magic here

  return arrColors[temp];
};

void Perlin::add_octave(const double freq, const double depth) {
  int xOrg = 100000;
  int yOrg = xOrg;
  int scale = 10;
  num_octaves++;

  SDL_PixelFormat *pixFormat = SDL_AllocFormat(SDL_PIXELFORMAT_RGBA8888);
  for (int y = 0; y < SIZE; y++) {
    for (int x = 0; x < SIZE; x++) {
      float xCoord = xOrg + x / ((float)SIZE) * scale; // coarseness
      float yCoord = yOrg + y / ((float)SIZE) * scale;
      float perlin = this->perlin_2d(yCoord, xCoord, freq, depth);
      this->total_noise[x][y] += perlin; // grayscale
    };
  };
};

double Perlin::get_noise(const int x, const int y) {
  return (this->total_noise[x][y] / num_octaves);
}

void Perlin::display(Uint32 *Pixels) {
  int xOrg = 100000;
  int yOrg = xOrg;
  int scale = 10;
  SDL_PixelFormat *pixFormat = SDL_AllocFormat(SDL_PIXELFORMAT_RGBA8888);
  for (int y = 0; y < SIZE; y++) {
    for (int x = 0; x < SIZE; x++) {
      // float xCoord = xOrg + x / ((float)SIZE) * scale; // coarseness
      // float yCoord = yOrg + y / ((float)SIZE) * scale;
      float perlin = this->get_noise(x, y);
      SDL_Color color = pickColor(perlin);
      Pixels[y * SIZE + x] =
          SDL_MapRGBA(pixFormat, color.r, color.g, color.b, 255); // grayscale
    };
  };
};

// SDL_MapRGBA(pixFormat, color, color, color, 255); // grayscale
//  SDL_PixelFormat *pixFormat = SDL_AllocFormat(SDL_PIXELFORMAT_RGBA8888);
