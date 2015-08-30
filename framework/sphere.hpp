#ifndef BUW_SPHERE_HPP
#define BUW_SPHERE_HPP

#include <glm/vec3.hpp>
#include "shape.hpp"
#include <ray.hpp>
#include <glm/glm.hpp>
#include <glm/gtx/intersect.hpp>
#include <cmath>
#include "computearc.hpp"

class Sphere : public Shape
{
  public:
    Sphere(); // default constructor
    Sphere(Sphere const& s);
    Sphere(glm::vec3 const& center, float radius,
           std::string const& name, Material const& mat);

    glm::vec3 const& center() const;
    float radius() const;
    float area() const; // override
    float volume() const; // override
    std::ostream& print(std::ostream& os) const; // override
    Hit intersect(Ray const& r, float & d);

    void translate(glm::vec3 const& direction);
    void scale(glm::vec3 const& scale);
    void rotate(float angle, glm::vec3 const& axis);

  private:
    glm::vec3 center_;
    float radius_;
};

#endif // BUW_SPHERE_HPP