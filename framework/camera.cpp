#include "camera.hpp"
#include <cmath>

Camera::Camera(std::string name, glm::vec3 pos, float fovX,  unsigned resX) :
	name_{name}, 
	position_{pos}, 
	fovX_{fovX}, 
	distance_{int(resX)/tan(fovX*M_PI/180)} 
{ }
	
// glm::vec3 Camera::translate() {};
// glm::vec3 Camera::rotate() {};
std::string Camera::name() const {
	return name_;
}

glm::vec3 Camera::position() const {
	return position_;
}

float Camera::fovX() const {
	return fovX_;
}

float Camera::distance() const {
	return distance_;
}

Ray Camera::compute_ray(Pixel const& p, unsigned resX, unsigned resY) const {
	float x = -int(resX)/2.0f+p.x; 
    float y = -int(resY)/2.0f+p.y;
    float z = -distance_;
    return Ray {position_, {x,y,z}};
}

float Camera::compute_distance(unsigned resX) {
	if (fovX_ >0 & resX > 0) { 
		// distance_= (tan(M_PI /360)*fovX_)*2/resX;
		distance_=int(resX)/tan(fovX_*M_PI/180);
		return distance_;
	} else {
		distance_ = -1;
		return -1;
	}
	// Beachte! Bezugsgröße für die Distanz ist die Bildbreite, d.h. resY
}

std::ostream& operator<<(std::ostream& os, Camera const& input) {
	return os << input.name_ << " => "
			<< " pos: " 	<< "[" << std::to_string(input.position_.x) << ";" << std::to_string(input.position_.y) << ";" << std::to_string(input.position_.z) << "]"
			<< " fovX: " 	<< input.fovX_
			<< " distance: " 	<< input.distance_
			<< std::endl;
}

std::istream& operator>>(std::istream & ins, Camera & input) {
	ins >> std::ws >> input.name_;
	ins >> std::ws >> input.fovX_ >> std::ws;
	if (ins.good()) { // Abweichend vom Standart SDF Format!!!!!
		float x,y,z;
		ins >> std::ws >> x;
		ins >> std::ws >> y;
		ins >> std::ws >> z;
		input.position_= glm::vec3 {x,y,z};
	} else {
		input.position_= glm::vec3 {0,0,0};
	}
	return ins; // should be empty
}