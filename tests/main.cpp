#define CATCH_CONFIG_RUNNER
#include <catch.hpp>
#include "shape.hpp"
#include "sphere.hpp"
#include "box.hpp"

TEST_CASE("default constructor of sphere", "[Sphere()]")
{
  Sphere s1{};
  glm::vec3 cen{0, 0, 0};
  REQUIRE(s1.radius() == Approx(1.0));
  REQUIRE(s1.center() == cen);
}

TEST_CASE("calculate area and volume of sphere", "[area(), volume()]")
{
  Sphere s1{};
  REQUIRE(s1.area() == Approx(12.5664));
  REQUIRE(s1.volume() == Approx(4.18879));
}

TEST_CASE("default constructor of box", "[Box()]")
{
  Box b1{};
  glm::vec3 min{0, 0, 0};
  glm::vec3 max{1, 1, 1};
  REQUIRE(b1.min() == min);
  REQUIRE(b1.max() == max);
}


int main(int argc, char *argv[])
{
  return Catch::Session().run(argc, argv);
}
