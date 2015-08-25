// -----------------------------------------------------------------------------
// Copyright  : (C) 2014 Martin Heinrich
// License    : MIT (see the file LICENSE)
// Maintainer : Andreas-C. Bernstein <andreas.bernstein@uni-weimar.de>
// Stability  : experimental
//
// Light
// -----------------------------------------------------------------------------

#ifndef BUW_LIGHT_HPP
#define BUW_LIGHT_HPP

#include <glm/vec3.hpp>
#include <string>

class Light {
public:
	Light();
	Light(std::string const&, glm::vec3 const&, Color const&, Color const&, Color const&);
private:
	std::string name_;
	glm::vec3 position_;
	Color la_; // Ambient Light
	Color ld_; // Diffuse Light
	Color lp_; // Helligkeit der Punktlichtquelle
};

#endif // BUW_LIGHT