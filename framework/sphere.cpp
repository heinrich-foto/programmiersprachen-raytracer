#include "sphere.hpp"
#include <cmath>

Sphere::Sphere() : 
	Shape{"sphere_default"}, 
	center_{}, 
	radius_{} 
	{}
Sphere::Sphere(double const& invalue) : 
	Shape{"sphere_r_w"}, 
	center_{}, 
	radius_{invalue} 
	{}
Sphere::Sphere(glm::vec3 const& invec, double const& inradius) : 
	Shape{"sphere_cr_w"}, 
	center_{invec}, 
	radius_{inradius} 
	{}

Sphere::Sphere(std::string const name, Color const color): 
	Shape("sphere_default_"+name, color), 
	center_{}, 
	radius_{} 
	{}
Sphere::Sphere(std::string const name, Color const color, double const& radius ):
	Shape("sphere_r_"+name,color),
	center_{},
	radius_{radius}
	{}
Sphere::Sphere(std::string const name, Color const color, glm::vec3 const& center, double const& radius) :
	Shape("sphere_cr_"+name, color), 
	center_{center}, 
	radius_{radius} 
	{ 
		// std::cout << "++ Konstruktor Sphere " << *this << std::endl; 
	}

Sphere::~Sphere() 
	{ 
		// std::cout << "-- Destruktor Sphere " << *this << std::endl;
	}


glm::vec3 Sphere::center() const
{
	return center_;
}
//void Sphere::center(glm::vec3 const&);

double Sphere::radius() const
{
	return radius_;
}
//void   Sphere::radius(double const&);

/*virtual*/ double Sphere::area() const
{
	return (radius_>0)? 4 * M_PI * pow(radius_,2) : 0;
}
/*virtual*/ double Sphere::volume() const
{
	return (radius_>0)? 4 * pow(3,-1) * M_PI * pow(radius_,3) : 0;
}

double Sphere::intersect(Ray const& ray) const
{
	float distance;
	glm::intersectRaySphere(
	ray.origin , glm::normalize(ray.direction) , center_ , radius_ , distance );
	return distance;
}

std::ostream& Sphere::print(std::ostream& os) const
{
	Shape::print(os);
	return os << "  " << print_point(center_) << " with radius " << radius_ << std::endl;
}

