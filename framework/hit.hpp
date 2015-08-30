#ifndef BUW_HIT_HPP
#define BUW_HIT_HPP

#include <glm/vec3.hpp>

struct Hit
{
        glm::vec3 intersectionPoint;
        glm::vec3 normal;
        bool intersect;
};

#endif