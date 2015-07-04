// -----------------------------------------------------------------------------
// Copyright  : (C) 2014 Martin Heinrich
// License    : MIT (see the file LICENSE)
// Maintainer : Andreas-C. Bernstein <andreas.bernstein@uni-weimar.de>
// Stability  : experimental
//
// Scene
// DTO verschiedene Assets: Lichter, Shapes, Materials usw.
// -----------------------------------------------------------------------------
// accessing elements in a deque by offsetting a pointer to another element causes undefined behavior.
// deque push und pop front --> vector only back

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
	std::vector<std::shared_ptr<Shape>> shape;
	// std::vector<Light> light;
	// Camera camera;
	// ...
};

#endif // BUW_SCENE
