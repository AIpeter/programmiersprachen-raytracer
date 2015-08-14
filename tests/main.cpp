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
/*
TEST_CASE("streamoperator class Material", "[operator<<]")
{
  Material mat1{"Material_1", {1,1,1}, {0,0,0}, {1,0,1}, 1.5};
  std::cout<<mat1<<std::endl;
}*/

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
    std::cout << *i << "\n";
  }
  delete scene;
}

TEST_CASE("jetzt wird's ernst", "[renderer]") {
  Scene* scene = loadSDF("sdfdatei.sdf");
  scene->render.render(scene->shapes);
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

int main(int argc, char *argv[])
{
  return Catch::Session().run(argc, argv);
}
