// -----------------------------------------------------------------------------
// Copyright  : (C) 2014 Martin Heinrich
// License    : MIT (see the file LICENSE)
// Maintainer : Andreas-C. Bernstein <andreas.bernstein@uni-weimar.de>
// Stability  : experimental
//
// Hit
// -----------------------------------------------------------------------------

#ifndef BUW_HIT_HPP
#define BUW_HIT_HPP

#include "ray.hpp"
#include "shape.hpp"

#include <glm/vec3.hpp>

struct Hit {
	// Hit(float d, std::string n):hit{false},distance{d},name{n} {};
	// Hit(bool h,float d, std::string n):hit{h},distance{d},name{n} {};
	bool hit;
	float distance;
	glm::vec3 normalVec;
	glm::vec3 hitPoint;
	std::shared_ptr<Shape> object;

	friend bool operator<(Hit const& lhs, Hit const& rhs) {
		return lhs.distance < rhs.distance;
	};

	friend bool operator>(Hit const& lhs, Hit const& rhs) {
		return lhs.distance > rhs.distance;
	};

};

#endif // BUW_HIT