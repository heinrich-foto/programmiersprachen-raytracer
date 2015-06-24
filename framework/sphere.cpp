#include "sphere.hpp"
#include <cmath>

Sphere::Sphere() : center_{}, radius_{} {}
Sphere::Sphere(double const& invalue) : center_{}, radius_{invalue} {}
Sphere::Sphere(glm::vec3 const& invec, double const& inradius) : center_{invec}, radius_{inradius} {}
Sphere::~Sphere() {}


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
	return 4 * M_PI * pow(radius_,2);
}
/*virtual*/ double Sphere::volume() const
{
	return 4 * pow(3,-1) * M_PI * pow(radius_,3);
}