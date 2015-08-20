#ifndef BUW_COMPUTEARC_HPP
#define BUW_COMPUTEARC_HPP

#include "ray.hpp"
#include "sphere.hpp"
#include "box.hpp"

class Light;
class Sphere;
class Box;
struct Ray;

float computeDiffuseArc(Sphere const& sphere, float & d, Ray const& r, Light const& light);
float computeSpecularArc(Sphere const& sphere, float & d, Ray const& r, Light const& light);
float computeDiffuseArc(Box const& box, float & d, Ray const& r, Light const& light);
float computeSpecularArc(Box const& box, float & d, Ray const& r, Light const& light);

#endif // BUW_COMPUTEARC_HPP