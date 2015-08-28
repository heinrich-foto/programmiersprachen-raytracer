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

// Hit Box::intersect(const Ray &r) const {
// 	float tmin, tmax, tmin_y, tmax_y, tmin_z, tmax_z;

// 	tmin  = (min_.x - r.origin.x) * r.inv_direction.x;
// 	tmax  = (max_.x - r.origin.x) * r.inv_direction.x;
// 	tmin_y = (min_.y - r.origin.y) * r.inv_direction.y;
// 	tmax_y = (max_.y - r.origin.y) * r.inv_direction.y;
	
// 	if ( (tmin > tmax_y) || (tmin_y > tmax) )
// 	{ 
// 		//std::cout << tmin <<" > " << tmax_y << " || " <<  tmin_y << " > "  << tmax << std::endl;
// 		// return Hit {false,tmax, r.origin, shared_from_this()}; 
// 		return Hit {false,tmax, r.origin, name_};
// 	}
// 	if (tmin_y > tmin)
// 		tmin = tmin_y;
// 	if (tmax_y < tmax)
// 		tmax = tmax_y;
// 	tmin_z = (min_.z - r.origin.z) * r.inv_direction.z;
// 	tmax_z = (max_.z - r.origin.z) * r.inv_direction.z;
// 	if ( (tmin > tmax_z) || (tmin_z > tmax) )
// 	{
// 		//std::cout << tmin <<" > "<< tmax_z<< " || " <<tmin_z<< " > " << tmax << std::endl;
// 		// return Hit {false,tmax, r.origin, shared_from_this()};
// 		return Hit {false,tmax, r.origin, name_};
// 	}
// 	if (tmin_z > tmin)
// 		tmin = tmin_z;
// 	if (tmax_z < tmax)
// 		tmax = tmax_z;

// 	std::cout << name_ << " min: " << tmin << " max: " << tmax << r << std::endl;
//  	// return Hit {true, tmin, r.origin, shared_from_this()};
//  	return Hit {true, tmin, r.origin, name_};
// }
Hit Box::intersect(const Ray &r) const {
 	float tx1 = (min_.x - r.origin.x)* r.inv_direction.x;
	float tx2 = (max_.x - r.origin.x)* r.inv_direction.x;
	float tmin_x = std::min(tx1, tx2);
	float tmax_x = std::max(tx1, tx2);

	float tx3 = (min_.y - r.origin.y)* r.inv_direction.y;
	float tx4 = (max_.y - r.origin.y)* r.inv_direction.y;
	float tmin_y = std::min(tx3, tx4);
	float tmax_y = std::max(tx3, tx4);

	float tx5 = (min_.z - r.origin.z)* r.inv_direction.z;
	float tx6 = (max_.z - r.origin.z)* r.inv_direction.z;
	float tmin_z = std::min(tx5, tx6);
	float tmax_z = std::max(tx5, tx6);

	float tmin = std::max(tmin_x, tmin_y);
	float tmax = std::min(tmax_x, tmax_y);
	tmin = std::max(tmin, tmin_z);
	tmax = std::min(tmax, tmax_z);

	// if (tmax >= tmin) std::cout << "Box " << name_ << " hit: " << tmax << " " << tmin << " " << r << std::endl;
	return Hit {tmax >= tmin, tmax, r.origin, name_};
}

std::ostream& Box::print(std::ostream& os) const
{
	Shape::print(os);
	return os << "  " << print_point(min_) << " " << print_point(max_) << std::endl;
}

void Box::readFromStream (std::istream & ins) {
	ins >> std::ws >> name_;
	if (name_=="root") { throw std::invalid_argument("There can only be one root as composit.");}
	float x,y,z;
	ins >> std::ws >> x;
	ins >> std::ws >> y;
	ins >> std::ws >> z;
	min_= glm::vec3 {x,y,z};
    
    ins >> std::ws >> x;
	ins >> std::ws >> y;
	ins >> std::ws >> z;
	max_= glm::vec3 {x,y,z};
	// return ins;
}

// std::istream& operator>>(std::istream & ins, Box & input) {
// 	ins >> std::ws >> input.name_;
// 	float x,y,z;
// 	ins >> std::ws >> x;
// 	ins >> std::ws >> y;
// 	ins >> std::ws >> z;
// 	input.min_= glm::vec3 {x,y,z};
    
//     ins >> std::ws >> x;
// 	ins >> std::ws >> y;
// 	ins >> std::ws >> z;
// 	input.max_= glm::vec3 {x,y,z};
// 	return ins;
// }

