#pragma once
#include<SDL2/SDL.h>
#include "./spritesheet.hpp"
class Entity {
 public:
	Entity(const int spritesheet_pos_x, const int spritesheet_pos_y, const int pos_x, const int pos_y);
	virtual ~Entity();

	void set_position(const int pos_x, const int pos_y); //set top left corner of the sprite
	virtual void draw(Spritesheet* sp, SDL_Texture* texture) = 0;


 protected:
	int pos_x;
	int pos_y;
	int spritesheet_pos_x;
	int spritesheet_pos_y;
};


class Terrain : public Entity {
public:
	Terrain(const int spritesheet_pos_x, const int spritesheet_pos_y, const int pos_x, const int pos_y);
	virtual ~Terrain();
	void draw(Spritesheet* sp, SDL_Texture* texture) override;
protected:
	//Randomly generate these guys
	float temp; 
	float humidity;
	float evil;
	float fauna;

	bool walkable;
};

class Water : public Terrain { //making a class so we can extend functionality later
public:
	Water(const int spritesheet_pos_x, const int spritesheet_pos_y, const int pos_x, const int pos_y);
	~Water();
};

class Dirt : public Terrain { //making a class so we can extend functionality later
public:
	Dirt(const int spritesheet_pos_x, const int spritesheet_pos_y, const int pos_x, const int pos_y);
	~Dirt();
};


class Building : public Terrain {
public:
	Building(const int spritesheet_pos_x, const int spritesheet_pos_y, const int size_x, const int size_y, const int pos_x, const int pos_y);
	~Building();

	void draw(Spritesheet* sp, SDL_Texture* texture) override;

private:
	int size_x, size_y;
};





