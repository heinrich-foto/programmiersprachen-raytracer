// -----------------------------------------------------------------------------
// Copyright  : (C) 2014 Martin Heinrich
// License    : MIT (see the file LICENSE)
// Maintainer : Andreas-C. Bernstein <andreas.bernstein@uni-weimar.de>
// Stability  : experimental
//
// Shape
// -----------------------------------------------------------------------------

#ifndef BUW_SHAPE_HPP
#define BUW_SHAPE_HPP

#include "color.hpp"
#include <glm/vec3.hpp>
#include <cmath>

class Shape
{
public: 
	Shape() : name_("default_shape"), color_{0,0,0} {};

	~Shape() {};

	virtual double area() const = 0;
	virtual double volume() const = 0;

	glm::vec3 abs(glm::vec3 const& ivec) const { return {std::fabs(ivec.x),std::fabs(ivec.y),std::fabs(ivec.z)}; };

private:
	std::string name_;
	Color 		color_;
};

#endif // BUW_SHAPE
