#ifndef BUW_BOX_HPP
#define BUW_BOX_HPP

#include <glm/vec3.hpp>
#include "shape.hpp"
#include "computearc.hpp"

class Box : public Shape
{
  public:
    Box(); // default constructor
    Box(Box const& b);
    Box(glm::vec3 const& min, glm::vec3 const& max,
        std::string const& name, Material const& mat);


    glm::vec3 min() const;
    glm::vec3 max() const;
    float area() const; // override
    float volume() const; // override
    std::ostream& print(std::ostream& os) const; // override
    bool intersect(Ray const& r, float& t);
    float closer_z() const; // override

    Color getLight(float & d, Ray const& r, Light const& light, float shade) const; // override

    void translate(glm::vec3 const& direction);
    void scale(glm::vec3 const& scale);
    void rotate(float angle, glm::vec3 const& axis);

  private:
    glm::vec3 min_;
    glm::vec3 max_;
};

#endif // BUW_BOX_HPP