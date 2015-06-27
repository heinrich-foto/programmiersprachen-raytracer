#include "box.hpp"
#include <cmath>
#include <algorithm>
#include <limits>
#include <vector>

Box::Box() : Shape{"box_default"}, min_{}, max_{} {}
Box::Box(glm::vec3 const& min, glm::vec3 const& max) : 
	Shape{"box_mm_w"}, 
	min_{min}, 
	max_{max} 
	{}

Box::Box(std::string const name, Color const color):
	Shape("box_default_"+name,color),
	min_{},
	max_{}
	{}
Box::Box(std::string const name, Color const color, glm::vec3 const& min, glm::vec3 const& max):
	Shape("box_mm_"+name, color),
	min_{min},
	max_{max}
	{}

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

// bool Box::intersect(const Ray &r, float t0, float t1) const {
std::pair<float,bool> Box::intersect(const Ray &r) const {
	float tmin, tmax, tymin, tymax, tzmin, tzmax;

	tmin  = (min_.x - r.origin.x) * r.inv_direction.x;
	tmax  = (max_.x - r.origin.x) * r.inv_direction.x;
	tymin = (min_.y - r.origin.y) * r.inv_direction.y;
	tymax = (max_.y - r.origin.y) * r.inv_direction.y;
	
	if ( (tmin > tymax) || (tymin > tmax) )
		return std::make_pair(tmax,false);
	if (tymin > tmin)
		tmin = tymin;
	if (tymax < tmax)
		tmax = tymax;
	tzmin = (min_.z - r.origin.z) * r.inv_direction.z;
	tzmax = (max_.z - r.origin.z) * r.inv_direction.z;
	if ( (tmin > tzmax) || (tzmin > tmax) )
		return std::make_pair(tmax,false);
	if (tzmin > tmin)
		tmin = tzmin;
	if (tzmax < tmax)
		tmax = tzmax;

	std::cout << "min: " << tmin << " max: " << tmax << std::endl;
 	// return ( (tmin < t1) && (tmax > t0) );
}

std::ostream& Box::print(std::ostream& os) const
{
	Shape::print(os);
	return os << "  " << print_point(min_) << " " << print_point(max_) << std::endl;
}

