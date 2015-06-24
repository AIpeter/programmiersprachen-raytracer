#include "shape.hpp"

Shape::Shape():
      name_{},
      color_{0.0, 0.0, 0.0} {};

Shape::Shape(std::string const& name):
      name_{name},
      color_{0.0, 0.0, 0.0} {};

Shape::Shape(Color const& color):
      name_{},
      color_{color} {};

Shape::Shape(std::string const& name, Color const& color):
      name_{name},
      color_{color} {};

std::string Shape::name() const {return name_;}
Color Shape::color() const {return color_;}

std::ostream& Shape::print(std::ostream& os) const
    {
      os << name_ << ", Color: " << color_ << "\n";
      return os;
    }

std::ostream& operator<<(std::ostream& os, Shape const& s)
{
  s.print(os);
  return os;
}