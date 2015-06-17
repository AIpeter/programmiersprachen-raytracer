#include "box.hpp"

Box::Box():
  min_{1},
  max_{1} {}

float Box::area() const {}
float Box::volume() const {return 2*min_+2*max_;}

float   Rectangle::min() const {return min_;}
float   Rectangle::max() const {return max_;}