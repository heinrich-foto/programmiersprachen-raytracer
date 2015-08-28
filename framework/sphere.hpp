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

#include <glm/glm.hpp>
#include <glm/gtx/intersect.hpp>
#include <glm/vec3.hpp>

class Sphere : public Shape
{
public: 
	Sphere();
	Sphere(double const&);
	Sphere(glm::vec3 const&, double const&);

	Sphere(std::string const&, Material const&);
	Sphere(std::string const&, Material const&, double const& );
	Sphere(std::string const&, Material const&, glm::vec3 const&, double const& );
	~Sphere();


	glm::vec3 center() const;
	//void center(glm::vec3 const&);

	double radius() const;
	//void   radius(double const&);

	// brauchen wir nicht. Behalten? (area volume)
	// /*virtual*/ double area() const override;
	// /*virtual*/ double volume() const override;

	// bool intersect(Ray const& ray) const;
	/*virtual*/ Hit intersect(const Ray &r) const override;

	/*virtual*/ std::ostream& print(std::ostream& os) const override;

	friend std::istream& operator>>(std::istream& os, Sphere & input);

protected:
	/*virtual*/ void readFromStream (std::istream & ins) override;

private:
	glm::vec3 	center_;
	double 		radius_;
};

#endif // BUW_SPHERE
