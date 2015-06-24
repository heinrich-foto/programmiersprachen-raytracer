// -----------------------------------------------------------------------------
// Copyright  : (C) 2014 Martin Heinrich
// License    : MIT (see the file LICENSE)
// Maintainer : Andreas-C. Bernstein <andreas.bernstein@uni-weimar.de>
// Stability  : experimental
//
// Box
// https://de.wikipedia.org/wiki/Minimal_umgebendes_Rechteck
// -----------------------------------------------------------------------------

#ifndef BUW_BOX_HPP
#define BUW_BOX_HPP

#include "shape.hpp"
#include "color.hpp"


#include <glm/vec3.hpp>

class Box : public Shape
{
public: 
	Box();
	Box(glm::vec3 const&, glm::vec3 const&);
	~Box();


	glm::vec3 min() const;
	glm::vec3 max() const;

	/*virtual*/ double area() const override;
	/*virtual*/ double volume() const override;


private:
	glm::vec3 	min_;
	glm::vec3 	max_;
};

#endif // BUW_BOX
