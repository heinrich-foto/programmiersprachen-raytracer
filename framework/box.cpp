#include "box.hpp"
#include <cmath>

Box::Box() : min_{}, max_{} {}
Box::Box(glm::vec3 const& min, glm::vec3 const& max) : min_{min}, max_{max} {}
Box::~Box() {}

glm::vec3 Box::min() const
{
	return min_;
}
glm::vec3 Box::max() const
{
	return max_;
}

/*virtual*/ double Box::area() const
{
	glm::vec3 tmp = abs(min_-max_); // abs from Shape
	return 2*(tmp.x * tmp.y)+2*(tmp.x * tmp.z)+2*(tmp.y* tmp.z);
}
/*virtual*/ double Box::volume() const
{
	glm::vec3 tmp = abs(min_-max_); // abs from Shape
	return tmp.x * tmp.y * tmp.z;
}
