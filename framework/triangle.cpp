#include "triangle.hpp"
#include <cmath>

Triangle::Triangle() : 
	Shape{"triangle_default"}, 
	p1_{0,0,0},
	p2_{0,0,0},
	p3_{0,0,0}
	{}

Triangle::Triangle(std::string const& name, Material const& material): 
	Shape("triangle_default_"+name, material), 
	p1_{0,0,0},
	p2_{0,0,0},
	p3_{0,0,0}
	{}
Triangle::Triangle(std::string const& name, Material const& material, glm::vec3 const& p1, glm::vec3 const& p2, glm::vec3 const& p3) :
	Shape("triangle_cr_"+name, material), 
	p1_{p1},
	p2_{p2},
	p3_{p3} 
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
	glm::vec3 baryPosition;

	auto result = glm::intersectRayTriangle	( r.origin, r.direction, p1_, p2_ , p3_, baryPosition);	
	
	// std::cout << print_point(r.direction) << print_point(glm::normalize(r.direction)) << std::endl;
	// return Hit {result, distance, {0,0,0}, {0,0,0}, this->name()};
	// at the moment a lot of debugging code... No Point and so on...
	// return Hit {result, distance, r.origin, name_ };
	return Hit {result, distance, IntersectionNormal, baryPosition, shared_from_this()};
}

std::ostream& Triangle::print(std::ostream& os) const
{
	Shape::print(os);
	return os << "  " << print_point(p1_) 
	<< ", " << print_point(p2_) 
	<< ", " << print_point(p3_)
	<< std::endl;
}

void Triangle::readFromStream (std::istream & ins) {
	ins >> std::ws >> name_;
	if (name_=="root") { throw std::invalid_argument("There can only be one root as composit.");}
	float x,y,z;
	ins >> std::ws >> x;
	ins >> std::ws >> y;
	ins >> std::ws >> z;
	p1_= glm::vec3 {x,y,z};

	ins >> std::ws >> x;
	ins >> std::ws >> y;
	ins >> std::ws >> z;
	p2_= glm::vec3 {x,y,z};

	ins >> std::ws >> x;
	ins >> std::ws >> y;
	ins >> std::ws >> z;
	p3_= glm::vec3 {x,y,z};
}