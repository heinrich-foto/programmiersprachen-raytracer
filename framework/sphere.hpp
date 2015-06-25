// -----------------------------------------------------------------------------
// Copyright  : (C) 2014 Martin Heinrich
// License    : MIT (see the file LICENSE)
// Maintainer : Andreas-C. Bernstein <andreas.bernstein@uni-weimar.de>
// Stability  : experimental
//
// Sphere
// -----------------------------------------------------------------------------

#ifndef BUW_SPHERE_HPP
#define BUW_SPHERE_HPP

#include "shape.hpp"
#include "color.hpp"


#include <glm/vec3.hpp>

class Sphere : public Shape
{
public: 
	Sphere();
	Sphere(double const&);
	Sphere(glm::vec3 const&, double const&);

	Sphere(std::string const, Color const);
	Sphere(std::string const, Color const, double const& );
	Sphere(std::string const, Color const, glm::vec3 const&, double const& );
	~Sphere();


	glm::vec3 center() const;
	//void center(glm::vec3 const&);

	double radius() const;
	//void   radius(double const&);

	/*virtual*/ double area() const override;
	/*virtual*/ double volume() const override;

private:
	glm::vec3 	center_;
	double 		radius_;
};

#endif // BUW_SPHERE
