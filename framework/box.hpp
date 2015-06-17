#ifndef BUW_BOX_HPP
#define BUW_BOX_HPP

#include <glm/vec3.hpp>
#include "shape.hpp"

class Box: public Shape
{
  public:
    Box();
    Box(glm::ve3 const& min, glm::ve3 const& max);

    /*virtual*/ float area() const;
    /*virtual*/ float volume() const;
    glm::vec3 min() const;
    glm::vec3 max() const;

  private:
    glm::vec3 min_;
    glm::vec3 max_;
};

#endif // BUW_BOX_HPP