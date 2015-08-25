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
#include <memory>
class Shape; // hit.hpp:26:18: error: use of undeclared identifier 'Shape'
class Hit {
	Hit(bool h, float distance, glm::vec3 RayOrigin, std::string object);

	friend bool operator<(Hit const& lhs, Hit const& rhs) {
		return lhs.distance < rhs.distance;
	};

	friend bool operator>(Hit const& lhs, Hit const& rhs) {
		return lhs.distance > rhs.distance;
	};

	// friend bool operator==(Hit const& lhs, Hit const& rhs) {
	// 	return ?(hit_)
	// };
	
private:
	bool hit_;
	float distance_;
	glm::vec3 normalVec_;
	glm::vec3 hitPoint_;
	// std::shared_ptr<const Shape> object_;
	std::string object_;
};

#endif // BUW_HIT