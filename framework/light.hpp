#ifndef BUW_LIGHT_HPP
#define BUW_LIGHT_HPP
#include <color.hpp>
#include <string>
#include <iostream>
#include <glm/vec3.hpp>
#include <glm/glm.hpp>
#include <glm/gtx/intersect.hpp>

class Light
{
public:
	Light();
	Light(std::string const& name, glm::vec3 const& position, Color const& la, Color const& ld);
	std::string const& getname() const;
	glm::vec3 const& getpostion() const;
	Color const& getla() const;
	Color const& getld() const;

private:
	std::string name_;
	glm::vec3 position_;
	Color la_;
	Color ld_;
};
#endif