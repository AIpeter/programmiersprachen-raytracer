#include "shape.hpp"

Shape::Shape(): // default constructor
      name_{},
      mat_{},
      world_transformation_{},
      world_transformation_inv_{}
      {
        // matrizenname[Spalte][Zeile]
        // 1 0 0 0
        // 0 1 0 0
        // 0 0 1 0
        // 0 0 0 1
        world_transformation_[0][0] = 1;
        world_transformation_[1][0] = 0;
        world_transformation_[2][0] = 0;
        world_transformation_[3][0] = 0;

        world_transformation_[0][1] = 0;
        world_transformation_[1][1] = 1;
        world_transformation_[2][1] = 0;
        world_transformation_[3][1] = 0;

        world_transformation_[0][2] = 0;
        world_transformation_[1][2] = 0;
        world_transformation_[2][2] = 1;
        world_transformation_[3][2] = 0;

        world_transformation_[0][3] = 0;
        world_transformation_[1][3] = 0;
        world_transformation_[2][3] = 0;
        world_transformation_[3][3] = 1;

        world_transformation_inv_ = glm::inverse(world_transformation_);
      }

Shape::Shape(Shape const& s):
      name_{s.name()},
      mat_{s.mat()},
      world_transformation_{},
      world_transformation_inv_{}
      {
        // matrizenname[Spalte][Zeile]
        // 1 0 0 0
        // 0 1 0 0
        // 0 0 1 0
        // 0 0 0 1
        world_transformation_[0][0] = 1;
        world_transformation_[1][0] = 0;
        world_transformation_[2][0] = 0;
        world_transformation_[3][0] = 0;

        world_transformation_[0][1] = 0;
        world_transformation_[1][1] = 1;
        world_transformation_[2][1] = 0;
        world_transformation_[3][1] = 0;

        world_transformation_[0][2] = 0;
        world_transformation_[1][2] = 0;
        world_transformation_[2][2] = 1;
        world_transformation_[3][2] = 0;

        world_transformation_[0][3] = 0;
        world_transformation_[1][3] = 0;
        world_transformation_[2][3] = 0;
        world_transformation_[3][3] = 1;

        world_transformation_inv_ = glm::inverse(world_transformation_);
      }

Shape::Shape(std::string const& name):
      name_{name},
      mat_{},
      world_transformation_{},
      world_transformation_inv_{}
      {
        // matrizenname[Spalte][Zeile]
        // 1 0 0 0
        // 0 1 0 0
        // 0 0 1 0
        // 0 0 0 1
        world_transformation_[0][0] = 1;
        world_transformation_[1][0] = 0;
        world_transformation_[2][0] = 0;
        world_transformation_[3][0] = 0;

        world_transformation_[0][1] = 0;
        world_transformation_[1][1] = 1;
        world_transformation_[2][1] = 0;
        world_transformation_[3][1] = 0;

        world_transformation_[0][2] = 0;
        world_transformation_[1][2] = 0;
        world_transformation_[2][2] = 1;
        world_transformation_[3][2] = 0;

        world_transformation_[0][3] = 0;
        world_transformation_[1][3] = 0;
        world_transformation_[2][3] = 0;
        world_transformation_[3][3] = 1;

        world_transformation_inv_ = glm::inverse(world_transformation_);
      }

Shape::Shape(std::string const& name, Material const& mat):
      name_{name},
      mat_{mat},
      world_transformation_{},
      world_transformation_inv_{}
      {
        // matrizenname[Spalte][Zeile]
        // 1 0 0 0
        // 0 1 0 0
        // 0 0 1 0
        // 0 0 0 1
        world_transformation_[0][0] = 1;
        world_transformation_[1][0] = 0;
        world_transformation_[2][0] = 0;
        world_transformation_[3][0] = 0;

        world_transformation_[0][1] = 0;
        world_transformation_[1][1] = 1;
        world_transformation_[2][1] = 0;
        world_transformation_[3][1] = 0;

        world_transformation_[0][2] = 0;
        world_transformation_[1][2] = 0;
        world_transformation_[2][2] = 1;
        world_transformation_[3][2] = 0;

        world_transformation_[0][3] = 0;
        world_transformation_[1][3] = 0;
        world_transformation_[2][3] = 0;
        world_transformation_[3][3] = 1;

        world_transformation_inv_ = glm::inverse(world_transformation_);
      }
      

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
  
  /*
  Color licht{0, 0, 0};
  licht.r = hit.normal.x;
  licht.g = hit.normal.y;
  licht.b = hit.normal.z;
  return licht;
  */
  
}

glm::mat4 Shape::world_transformation() {return world_transformation_;}
glm::mat4 Shape::world_transformation_inv() {return world_transformation_inv_;}

void Shape::translate(glm::vec3 const& direction)
{
  world_transformation_ += glm::translate(direction);
  world_transformation_inv_ = glm::inverse(world_transformation_);
}

void Shape::scale(glm::vec3 const& scale)
{
  world_transformation_ *= glm::scale(scale);
  world_transformation_inv_ = glm::inverse(world_transformation_);
}

void Shape::rotate(float angle, glm::vec3 const& axis)
{
  // float old_value_11 = world_transformation_[1][1];
  //float old_value_22 = world_transformation_[2][2];
  world_transformation_ *= glm::rotate(angle, axis);
  std::cout << "world_transformation_: " << glm::to_string(world_transformation_) << "\n";
  // world_transformation_[1][1] -= old_value_11;
  // world_transformation_[2][2] -= old_value_22;
  world_transformation_inv_ = glm::inverse(world_transformation_);
  std::cout << "world_transformation_inv_: " << glm::to_string(world_transformation_inv_) << std::endl;
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