#ifndef BUW_SHAPE_HPP
#define BUW_SHAPE_HPP

#include "color.hpp"
#include <string>

class Shape
{
  public:
    Shape():
      name_{},
      color_{0.0, 0.0, 0.0} {}

    virtual float area() const = 0; // pure virtual
    virtual float volume() const = 0; // pure virual

  private:
    std::string name_;
    Color color_;

};

#endif // BUW_SHAPE_HPP