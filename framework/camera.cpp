#include "camera.hpp"

Camera::Camera() :
name_{cam},
fov_x_{45}
position_{0, 0, 0},
direction_{0, 0, -1}, // camera looks in direction of negative z-axis
up_{1, 0, -5}
{}

Camera::Camera(std::string const& name, double const fov_x,
                glm::vec3 const& position, glm::vec3 direction,
                glm::vec3 up) :
name_{name},
fov_x_{fov_x}
position_{position},
direction_{direction},
up_{up}
{}

std::string const& Camera::getname() const
{
	return name_;
}

double const& Camera::getfov_x() const
{
  return fov_x_;
}

glm::vec3 const& Camera::getpostion() const
{
	return position_;
}
	
glm::vec3 const& getDirection() const
{
  return direction_;
}

glm::vec3 const& getUp() const
{
  return up_;
}