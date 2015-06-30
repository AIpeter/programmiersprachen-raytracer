#include "shape.hpp"

Shape::Shape(): // default constructor
      name_{},
      color_{0.0, 0.0, 0.0}
      {std::cout <<
        "Shape constructed."
            << std::endl;}

Shape::Shape(std::string const& name):
      name_{name},
      color_{0.0, 0.0, 0.0}
      {std::cout <<
        "Shape constructed."
            << std::endl;}

Shape::Shape(Color const& color):
      name_{},
      color_{color}
      {std::cout <<
        "Shape constructed."
            << std::endl;}

Shape::Shape(std::string const& name, Color const& color):
      name_{name},
      color_{color}
      {std::cout <<
        "Shape constructed."
            << std::endl;}

Shape::~Shape() //destructor
{
    std::cout <<
        "Shape destroyed."
            << std::endl;
}

std::string const& Shape::name() const {return name_;}
Color const& Shape::color() const {return color_;}

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