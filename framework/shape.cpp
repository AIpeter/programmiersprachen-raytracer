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

Color Shape::getLight(Hit const& hit, Ray const& r, Light const& light, float shade) const
{
  if(shade == 0) // Schatten
  {
    Color licht = (light.getla()* mat_.ka());
    return licht;
  }
  else
  {
    float diffuseCos = computeDiffuseArc(hit, light);
    // std::cout << "diffuseCos: " << diffuseCos << "\n";
    float specularCos = computeSpecularArc(hit, r, light);
    // std::cout << "specularCos: " << specularCos << std::endl;
    Color licht = (light.getld() * mat_.kd() * diffuseCos)
                  + (light.getld() * mat_.ks() * (pow(specularCos, mat_.m()))) 
                  + (light.getla()* mat_.ka());
    return licht;
  }
}

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