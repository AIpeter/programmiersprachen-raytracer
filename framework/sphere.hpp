#ifndef BUW_SPHERE_HPP
#define BUW_SPHERE_HPP

#include <glm/vec3.hpp>

class Sphere: public Shape
{
  public:
    /*virtual*/ float area() const;
    /*virtual*/ float volume() const;

  private:
    glm::vec3 center_;
    float radius_;
};