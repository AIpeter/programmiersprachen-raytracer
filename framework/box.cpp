#include "box.hpp"

Box::Box():
  min_{1},
  max_{1} {}

float Box::area() const {}
float Box::volume() const {}

float   Box::min() const {return min_;}
float   Box::max() const {return max_;}