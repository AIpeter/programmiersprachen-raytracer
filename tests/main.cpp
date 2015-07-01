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

/*
TEST_CASE("default constructor of sphere", "[Sphere]")
{
  Sphere s1{};
  glm::vec3 cen{0, 0, 0};
  REQUIRE(s1.center() == cen);
  REQUIRE(s1.radius() == Approx(1.0));
}

TEST_CASE("copy constructor of sphere", "[Sphere]")
{
  // zu übergeben: center, radius, name, color
  Sphere s1{glm::vec3{1, 2, 3}, 3, "Sphere1", Color{1, 1, 1}};
  Sphere s2(s1);
  glm::vec3 cen{1, 2, 3};
  Color c{1, 1, 1};
  REQUIRE(s2.center() == cen);
  REQUIRE(s2.radius() == Approx(3));
  REQUIRE(s2.name() == "Sphere1");
  REQUIRE(s2.color().r == c.r);
  REQUIRE(s2.color().g == c.g);
  REQUIRE(s2.color().b == c.b);
}

TEST_CASE("user-defined constructor of sphere", "[Sphere]")
{
  Sphere s1{{1, 1, 1}, 5};
  glm::vec3 cen{1, 1, 1};
  REQUIRE(s1.center() == cen);
  REQUIRE(s1.radius() == Approx(5.0));
}

TEST_CASE("calculate area and volume of sphere", "[area, volume]")
{
  Sphere s1{};
  REQUIRE(s1.area() == Approx(12.5664));
  REQUIRE(s1.volume() == Approx(4.18879));
}

TEST_CASE("default constructor of box", "[Box]")
{
  Box b1{};
  glm::vec3 min{0, 0, 0};
  glm::vec3 max{1, 1, 1};
  REQUIRE(b1.min() == min);
  REQUIRE(b1.max() == max);
}

TEST_CASE("copy constructor of box", "[Box]")
{
  // zu übergeben: min, max, name, color
  Box b1{glm::vec3{1, 2, 3}, glm::vec3{2, 3, 4},
        "Box1", Color{1, 1, 1}};
  Box b2(b1);
  glm::vec3 min{1, 2, 3};
  glm::vec3 max{2, 3, 4};
  Color c{1, 1, 1};
  REQUIRE(b2.min() == min);
  REQUIRE(b2.max() == max);
  REQUIRE(b2.name() == "Box1");
  REQUIRE(b2.color().r == c.r);
  REQUIRE(b2.color().g == c.g);
  REQUIRE(b2.color().b == c.b);
}

TEST_CASE("user-defined constructor of box", "[Box]")
{
  Box b1{glm::vec3{2, 2, 3}, glm::vec3{1, 2, 4}};
  glm::vec3 min{2, 2, 3};
  glm::vec3 max{1, 2, 4};
  REQUIRE(b1.min() == min);
  REQUIRE(b1.max() == max);
}

TEST_CASE("print name and color of Sphere", "[print]")
{
  Sphere s1{"Sphere1", Color{1, 1, 1}};
  std::cout<<"Name und Color der Sphere: "<<s1<<"\n";
}

TEST_CASE("print member variables of Box", "[print]")
{
  Box b1{glm::vec3{1, 2, 3}, glm::vec3{2, 3, 4}, "Box1", Color{1, 0, 1}};
  std::cout<<"Member Variablen der Box: "<<b1<<"\n";
}

TEST_CASE("intersectRaySphere", "[intersect]")
{
  // Ray
  glm::vec3 ray_origin(0.0, 0.0, 0.0);
  // ray direction has to be normalized!
  glm::vec3 ray_direction(0.0, 0.0, 1.0);

  // Sphere
  glm::vec3 sphere_center(0.0, 0.0, 5.0);
  float sphere_radius(1.0);

  float distance(0.0);
  auto result = glm::intersectRaySphere(ray_origin,
    ray_direction, sphere_center, sphere_radius,
    distance);
  REQUIRE(distance == Approx(4.0f));
}

TEST_CASE("intersectRaySphere II", "[intersectRaySphere]")
{
  Ray r1{{0.0,0.0,0.0}, {0.0,0.0,1.0}};
  Sphere s1{glm::vec3{0.0,0.0,5.0}, 1.0};
  REQUIRE(s1.intersect(r1) == true);
}

TEST_CASE("static and dynamic variables", "[static and dynamic]")
{
  std::cout<<std::endl<<"Hier gehts los!"<<std::endl<<std::endl;
  Color red(255, 0, 0);
  glm::vec3 position(0.0);
  std::shared_ptr<Sphere> s1 =
  std::make_shared<Sphere>(position, 1.2,"sphere0", red);
  std::shared_ptr<Shape> s2 =
  std::make_shared<Sphere>(position, 1.2, "sphere1", red);
  s1-> print(std::cout);
  s2-> print(std::cout);
}

TEST_CASE("destructor", "[delete]")
{
  std::cout<<std::endl<<"Hier gehts wieder los!"<<std::endl<<std::endl;
  Color red(255, 0, 0);
  glm::vec3 position(0.0);

  Sphere* s1 = new Sphere(position, 1.2, "sphere0", red);
  Shape* s2 = new Sphere(position, 1.2, "sphere1", red);

  s1->print(std::cout);
  s2->print(std::cout);

  delete s1;
  delete s2;
}
*/

TEST_CASE("streamoperator class Material", "[operator<<]")
{
  Material mat1{"Material_1", {1,1,1}, {0,0,0}, {1,0,1}, 1.5};
  std::cout<<mat1<<std::endl;
}

TEST_CASE("intersect Ray and Box", "[intersect]")
{
  // Box im Ursprung, Seitenlängen = 1
  Box b1{glm::vec3{1, 0, 0}, glm::vec3{0, 1, 1}};
  // Ray geht von min aus durch max
  Ray r1{{1, 0, 0}, {-1, 1, 1}};
  float t = 0;
  REQUIRE(b1.intersect(r1, t) == true);
}

TEST_CASE("read a file", "[file]")
{
  loadSDF("read_mat.sdf");
}


int main(int argc, char *argv[])
{
  return Catch::Session().run(argc, argv);
}
