#ifndef BUW_SPHERE_HPP
#define BUW_SPHERE_HPP

#include <glm/vec3.hpp>
#include "shape.hpp"

class Sphere : public Shape
{
  public:
    Sphere();
    Sphere(std::string const& name);
    Sphere(Color const& color);
    Sphere(std::string const& name, Color const& color);
    Sphere(glm::vec3 const& center, float radius);
    Sphere(glm::vec3 const& center, float radius,
           std::string const& name);
    Sphere(glm::vec3 const& center, float radius,
           Color const& color);
    Sphere(glm::vec3 const& center, float radius,
           std::string const& name, Color const& color);


    glm::vec3 center() const;
    float radius() const;
    /*virtual*/ float area() const;
    /*virtual*/ float volume() const;

  private:
    glm::vec3 center_;
    float radius_;
};

#endif // BUW_SPHERE_HPP