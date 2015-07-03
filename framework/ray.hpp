// -----------------------------------------------------------------------------
// Copyright  : (C) 2014 Martin Heinrich
// License    : MIT (see the file LICENSE)
// Maintainer : Andreas-C. Bernstein <andreas.bernstein@uni-weimar.de>
// Stability  : experimental
//
// Ray
// -----------------------------------------------------------------------------

#ifndef BUW_RAY_HPP
#define BUW_RAY_HPP
#include <glm/glm.hpp>
#include <glm/gtx/intersect.hpp>
#include <iostream>
struct Ray
{
	// Ray(glm::vec3 const& origin, glm::vec3 const& direction ): origin(origin), direction(direction) {};
	// glm::vec3 origin;
	// glm::vec3 direction; 

	Ray(glm::vec3 const& o, glm::vec3 const& d) :
		origin(o),
		direction(d)
		{
			direction = glm::normalize(direction);
			inv_direction = glm::vec3{1/d.x, 1/d.y, 1/d.z};
			sign[0] = (inv_direction.x < 0);
			sign[1] = (inv_direction.y < 0);
			sign[2] = (inv_direction.z < 0);
		}
	glm::vec3 origin;
	glm::vec3 direction;
	glm::vec3 inv_direction;
	int sign[3];
};


#endif //#define BUW_RAY_HPP
