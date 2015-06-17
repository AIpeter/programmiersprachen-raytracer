#ifndef BUW_SPHERE_HPP
#define BUW_SPHERE_HPP

#include <glm/vec3.hpp>
#include "shape.hpp"

class Sphere: public Shape
{
  public:
    Sphere();
    Sphere(std::string name);
    Sphere(Color color);
    Sphere(std::string name, Color color);
    Sphere(glm::vec3 const& center, float radius);
    Sphere(glm::vec3 const& center, float radius, std::string name);
    Sphere(glm::vec3 const& center, float radius, Color color);
    Sphere(glm::vec3 const& center, float radius,
           std::string name, Color color);

    /*virtual*/ float area() const;
    /*virtual*/ float volume() const;
    glm::vec3 center() const;
    float radius() const;

  private:
    glm::vec3 center_;
    float radius_;
    std::string name_;
    Color color_;
};

#endif // BUW_SPHERE_HPP