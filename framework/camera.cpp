#include "camera.hpp"
#include <cmath>

Camera::Camera(std::string name, glm::vec3 pos, float fovX,  unsigned resX) :
	name_{name}, 
	position_{pos}, 
	fovX_{fovX}, 
	distance_{0} 
{ }
	
// glm::vec3 Camera::translate() {};
// glm::vec3 Camera::rotate() {};
std::string Camera::name() const {
	return name_;
}

float Camera::compute_distance(unsigned resX) {
	if (fovX_ >0 & resX > 0) { 
		distance_= (tan(M_PI /360)*fovX_)*2/resX;
		return distance_;
	} else {
		distance_ = -1;
		return -1;
	}
	// Beachte! Bezugsgröße für die Distanz ist die Bildbreite, d.h. resY
}

std::istream& operator>>(std::istream & ins, Camera & input) {
	ins >> std::ws >> input.name_;
	ins >> std::ws >> input.fovX_;
	if (ins.good()) { // Abweichend vom Standart SDF Format!!!!!
		float x,y,z;
		ins >> std::ws >> x;
		ins >> std::ws >> y;
		ins >> std::ws >> z;
		input.position_= glm::vec3 {x,y,z};
	}
	return ins; // should be empty
}