#include "material.hpp"

Material::Material(): // default constructor
  name_{},
  ka_{0.0, 0.0, 0.0},
  kd_{0.0, 0.0, 0.0},
  ks_{0.0, 0.0, 0.0},
  m_{1} {}

Material::Material(std::string const& name, Color const& ka,
                   Color const& kd, Color const& ks, float m):
  name_{name},
  ka_{ka},
  kd_{kd},
  ks_{ks},
  m_{m} {}

std::string const& Material::name() const {return name_;}
Color const& Material::ka() const {return ka_;}
Color const& Material::kd() const {return kd_;}
Color const& Material::ks() const {return ks_;}
float Material::m() const {return m_;}

std::ostream& operator<<(std::ostream& os, Material const& mat)
{
  os<<"--------"<<"\n"<<"Material"<<"\n"<<"--------"<<"\n"
  <<"Name: "<<mat.name()<<"\n"<<"ka: "<<mat.ka()<<"kd: "
  <<mat.kd()<<"ks: "<<mat.ks()<<"m: "<<mat.m()<<"\n";
  return os;
}