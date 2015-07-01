#ifndef BUW_SHAPE_HPP
#define BUW_SHAPE_HPP

#include "material.hpp"
#include "ray.hpp"
#include <glm/glm.hpp>
#include <string>
#include <iostream>

class Shape
{
  public:
    Shape(); // default constructor
    Shape(std::string const& name);
    Shape(Material const& mat);
    Shape(std::string const& name, Material const& mat);

    virtual std::string const& name() const; // getter
    virtual Material const& mat() const; // getter
    virtual float area() const = 0; // pure virtual
    virtual float volume() const = 0; // pure virual
    virtual bool intersect(Ray const& r, float& t) = 0; // pure virtual

    virtual std::ostream& print(std::ostream& os) const;

  protected:
    std::string name_;
    Material mat_;
};

std::ostream& operator<<(std::ostream& os, Shape const& s);

#endif // BUW_SHAPE_HPP