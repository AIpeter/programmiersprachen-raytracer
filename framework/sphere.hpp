#ifndef BUW_SPHERE_HPP
#define BUW_SPHERE_HPP

#include <glm/vec3.hpp>
#include "shape.hpp"
#include <ray.hpp>
#include <glm/glm.hpp>
#include <glm/gtx/intersect.hpp>

class Sphere : public Shape
{
  public:
    Sphere(); // default constructor
    Sphere(Sphere const& s); // copy constructor
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
    ~Sphere(); //destructor


    glm::vec3 center() const;
    float radius() const;
    float area() const; // override
    float volume() const; // override
    std::ostream& print(std::ostream& os) const; // override
    bool intersect(Ray & r) const;

  private:
    glm::vec3 center_;
    float radius_;
};

#endif // BUW_SPHERE_HPP