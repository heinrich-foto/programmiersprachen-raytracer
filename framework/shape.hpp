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
#include <iostream>

class Shape
{
public: 
	// Shape() : name_("shape_default_w"), color_{0,0,0} {};
	Shape(std::string const& name) : name_(name), color_{0,0,0} {};
	Shape(std::string const& name, Color const& color): name_(name), color_{color} {};
	// Shape(Color const color): name_("shape_"+color.str()),color_{color} {}; 
	~Shape() {};

	virtual double area() const = 0;
	virtual double volume() const = 0;

	Color color() const { return color_; };
	std::string name() const { return name_; };

	glm::vec3 abs(glm::vec3 const& ivec) const { return {std::fabs(ivec.x),std::fabs(ivec.y),std::fabs(ivec.z)}; };

	virtual std::ostream& print(std::ostream& os) const;

private:
	std::string name_;
	Color 		color_;
};

#endif // BUW_SHAPE
