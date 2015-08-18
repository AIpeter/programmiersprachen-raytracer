#include "shape.hpp"

Shape::Shape(): // default constructor
      name_{},
      mat_{}
      {}

Shape::Shape(Shape const& s):
      name_{s.name()},
      mat_{s.mat()}
      {}

Shape::Shape(std::string const& name):
      name_{name},
      mat_{}
      {}

Shape::Shape(std::string const& name, Material const& mat):
      name_{name},
      mat_{mat}
      {}
      

std::string const& Shape::name() const {return name_;}
Material const& Shape::mat() const {return mat_;}

std::ostream& Shape::print(std::ostream& os) const
    {
      os<<"Name: "<<name_<<"\n"<<"Material: "<<mat_<<"\n";
      return os;
    }

std::ostream& operator<<(std::ostream& os, Shape const& s)
{
  s.print(os);
  return os;
}

glm::vec3 const& Shape::center() const
{
  return glm::vec3{0,0,0};
}

float Shape::radius() const
{
  return 0;
}