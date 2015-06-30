#ifndef BUW_MATERIAL_HPP
#define BUW_MATERIAL_HPP

#include "color.hpp"
#include <string>
#include <iostream>

class Material
{
  public:
    Material(); // default constructor
    Material(std::string const& name, Color const& ka,
             Color const& kd, Color const& ks, float m);
    std::string const& name() const;
    Color const& ka() const;
    Color const& kd() const;
    Color const& ks() const;
    float m() const;

  private:
    std::string name_;
    Color ka_;
    Color kd_;
    Color ks_;
    float m_;
};

std::ostream& operator<<(std::ostream& os, Material const& mat);

#endif // BUW_MATERIAL_HPP