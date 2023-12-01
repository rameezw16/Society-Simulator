#pragma once

class Builder {
public:
  virtual ~Builder() {}
  virtual void general_generation() = 0;
  virtual void random_walk_generation() = 0;
  virtual void cleanup() = 0;
};
