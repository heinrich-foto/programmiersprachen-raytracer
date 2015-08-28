#include "hit.hpp"

// Hit::Hit(bool h, float distance, glm::vec3 RayOrigin, std::string object): 
Hit::Hit(bool h, float distance, glm::vec3 RayOrigin, std::shared_ptr<const Shape> object): 
	hit_{h},
	distance_{distance},
	normalVec_{0,0,0},
	hitPoint_{0,0,0},
	object_{object} 
	{
		// Berechnung des HitPoints und NormalVec (only if true)
	}

Hit::Hit(bool h, float distance, glm::vec3 normalVec, glm::vec3 hitPoint, std::string object):
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

float Hit::distance() const {
	return distance_;
}

glm::vec3 Hit::hitPoint() const {
	return hitPoint_;
}

std::shared_ptr<const Shape> Hit::object() const
// std::string Hit::object() const 
{
	return object_;
}