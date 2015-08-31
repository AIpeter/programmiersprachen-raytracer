#ifndef BUW_SHAPE_HPP
#define BUW_SHAPE_HPP
#define _USE_MATH_DEFINES
#define GLM_FORCE_RADIANS

#include "material.hpp"
#include "ray.hpp"
#include "hit.hpp"
#include "computearc.hpp"
#include "light.hpp"
#include <glm/glm.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtx/transform.hpp>
#include <string>
#include <iostream>

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
    virtual float volume() const = 0; // pure virtual
    virtual Hit intersect(Ray const& r, float& t) = 0; // pure virtual
    virtual std::ostream& print(std::ostream& os) const;

    Color getLight(Hit const& hit, Ray const& r, Light const& light, float shade) const;

    glm::mat4 world_transformation();
    glm::mat4 world_transformation_inv();
    void translate(glm::vec3 const& direction);
    void scale(glm::vec3 const& scale);
    void rotate(float angle, glm::vec3 const& axis);

  protected:
    std::string name_;
    Material mat_;
    glm::mat4 world_transformation_;
    glm::mat4 world_transformation_inv_;
};

std::ostream& operator<<(std::ostream& os, Shape const& s);

#endif // BUW_SHAPE_HPP