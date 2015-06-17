#ifndef BUW_SPHERE_HPP
#define BUW_SPHERE_HPP

#include <glm/vec3.hpp>
#include "shape.hpp"

class Sphere: public Shape
{
  public:
    Sphere();
    Sphere(glm::vec3 const& center, float radius);

    /*virtual*/ float area() const;
    /*virtual*/ float volume() const;
    glm::vec3 center() const;
    float radius() const;

  private:
    glm::vec3 center_;
    float radius_;
};

#endif // BUW_SPHERE_HPP