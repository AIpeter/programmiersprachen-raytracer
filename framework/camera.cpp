#include "camera.hpp"

Camera::Camera() :
  name_{"cam"},
  fov_x_{45},
  position_{0, 0, 0},
  direction_{0, 0, -1}, // camera looks in direction of negative z-axis
  cam_up_{0, 1, 0}
  {
    cam_right_ = glm::cross(direction_, cam_up_);
    cam_up_ = glm::cross(cam_right_, direction_);
  }

Camera::Camera(std::string const& name, double const fov_x,
                glm::vec3 const& position, glm::vec3 direction,
                glm::vec3 up) :
  name_{name},
  fov_x_{fov_x},
  position_{position},
  direction_{glm::normalize(direction)},
  cam_up_{up}
  {
    cam_right_ = glm::cross(direction_, cam_up_);
    cam_up_ = glm::cross(cam_right_, direction_);
  }

std::string const& Camera::getName() const
{
	return name_;
}

double const& Camera::getFov_x() const
{
  return fov_x_;
}

glm::vec3 const& Camera::getPosition() const
{
	return position_;
}
	
glm::vec3 const& Camera::getDirection() const
{
  return direction_;
}

glm::vec3 const& Camera::getCamUp() const
{
  return cam_up_;
}

glm::vec3 const& Camera::getCamRight() const
{
  return cam_right_;
}