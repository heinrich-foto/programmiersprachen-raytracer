#include "box.hpp"
#include <cmath>
#include <algorithm>

Box::Box() : Shape{"box_default"}, min_{}, max_{} {}
Box::Box(glm::vec3 const& min, glm::vec3 const& max) : 
	Shape{"box_mm_b"}, 
	min_{min}, 
	max_{max} 
	{}

Box::Box(std::string const& name, Material const& material):
	Shape("box_default_"+name,material),
	min_{},
	max_{}
	{}
Box::Box(std::string const& name, Material const& material, glm::vec3 const& min, glm::vec3 const& max):
	Shape("box_mm_"+name, material),
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
Hit Box::intersect(const Ray &r) const {
/* 
	the computet distence is untestet, 
	and at the moment not implemented!! 
	at the moment the boolean value returns 
	true if the ray intersects the box. 

	possible could be a input double vlaue per reference for distance.
	its an more better way maybe, for returning values. (intersection Hitpoint, distance etc.)
*/
	float tmin, tmax, tmin_y, tmax_y, tmin_z, tmax_z;

	tmin  = (min_.x - r.origin.x) * r.inv_direction.x;
	tmax  = (max_.x - r.origin.x) * r.inv_direction.x;
	tmin_y = (min_.y - r.origin.y) * r.inv_direction.y;
	tmax_y = (max_.y - r.origin.y) * r.inv_direction.y;
	
	if ( (tmin > tmax_y) || (tmin_y > tmax) )
	{ 
		//std::cout << tmin <<" > " << tmax_y << " || " <<  tmin_y << " > "  << tmax << std::endl;
		return Hit {false,tmax, glm::vec3 {0,0,0}, glm::vec3 {0,0,0}, shared_from_this()}; 
	}
	if (tmin_y > tmin)
		tmin = tmin_y;
	if (tmax_y < tmax)
		tmax = tmax_y;
	tmin_z = (min_.z - r.origin.z) * r.inv_direction.z;
	tmax_z = (max_.z - r.origin.z) * r.inv_direction.z;
	if ( (tmin > tmax_z) || (tmin_z > tmax) )
	{
		//std::cout << tmin <<" > "<< tmax_z<< " || " <<tmin_z<< " > " << tmax << std::endl;
		return Hit {false,tmax, glm::vec3 {0,0,0}, glm::vec3 {0,0,0}, shared_from_this()};
	}
	if (tmin_z > tmin)
		tmin = tmin_z;
	if (tmax_z < tmax)
		tmax = tmax_z;

	//std::cout << "min: " << tmin << " max: " << tmax << std::endl;
 	return Hit {true, tmin, glm::vec3 {0,0,0}, glm::vec3 {0,0,0}, shared_from_this()};
}

std::ostream& Box::print(std::ostream& os) const
{
	Shape::print(os);
	return os << "  " << print_point(min_) << " " << print_point(max_) << std::endl;
}

std::istream& operator>>(std::istream & ins, Box & input) {
	ins >> std::ws >> input.name_;
	float x,y,z;
	ins >> std::ws >> x;
	ins >> std::ws >> y;
	ins >> std::ws >> z;
	input.min_= glm::vec3 {x,y,z};
    
    ins >> std::ws >> x;
	ins >> std::ws >> y;
	ins >> std::ws >> z;
	input.max_= glm::vec3 {x,y,z};
	return ins;
}

