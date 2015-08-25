#include "hit.hpp"

Hit::Hit(bool h, float distance, glm::vec3 RayOrigin, std::string object): 
	hit_{h},
	distance_{distance},
	normalVec_{0,0,0},
	hitPoint_{0,0,0},
	object_{object} 
	{
		// Berechnung des HitPoints und NormalVec (only if true)
	}

bool Hit::hit() const {
	return hit_;
}

float Hit::distance() const {
	return distance_;
}

// std::shared_ptr<const Shape> Hit::object() const
std::string Hit::object() const 
{
	return object_;
}