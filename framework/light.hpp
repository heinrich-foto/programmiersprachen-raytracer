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

#include "color.hpp"
#include <glm/vec3.hpp>
#include <string>
#include <iostream>

class Light {
public:
	Light();
	Light(std::string const& name, glm::vec3 const& position, Color const& ambient, Color const& diffuse, Color const& hu);

	Color color() const;
	Color ambient() const;
	Color diffuse() const;
	glm::vec3 position() const;
	std::string type() const {return lighttype_; };

	friend std::ostream& operator<<(std::ostream& os, Light const& input);
	friend std::istream& operator>>(std::istream & ins, Light & input);
private:
	std::string name_;
	glm::vec3 position_;
	Color la_; // Ambient Light
	Color ld_; // Diffuse Light
	Color lp_; // Helligkeit der Punktlichtquelle
	std::string lighttype_; // ambient, diffuse
};

#endif // BUW_LIGHT