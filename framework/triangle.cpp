#include "triangle.hpp"
#include <cmath>
#include <glm/gtx/fast_square_root.hpp> // fastNormalize

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

	auto result = glm::intersectRayTriangle	( r.origin, glm::normalize(r.direction), p1_, p2_ , p3_, baryPosition);	
	if (result==true) {
		// Convert barycentric to world coordinates
		// http://gamedev.stackexchange.com/questions/65723/finding-z-given-x-y-coordinates-on-terrain
        double u, v, w;
        u = baryPosition.x;
        v = baryPosition.y;
        w = 1 - (u+v);

        baryPosition.x = (u * p1_.x + v * p2_.x + w * p3_.x);
        baryPosition.y = (u * p1_.y + v * p2_.y + w * p3_.y);
        baryPosition.z = (u * p1_.z + v * p2_.z + w * p3_.z);
	}

	distance = glm::distance(r.origin,baryPosition);
	// http://glm.g-truc.net/0.9.2/api/a00006.html
	// IntersectionNormal = glm::fastNormalize(glm::cross(p3_ - p1_, p2_ - p1_));
	IntersectionNormal = glm::normalize(glm::cross(p3_ - p1_, p2_ - p1_));

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
	ins >> std::ws;
}