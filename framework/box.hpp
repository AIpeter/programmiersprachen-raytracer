#ifndef BUW_BOX_HPP
#define BUW_BOX_HPP

#include <glm/vec3.hpp>

class Box: public Shape
{
  public:
    /*virtual*/ float area() const;
    /*virtual*/ float volume() const;

  private:
    glm::vec3 min_;
    glm::vec3 max_;
};