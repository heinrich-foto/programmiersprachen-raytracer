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
public:
	// Hit(bool h, float distance, glm::vec3 RayOrigin, std::string object);
	Hit(bool h, float distance, glm::vec3 RayOrigin, std::shared_ptr<const Shape> object);
	Hit();

	bool hit() const;
	float distance() const;
	glm::vec3 hitPoint() const;
	std::shared_ptr<const Shape> object() const;
	// std::string object() const;

	friend bool operator<(Hit const& lhs, Hit const& rhs) {
		return lhs.distance_ < rhs.distance_;
	};

	friend bool operator>(Hit const& lhs, Hit const& rhs) {
		return lhs.distance_ > rhs.distance_;
	};

	// friend bool operator==(Hit const& lhs, Hit const& rhs) {
	// 	return (lhs.hit_==rhs.hit_)&&(lhs<rhs); // Objekt representiert keine Gleichheit mehr.
	// };
	
private:
	bool hit_;
	float distance_;
	glm::vec3 normalVec_;
	glm::vec3 hitPoint_;
	std::shared_ptr<const Shape> object_;
	// std::string object_;
};

#endif // BUW_HIT