#ifndef BUW_TRIANGLE_HPP
#define BUW_TRIANGLE_HPP

#include <glm/vec3.hpp>
#include "shape.hpp"
#include <ray.hpp>
#include <glm/glm.hpp>
#include <glm/gtx/intersect.hpp>
#include <cmath>
#include "computearc.hpp"

class Triangle : public Shape
{
  public:
    Triangle(); // default constructor
    Triangle(Triangle const& triangle);
    Triangle(glm::vec3 const& left, glm::vec3 const& right, glm::vec3 const& top,
           std::string const& name, Material const& mat);

    glm::vec3 const& getleft() const;
    glm::vec3 const& getright() const;
    glm::vec3 const& gettop() const;
    float area() const; // override
    float volume() const; // override
    std::ostream& print(std::ostream& os) const; // override
    bool intersect(Ray const& r, float & d);
    float closer_z() const; // override

    Color getLight(float & d, Ray const& r, Light const& light, float shade) const; // override

    void translate(glm::vec3 const& direction);
    void scale(glm::vec3 const& scale);
    void rotate(float angle, glm::vec3 const& axis);

  private:
    glm::vec3 left_;
    glm::vec3 right_;
    glm::vec3 top_;
};

#endif // BUW_TRIANGLE_HPP