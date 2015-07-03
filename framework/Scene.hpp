// -----------------------------------------------------------------------------
// Copyright  : (C) 2014 Martin Heinrich
// License    : MIT (see the file LICENSE)
// Maintainer : Andreas-C. Bernstein <andreas.bernstein@uni-weimar.de>
// Stability  : experimental
//
// Scene
// -----------------------------------------------------------------------------

#ifndef BUW_SCENE_HPP
#define BUW_SCENE_HPP

#include "material.hpp"
#include "shape.hpp"
#include "box.hpp"
#include "sphere.hpp"

#include <vector>


struct Scene
{
	std::vector<Material> material;
};

#endif // BUW_SCENE
