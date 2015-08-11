#ifndef BUW_CAMERA_HPP
#define BUW_CAMERA_HPP
//#include <color.hpp>
#include <string>
//#include <iostream>
#include <glm/vec3.hpp>
#include <glm/glm.hpp>
#include <glm/gtx/intersect.hpp>

class Camera
{
public:
	Camera();
	Camera(std::string const& name, double fov_x);
	std::string const& getname() const;
	glm::vec3 const& getpostion() const;
	double const& getfov_x() const;

private:
	std::string name_;
	glm::vec3 position_;
	glm::vec3 direction_;
	double fov_x_;
};
#endif