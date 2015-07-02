#ifndef BUW_SCENE_HPP
#define BUW_SCENE_HPP

#include <vector>
#include "sphere.hpp"
#include "box.hpp"
#include "material.hpp"
//#include "light.hpp"
//#include "camera.hpp"

struct Scene
{
  std::vector<Sphere> spheres;
  std::vector<Box> boxes;
  std::vector<Material> materials;
  //std::vector<Light> lights;
  //Camera camera;
};


#endif // BUW_SCENE_HPP