#define CATCH_CONFIG_RUNNER
#include <catch.hpp>
#include "shape.hpp"
#include "sphere.hpp"
#include "box.hpp"

TEST_CASE("default constructor of sphere", "[Sphere()]")
{
  Sphere s1{};
  glm::vec3 cen{0, 0, 0};
  REQUIRE(s1.center() == cen);
  REQUIRE(s1.radius() == Approx(1.0));
}

TEST_CASE("user-defined constructor of sphere", "[Sphere()]")
{
  Sphere s1{{1, 1, 1}, 5};
  glm::vec3 cen{1, 1, 1};
  REQUIRE(s1.center() == cen);
  REQUIRE(s1.radius() == Approx(5.0));
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

TEST_CASE("user-defined constructor of box", "[Box()]")
{
  Box b1{{2, 2, 3}, {1, 2, 4}};
  glm::vec3 min{2, 2, 3};
  glm::vec3 max{1, 2, 4};
  REQUIRE(b1.min() == min);
  REQUIRE(b1.max() == max);
}


int main(int argc, char *argv[])
{
  return Catch::Session().run(argc, argv);
}
