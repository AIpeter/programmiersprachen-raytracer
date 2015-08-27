#define CATCH_CONFIG_RUNNER
#include <catch.hpp>
#include "shape.hpp"
#include "sphere.hpp"
#include "box.hpp"
#include "material.hpp"
#include "sdfloader.hpp"
#include "composite.hpp"
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtx/intersect.hpp>
#include <renderer.hpp>
/*
TEST_CASE("streamoperator class Material", "[operator<<]")
{
  Material mat1{"Material_1", {1,1,1}, {0,0,0}, {1,0,1}, 1.5};
  std::cout<<mat1<<std::endl;
}*/
/*
TEST_CASE("intersectBox", "[intersect]") {
        Material m{"Testmaterial", Color{1,0,0}, Color{0,1,0}, Color{0,0,1},
                    15};
        Ray r{{0.0, 0.0, 0.0}, {1.0, 1.0, 1.0}};
        Box b{glm::vec3{0.0, 0.0, 0.0}, glm::vec3{1.0, 1.0, 1.0}, "testbox", m};
        float t = 0;
        REQUIRE(b.intersect(r, t) == true);
}

TEST_CASE("read a file", "[file]")
{
  Scene* scene = loadSDF("sdfdatei.sdf");
  for(auto i : scene->materials)
  {
    std::cout << i.second << "\n";
  }
  for(auto i : scene->shapes) {
    std::cout << *i.second << "\n";
  }
  delete scene;
}
*/
/*
TEST_CASE("animation", "[renderer]") {
  Scene* scene = loadSDF("sdfdatei.sdf");
  int picturecount = 0;
  for (int i = 0; i <= 360; ++i)
  {
    for (auto j: scene->shapes)
    {
      j.second->rotate(1, {0,0,1});
    }
    for (int k = 0; k < 2; ++k)
    {
      std::string filename = "image" + std::to_string(picturecount) + ".ppm";
      scene->render.filename(filename);
      scene->render.render(scene->shapes, scene->lights);
      picturecount++;
    }
  }
}
*/
TEST_CASE("jetzt wird's ernst", "[renderer]") {
  Scene* scene = loadSDF("sdfdatei.sdf");
  // AA an: bool true
  // scene->render.render(scene->shapes, scene->lights, true);
  // AA aus: bool false
  scene->render.render(scene->shapes, scene->lights, false);
}
/*
TEST_CASE("composite", "[composite]") {
  Material m{"Testmaterial", Color{1,0,0}, Color{0,1,0}, Color{0,0,1}, 15};
  auto b = std::make_shared<Box>(glm::vec3{0.0, 0.0, 0.0}, glm::vec3{1.0, 1.0, 1.0}, "testbox", m);
  auto s = std::make_shared<Sphere>(glm::vec3{1.0, 1.0, 1.0}, 1, "testsphere", m);
  Composite c{b, s};
  // std::cout << c << std::endl;
  Ray r{{0.0, 0.0, 0.0}, {1.0, 1.0, 1.0}};
  float t = 0;
  REQUIRE(c.intersect(r, t) == true);
  std::cout << c.volume() << std::endl;
}
*/

/*  glm::vec3 camright{0,1,0};
  glm::vec3 camup{1,0,0};
  glm::vec3 position{0,0,0};
  glm::vec3 direction{0,0,-1};
  float width_ = 200;
  float height_ = 200;

  Ray ComputeCameraRay(int i, int j)
  {
  float norm_i = (i/width_) - 0.5;
  float norm_j = (j/height_) - 0.5;
  glm::vec3 image_point = norm_i * camright
                        + norm_j * camup
                        + position
                        + direction;
  glm::vec3 ray_dir = image_point - position;
  return Ray{position, ray_dir};
  }

TEST_CASE("computecameraray", "[computecameraray]") 
{

  std::cout << "computecameraray" << std::endl;
  Ray result = ComputeCameraRay(0, 100);
  std::cout << result.origin.x << result.origin.y << result.origin.z << std::endl;
  std::cout << result.direction.x << result.direction.y << result.direction.z << std::endl;
  
}*/

int main(int argc, char *argv[])
{
  return Catch::Session().run(argc, argv);
}
