#ifndef BUW_SHAPE_HPP
#define BUW_SHAPE_HPP
#define _USE_MATH_DEFINES

#include "material.hpp"
#include "ray.hpp"
#include <glm/glm.hpp>
#include <string>
#include <iostream>
#include "light.hpp"

class Shape
{
  public:
    Shape(); // default constructor
    Shape(Shape const& s);
    Shape(std::string const& name);
    Shape(std::string const& name, Material const& mat);

    std::string const& name() const; // getter
    Material const& mat() const; // getter
    virtual float area() const = 0; // pure virtual
    virtual float volume() const = 0; // pure virual
    virtual bool intersect(Ray const& r, float& t) = 0; // pure virtual
    virtual float closer_z() const = 0; // pure virtual getter
    virtual glm::vec3 const& center() const;
    virtual float radius() const;
    virtual std::ostream& print(std::ostream& os) const;

    virtual Color getLight(float & d, Ray const& r, Light const& light, float shade) const = 0; //pure virtual

    virtual void translate(glm::vec3 const& direction) = 0; // pure virtual
    virtual void scale(glm::vec3 const& scale) = 0; // pure virtual

  protected:
    std::string name_;
    Material mat_;
};

std::ostream& operator<<(std::ostream& os, Shape const& s);

#endif // BUW_SHAPE_HPP