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
	Camera(std::string const& name, double const fov_x,
          glm::vec3 const& position, glm::vec3 direction,
          glm::vec3 up);
	std::string const& getName() const;
  double const& getFov_x() const;
  glm::vec3 const& getPostion() const;
  glm::vec3 const& getDirection() const;
	glm::vec3 const& getUp() const;

private:
	std::string name_;
  double fov_x_;
	glm::vec3 position_;
	glm::vec3 direction_;
  glm::vec3 up_;
};
#endif