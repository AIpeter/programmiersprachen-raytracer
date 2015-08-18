#include "light.hpp"

Light::Light() :
name_{},
position_{0, 0, 0},
la_{0.0, 0.0, 0.0},
ld_{0.0, 0.0, 0.0}
{}

Light::Light(std::string const& name, glm::vec3 const& position, Color const& la, Color const& ld) :
name_{name},
position_{position},
la_{la},
ld_{ld}
{}

std::string const& Light::getname() const
{
	return name_;
}

glm::vec3 const& Light::getposition() const
{
	return position_;
}

Color const& Light::getla() const
{
	return la_;
}

Color const& Light::getld() const
{
	return ld_;
}

Color const& Light::getLight(float & d, Ray const& r, Shape* const& shape) const
{
	Sphere sphere{shape->center(), shape->radius(), shape->name(), shape->mat()};
	float cosin = computeArc(sphere, d, r, *this);
	return (ld_ * sphere.mat().kd() * cosin);
}