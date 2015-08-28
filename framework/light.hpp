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
	Light():
		name_{"default_light"},
		position_{200,200,0},
		la_{0,0,0},
		ld_{0,0,0},
		lp_{0,0,0}
	{};

	Light(std::string const& name, glm::vec3 const& position, Color const& ambient, Color const& diffuse, Color const& hu):
		name_{"default_light"},
		position_{position},
		la_{ambient},
		ld_{diffuse},
		lp_{hu}
		{};
private:
	std::string name_;
	glm::vec3 position_;
	Color la_; // Ambient Light
	Color ld_; // Diffuse Light
	Color lp_; // Helligkeit der Punktlichtquelle
};

#endif // BUW_LIGHT