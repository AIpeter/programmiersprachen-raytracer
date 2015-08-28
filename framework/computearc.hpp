#ifndef BUW_COMPUTEARC_HPP
#define BUW_COMPUTEARC_HPP
#define _USE_MATH_DEFINES

#include "ray.hpp"
#include "sphere.hpp"
#include "box.hpp"
#include "triangle.hpp"
#include <cmath>

class Triangle;
class Light;
class Sphere;
class Box;
struct Ray;

float computeDiffuseArc(Sphere const& sphere, float & d, Ray const& r, Light const& light);
float computeSpecularArc(Sphere const& sphere, float & d, Ray const& r, Light const& light);
float computeDiffuseArc(Box const& box, float & d, Ray const& r, Light const& light);
float computeSpecularArc(Box const& box, float & d, Ray const& r, Light const& light);
float computeDiffuseArc(Triangle const& triangle, float & d, Ray const& r, Light const& light);
//float computeSpecularArc(Triangle const& triangle, float & d, Ray const& r, Light const& light);


#endif // BUW_COMPUTEARC_HPP