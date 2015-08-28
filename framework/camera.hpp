// -----------------------------------------------------------------------------
// Copyright  : (C) 2014 Martin Heinrich
// License    : MIT (see the file LICENSE)
// Maintainer : Andreas-C. Bernstein <andreas.bernstein@uni-weimar.de>
// Stability  : experimental
//
// Camera
/*  Kamera ist definiert durch <Namen> und den 
	horizontalen Öffnungsinkel <fovX>.
	Sie befindet sich im Nullpunkt und blickt in Richtung der negativen z-Achse. 

	Somit mit Camera() Konstruktor?

	Erweitertes Kamera Modell
	===========

	camera <name> <fov-x> <eye> (Position) <dir> (Blickrichtung) <up> (Up-Vector)
*/
// -----------------------------------------------------------------------------

#ifndef BUW_CAMERA_HPP
#define BUW_CAMERA_HPP

#include "ray.hpp"
#include "pixel.hpp"
#include <glm/vec3.hpp>
#include <string>
#include <iostream>

class Camera {
public:
	Camera(std::string name, glm::vec3 pos, float fovX,  unsigned resX);
	// glm::vec3 translate();
	// glm::vec3 rotate();
	std::string name() const;
	glm::vec3 position() const;
	float fovX() const;
	float distance() const;

	friend std::ostream& operator<<(std::ostream& os, Camera const& input);
	friend std::istream& operator>>(std::istream & ins, Camera & input);

	Ray compute_ray(Pixel const& p, unsigned resX, unsigned resY) const;
	float compute_distance( unsigned resX);

private:
	std::string name_;
	glm::vec3 position_; //eye
	float fovX_;
	float distance_; // Entfernung zur Bildebene 
	glm::vec3 dir_; // Blickrichtung
	glm::vec3 up_; // Up-Vector

	// Translations und Rotationsmatrix??!!!!!
	
};

#endif // BUW_CAMERA