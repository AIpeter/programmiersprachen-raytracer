#include "triangle.hpp"

Triangle::Triangle() :
	Shape(),
	left_{0, 0, 0},
	right_{1, 0, 0},
	top_{0.5, 1, 0}
	{}

Triangle::Triangle(Triangle const& triangle) :
	Shape(),
	left_{triangle.left_},
	right_{triangle.right_},
	top_{triangle.top_}
	{}

Triangle::Triangle(glm::vec3 const& left, glm::vec3 const& right, glm::vec3 const& top,
           std::string const& name, Material const& mat) :
	Shape(name, mat),
	left_{left},
	right_{right},
	top_{top}
	{}

glm::vec3 const& Triangle::getleft() const
{
	return left_;
}
    
glm::vec3 const& Triangle::getright() const
{
	return right_;
}
    
glm::vec3 const& Triangle::gettop() const
{
	return top_;
}

float Triangle::area() const // override
{

}

float Triangle::volume() const // override
{
	return 0;
}

/*virtual*/ std::ostream& Triangle::print(std::ostream& os) const // override
{
        os << "Triangle " << name() << ", left (" << left_.x << "," 
                << left_.y << "," << left_.z << "), right (" << right_.x << "," 
                << right_.y << "," << top_.z << "), top (" << top_.x << ","
                << top_.y << "," << top_.z << ")" << "\n" << mat();
        return os;
}

Hit Triangle::intersect(Ray const& r, float & d)
{
        Hit hit;
	bool cut = false;
	auto dir = glm::normalize(r.direction);
	glm::vec3 dvec = {0, 0, d};

	cut = glm::intersectRayTriangle(r.origin, dir, left_, right_, top_, dvec);
	
        if (cut == true)
        {
                d = dvec.z;
                hit.intersectionPoint = r.origin + (d * dir);
                glm::vec3 right{right_.x - left_.x,
                                right_.y - left_.y, 
                                right_.z - left_.z}; // direction of triangleplane
                glm::vec3 top{top_.x - left_.x,  
                                top_.y - left_.y,
                                top_.z - left_.z}; // direction of triangleplane
                hit.normal = glm::cross(right, top); //Normalenvektor
                hit.intersect = cut;
        }

	return hit;
}

void Triangle::translate(glm::vec3 const& direction)
{
	left_ = left_ + direction;
	right_ = right_ + direction;
	top_ = top_ + direction;
}
    
void Triangle::scale(glm::vec3 const& scale)
{
	left_ = left_ * scale;
	right_ = right_ * scale;
	top_ = top_ * scale;
}

void Triangle::rotate(float angle, glm::vec3 const& axis)
{

}