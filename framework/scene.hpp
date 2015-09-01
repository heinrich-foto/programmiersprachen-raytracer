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
#include "color.hpp"
#include "light.hpp"
#include "camera.hpp"
#include <vector>


struct Scene
{
	Scene(): 
		material{}, 
		shape{},
		light{},
		camera{"default_camera",{0,0,0}, 60, 600}, 
		ambientColor{0,0,0}, 
		ambientBrightness{0.5}, 
		resX{600}, 
		resY{600},
		filename{"image.ppm"} {};

	std::vector<Material> material;
	std::vector<std::shared_ptr<Shape>> shape;
	std::vector<Light> light;
	Camera camera;
	Color ambientColor;		// could be Depricated soon?
	float ambientBrightness; // Depricated
	unsigned resX;
	unsigned resY;
	float SSAA_;
	std::string filename;

	Material get_material(std::string name) const {
		for (auto const& m_item : material) {
			if (name == m_item.name()) return m_item;
		}
		return Material{};
	};

	std::shared_ptr<Shape> get_shape(std::string name) const {
		for (auto const& m_item : shape) {
			if (name == m_item->name()) return m_item;
		}
		return nullptr;
	};
};

#endif // BUW_SCENE
