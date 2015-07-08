// -----------------------------------------------------------------------------
// Copyright  : (C) 2014 Martin Heinrich
// License    : MIT (see the file LICENSE)
// Maintainer : Andreas-C. Bernstein <andreas.bernstein@uni-weimar.de>
// Stability  : experimental
//
// Material
// -----------------------------------------------------------------------------

#ifndef BUW_MATERIAL_HPP
#define BUW_MATERIAL_HPP

#include "color.hpp"
#include <iostream>

class Material
{
public: 
	Material();
	Material(std::string const&, Color const&, Color const&, Color const&, float const);
	Material(std::string const&, Color const&, float const);
	~Material() {};

	std::string name() const;
	Color ka() const;
	Color kd() const;
	Color ks() const;
	float m() const;
	
	friend std::ostream& operator<<(std::ostream& os, Material const& input);
	
private:
	std::string name_;
	Color 		ka_;	// koefficiant ambiend
	Color 		kd_;	// koefficiant 
	Color 		ks_;	// koefficiant 
	float 		m_;  	// exponent
};

#endif // BUW_MATERIAL
