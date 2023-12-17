#pragma once
#include <SDL2/SDL.h>
#include <string>
// #include "./spritesheet.hpp"
#define SIZE_OCCUPIED 10

// This class has grown a little out of control, however it is the common
// interface for all entities (terrain, features, agents). Notice the virtual
// getters and setters, these are important for polymorphic accessing. While the
// get_type() method does tend to break best-practices for doing polymorphism,
// it is generally there for legacy purposes, and our code does not depend
// heavily on it.

enum Seasons { Harvest, Drought, Famine, Monsoon };

class Entity {
public:
  Entity(const int pos_x, const int pos_y, const int spritesheet_pos_x,
         const int spritesheet_pos_y);

  virtual ~Entity();

  virtual bool get_walkable() const = 0;
  virtual std::string get_type() const = 0;

  void set_position(const int pos_x, const int pos_y);

  void set_sprite(const int spritesheet_pos_x, const int spritesheet_pos_y);

  virtual int get_spritesheet_pos_x() const;
  virtual int get_spritesheet_pos_y() const;

  static void step_season();
  static Seasons season;
  static int timer;
  static int year;

  virtual void step() = 0;
  virtual void consume() = 0;
  virtual void decay();
  virtual void grow_back() = 0;

protected:
  bool walkable = true;
  std::string type = "entity";
  int pos_x;
  int pos_y;
  int spritesheet_pos_x;
  int spritesheet_pos_y;
};
