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

class Shape
{
public: 
	Shape() : name_("default_shape"), color_{} {};

	~Shape() {};

	virtual double area() const;
	virtual double volume() const;

private:
	std::string name_;
	Color 		color_;
};

#endif // BUW_SHAPE
