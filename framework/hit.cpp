#include "hit.hpp"

// Hit::Hit(bool h, float distance, glm::vec3 RayOrigin, std::string object): 
Hit::Hit(bool h, float distance, glm::vec3 const& RayOrigin, std::shared_ptr<const Shape> const& object): 
	hit_{h},
	distance_{distance},
	normalVec_{0,0,0},
	hitPoint_{0,0,0},
	object_{object} 
	{
		// Berechnung des HitPoints und NormalVec (only if true)
	}

Hit::Hit(bool h, float distance, glm::vec3 const& normalVec, glm::vec3 const& hitPoint, std::shared_ptr<const Shape> const& object):
	hit_{h},
	distance_{distance},
	normalVec_{normalVec},
	hitPoint_{hitPoint},
	object_{object} 
	{}

Hit::Hit(): 
	hit_{false},
	distance_{std::numeric_limits<double>::infinity()},
	normalVec_{0,0,0},
	hitPoint_{0,0,0},
	object_{nullptr}
	// object_{"nullptr"}
	{}

bool Hit::hit() const {
	return hit_;
}

void Hit::hit(bool value) {
	hit_ = value;
}

float Hit::distance() const {
	return distance_;
}

glm::vec3 Hit::hitPoint() const {
	return hitPoint_;
}

glm::vec3 Hit::normalVec() const {
	return normalVec_;
}

std::shared_ptr<const Shape> Hit::object() const
// std::string Hit::object() const 
{
	return object_;
}