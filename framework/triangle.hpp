// -----------------------------------------------------------------------------
// Copyright  : (C) 2014 Martin Heinrich
// License    : MIT (see the file LICENSE)
// Maintainer : Andreas-C. Bernstein <andreas.bernstein@uni-weimar.de>
// Stability  : experimental
//
// Triangle
// -----------------------------------------------------------------------------

#ifndef BUW_TRIANGLE_HPP
#define BUW_TRIANGLE_HPP

#include "shape.hpp"

#include <glm/glm.hpp>
#include <glm/gtx/intersect.hpp>
#include <glm/vec3.hpp>

class Triangle : public Shape
{
public: 
	Triangle();
	Triangle(std::string const& name, Material const& material);
	Triangle(std::string const& name, Material const& material, glm::vec3 const& p1, glm::vec3 const& p2, glm::vec3 const& p3);
	~Triangle();


	glm::vec3 p1() const;
	glm::vec3 p2() const;
	glm::vec3 p3() const;

	// brauchen wir nicht. Behalten? (area volume)
	// /*virtual*/ double area() const override;
	// /*virtual*/ double volume() const override;

	// bool intersect(Ray const& ray) const;
	/*virtual*/ Hit intersect(const Ray &r) const override;

	/*virtual*/ std::ostream& print(std::ostream& os) const override;

	friend std::istream& operator>>(std::istream& os, Triangle & input);

protected:
	/*virtual*/ void readFromStream (std::istream & ins) override;

private:
	glm::vec3 p1_;
	glm::vec3 p2_;
	glm::vec3 p3_;
};

#endif // BUW_TRIANGLE
