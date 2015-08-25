// -----------------------------------------------------------------------------
// Copyright  : (C) 2014 Martin Heinrich
// License    : MIT (see the file LICENSE)
// Maintainer : Andreas-C. Bernstein <andreas.bernstein@uni-weimar.de>
// Stability  : experimental
//
// Camera
// -----------------------------------------------------------------------------

#ifndef BUW_CAMERA_HPP
#define BUW_CAMERA_HPP

#include <glm/vec3.hpp>
#include <string>

class Camera {
public:
	Camera(std::string name, glm::vec3 pos, float fovX,  float resX);
	// glm::vec3 translate();
	// glm::vec3 rotate();
private:
	std::string name_;
	glm::vec3 position_;
	float fovX_;
	float distance_;
	// Translations und Rotationsmatrix??!!!!!
};

#endif // BUW_CAMERA