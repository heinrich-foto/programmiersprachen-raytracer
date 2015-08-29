#include "triangle.hpp"
#include <cmath>

Triangle::Triangle() : 
	Shape{"triangle_default"}, 
	center_{}, 
	radius_{} 
	{}
Triangle::Triangle(double const& invalue) : 
	Shape{"triangle_r_b"}, 
	center_{}, 
	radius_{invalue} 
	{}
Triangle::Triangle(glm::vec3 const& invec, double const& inradius) : 
	Shape{"triangle_cr_b"}, 
	center_{invec}, 
	radius_{inradius} 
	{}

Triangle::Triangle(std::string const& name, Material const& material): 
	Shape("triangle_default_"+name, material), 
	center_{}, 
	radius_{} 
	{}
Triangle::Triangle(std::string const& name, Material const& material, double const& radius ):
	Shape("triangle_r_"+name,material),
	center_{},
	radius_{radius}
	{}
Triangle::Triangle(std::string const& name, Material const& material, glm::vec3 const& center, double const& radius) :
	Shape("triangle_cr_"+name, material), 
	center_{center}, 
	radius_{radius} 
	{ 
		// std::cout << "++ Konstruktor Triangle " << *this << std::endl; 
	}

Triangle::~Triangle() 
	{ 
		// std::cout << "-- Destruktor Triangle " << *this << std::endl;
	}


glm::vec3 Triangle::p1() const { 
	return p1_;
}

glm::vec3 Triangle::p2() const { 
	return p2_;
}

glm::vec3 Triangle::p3() const { 
	return p3_;
}



Hit Triangle::intersect(Ray const& r) const
{
	float distance;
	glm::vec3 IntersectionNormal;
	glm::vec3 HitPoint;

	auto result = glm::intersectRayTriangle(
		r.origin, glm::normalize(r.direction), center_, radius_, HitPoint, IntersectionNormal);
	result = glm::intersectRayTriangle(
		r.origin , glm::normalize(r.direction) , center_ , radius_ * radius_, distance );
	
	// std::cout << print_point(r.direction) << print_point(glm::normalize(r.direction)) << std::endl;
	// return Hit {result, distance, {0,0,0}, {0,0,0}, this->name()};
	// at the moment a lot of debugging code... No Point and so on...
	// return Hit {result, distance, r.origin, name_ };
	return Hit {result, distance, IntersectionNormal, HitPoint, shared_from_this()};
}

std::ostream& Triangle::print(std::ostream& os) const
{
	Shape::print(os);
	return os << "  " << print_point(center_) << " with radius " << radius_ << std::endl;
}

void Triangle::readFromStream (std::istream & ins) {
	ins >> std::ws >> name_;
	if (name_=="root") { throw std::invalid_argument("There can only be one root as composit.");}
	float x,y,z;
	ins >> std::ws >> x;
	ins >> std::ws >> y;
	ins >> std::ws >> z;
	center_= glm::vec3 {x,y,z};
    
    ins >> std::ws >> radius_;
	// return ins;
}

// std::istream& operator>>(std::istream & ins, Triangle & input) {
// 	ins >> std::ws >> input.name_;
// 	float x,y,z;
// 	ins >> std::ws >> x;
// 	ins >> std::ws >> y;
// 	ins >> std::ws >> z;
// 	input.center_= glm::vec3 {x,y,z};
    
//     ins >> std::ws >> input.radius_;
// 	return ins;
// }
