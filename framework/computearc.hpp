#ifndef BUW_COMPUTEARC_HPP
#define BUW_COMPUTEARC_HPP

#include "light.hpp"
#include "ray.hpp"
#include "sphere.hpp"

class Light;
class Sphere;
struct Ray;

float computeArc(Sphere const& sphere, float & d, Ray const& r, Light const& light);

#endif // BUW_COMPUTEARC_HPP