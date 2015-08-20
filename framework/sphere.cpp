#include "sphere.hpp"
#include <cmath>

Sphere::Sphere() : 
	Shape{"sphere_default"}, 
	center_{}, 
	radius_{} 
	{}
Sphere::Sphere(double const& invalue) : 
	Shape{"sphere_r_b"}, 
	center_{}, 
	radius_{invalue} 
	{}
Sphere::Sphere(glm::vec3 const& invec, double const& inradius) : 
	Shape{"sphere_cr_b"}, 
	center_{invec}, 
	radius_{inradius} 
	{}

Sphere::Sphere(std::string const& name, Material const& material): 
	Shape("sphere_default_"+name, material), 
	center_{}, 
	radius_{} 
	{}
Sphere::Sphere(std::string const& name, Material const& material, double const& radius ):
	Shape("sphere_r_"+name,material),
	center_{},
	radius_{radius}
	{}
Sphere::Sphere(std::string const& name, Material const& material, glm::vec3 const& center, double const& radius) :
	Shape("sphere_cr_"+name, material), 
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
// std::optional (erst mit C++14)
Hit Sphere::intersect(Ray const& ray) const
{
	float distance;
	auto result = glm::intersectRaySphere(
	ray.origin , glm::normalize(ray.direction) , center_ , radius_ * radius_, distance );
	// std::cout << print_point(ray.direction) << print_point(glm::normalize(ray.direction)) << std::endl;
	// return Hit {result, distance, {0,0,0}, {0,0,0}, this->name()};
	// at the moment a lot of debugging code... No Point and so on...
	return Hit {result, distance, {0,0,0}, {0,0,0}, name_ };
}

std::ostream& Sphere::print(std::ostream& os) const
{
	Shape::print(os);
	return os << "  " << print_point(center_) << " with radius " << radius_ << std::endl;
}

std::istream& operator>>(std::istream & ins, Sphere & input) {
	ins >> std::ws >> input.name_;
	float x,y,z;
	ins >> std::ws >> x;
	ins >> std::ws >> y;
	ins >> std::ws >> z;
	input.center_= glm::vec3 {x,y,z};
    
    ins >> std::ws >> input.radius_;
	return ins;
}
