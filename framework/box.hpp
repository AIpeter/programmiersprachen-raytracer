#ifndef BUW_BOX_HPP
#define BUW_BOX_HPP

#include <glm/vec3.hpp>
#include "shape.hpp"

class Box : public Shape
{
  public:
    Box(); // default constructor
    Box(Box const& b); // copy constructor
    Box(std::string const& name);
    Box(Color const& color);
    Box(std::string const& name, Color const& color);
    Box(glm::vec3 const& min, glm::vec3 const& max);
    Box(glm::vec3 const& min, glm::vec3 const& max,
        std::string const& name);
    Box(glm::vec3 const& min, glm::vec3 const& max,
        Color const& color);
    Box(glm::vec3 const& min, glm::vec3 const& max,
        std::string const& name, Color const& color);


    glm::vec3 min() const;
    glm::vec3 max() const;
    float area() const; // override
    float volume() const; // override
    std::ostream& print(std::ostream& os) const; // override
    //bool intersect(Ray & r) const;

  private:
    glm::vec3 min_;
    glm::vec3 max_;
};

#endif // BUW_BOX_HPP