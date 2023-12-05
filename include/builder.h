#pragma once

class Builder {
public:
  virtual ~Builder() {}
  virtual void general_generation() = 0;
  virtual void random_walk_generation() = 0;
  virtual void add_people_to_grid() = 0;
  virtual void cleanup() = 0;
};
