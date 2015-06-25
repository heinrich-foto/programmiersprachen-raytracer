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

struct Ray
{
	Ray(glm::vec3 const& origin, glm::vec3 const& direction ): origin(origin), direction(direction) {};
	glm::vec3 origin;
	glm::vec3 direction; 
};


#endif //#define BUW_RAY_HPP
