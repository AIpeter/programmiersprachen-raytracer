#define CATCH_CONFIG_RUNNER
#include <catch.hpp>
#include "shape.hpp"
#include "sphere.hpp"
#include "box.hpp"
#include "material.hpp"
#include "sdfloader.hpp"
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtx/intersect.hpp>

TEST_CASE("streamoperator class Material", "[operator<<]")
{
  Material mat1{"Material_1", {1,1,1}, {0,0,0}, {1,0,1}, 1.5};
  std::cout<<mat1<<std::endl;
}

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
  Scene* scene = loadSDF("read_mat.sdf");
  for(auto i : scene->materials)
  {
    std::cout << i.second << "\n";
  }
  delete scene;
}


int main(int argc, char *argv[])
{
  return Catch::Session().run(argc, argv);
}
