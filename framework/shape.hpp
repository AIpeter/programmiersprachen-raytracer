#ifndef BUW_SHAPE_HPP
#define BUW_SHAPE_HPP

#include "color.hpp"
#include <string>

class Shape
{
  public:
    Shape():
      name_{},
      color_{0.0, 0.0, 0.0} {};

    Shape(std::string const& name):
      name_{name},
      color_{0.0, 0.0, 0.0} {};

    Shape(Color const& color):
      name_{},
      color_{color} {};

    Shape(std::string const& name, Color const& color):
      name_{name},
      color_{color} {};

    virtual std::string name() const {return name_;}
    virtual Color color() const {return color_;}
    virtual float area() const = 0; // pure virtual
    virtual float volume() const = 0; // pure virual

    //virtual std::ostream& print(std::ostream& os) const;

  protected:
    std::string name_;
    Color color_;

};

//std::ostream& operator<<(std::ostream& os, Shape const& s);

#endif // BUW_SHAPE_HPP