#ifndef BUW_COMPUTEARC_HPP
#define BUW_COMPUTEARC_HPP
#define _USE_MATH_DEFINES

#include "ray.hpp"
#include "hit.hpp"
#include "light.hpp"
#include <cmath>

float computeDiffuseArc(Hit const& hit, Light const& light);
float computeSpecularArc(Hit const& hit, Ray const& r, Light const& light);

#endif // BUW_COMPUTEARC_HPP