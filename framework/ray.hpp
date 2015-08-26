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

	// Ray(glm::vec3 const& o, glm::vec3 const& d) :
	// 	origin(o),
	// 	direction(d)
	// 	{
	// 		//direction = glm::normalize(direction);
	// 		glm::vec3 dir = glm::normalize(direction);
	// 		inv_direction = glm::vec3{1/dir.x, 1/dir.y, 1/dir.z};
	// 		// sign[0] = (inv_direction.x < 0);
	// 		// sign[1] = (inv_direction.y < 0);
	// 		// sign[2] = (inv_direction.z < 0);
	// 	}
	// glm::vec3 origin;
	// glm::vec3 direction;
	// glm::vec3 inv_direction;
	// // int sign[3];

	Ray(glm::vec3 const& o, glm::vec3 const& d) :
		origin{ o },
		direction{ d },
		inv_direction{1.0 / glm::normalize(direction).x,
					1.0 / glm::normalize(direction).y,
					1.0 / glm::normalize(direction).y } {}

	glm::vec3 origin;
	glm::vec3 direction;
	glm::vec3 inv_direction;

	friend std::ostream& operator<<(std::ostream& os, Ray const& ray) {
		return os << "Ray with origin: [" << std::to_string(ray.origin.x) << ";" << std::to_string(ray.origin.y) << ";" << std::to_string(ray.origin.z) << "]"
		<< " dir: [" << std::to_string(ray.direction.x) << ";" << std::to_string(ray.direction.y) << ";" << std::to_string(ray.direction.z) << "]"
		<< " inv_dir: [" << std::to_string(ray.inv_direction.x) << ";" << std::to_string(ray.inv_direction.y) << ";" << std::to_string(ray.inv_direction.z) << "]" << std::endl;
	}
};


#endif //#define BUW_RAY_HPP
