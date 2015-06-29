#ifndef BUW_SHAPE_HPP
#define BUW_SHAPE_HPP

#include "color.hpp"
#include <string>
#include <iostream>

class Shape
{
  public:
    Shape(); // default constructor
    Shape(std::string const& name);
    Shape(Color const& color);
    Shape(std::string const& name, Color const& color);
    virtual ~Shape(); //destructor

    virtual std::string name() const; // getter
    virtual Color color() const; // getter
    virtual float area() const = 0; // pure virtual
    virtual float volume() const = 0; // pure virual

    virtual std::ostream& print(std::ostream& os) const;

  protected:
    std::string name_;
    Color color_;
};

std::ostream& operator<<(std::ostream& os, Shape const& s);

#endif // BUW_SHAPE_HPP