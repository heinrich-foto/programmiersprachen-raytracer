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
#include "ray.hpp"

#include <glm/vec3.hpp>
#include <cmath>
#include <iostream>

class Shape
{
public: 
	// Shape(Color const color): name_("shape_"+color.str()),color_{color} {}; 
	virtual ~Shape() { 
		// std::cout << "--  Destruktor Shape " << *this << std::endl; 
	};

	virtual double area() const = 0;
	virtual double volume() const = 0;

	Color color() const { return color_; };
	std::string name() const { return name_; };

	glm::vec3 abs(glm::vec3 const& ivec) const { return {std::fabs(ivec.x),std::fabs(ivec.y),std::fabs(ivec.z)}; };

	virtual std::ostream& print(std::ostream& os) const;

	virtual bool intersect(Ray const& ray, float& t) const;
	virtual std::pair<bool,float> intersect(const Ray &r) const = 0;

	friend std::ostream& operator<<(std::ostream& os, Shape const& s);
	// friend std::ostream& operator<<(std::ostream& os, glm::vec3 const vec);

protected: 
	// Protected Construktor.
	// Shape() : name_("shape_default_w"), color_{0,0,0} {};
	Shape(std::string const& name) : name_(name), color_{0,0,0} {};
	Shape(std::string const& name, Color const& color): name_(name), color_{color} { 
		// std::cout << "++ Konstruktor Shape " << *this << std::endl; 
	};
	std::string print_point(glm::vec3 const& vec) const;
private:
	// Shape(const Shape&); // no copy
	// Shape& operator=(const Shape&); 
	std::string name_;
	Color 		color_;
};

#endif // BUW_SHAPE
