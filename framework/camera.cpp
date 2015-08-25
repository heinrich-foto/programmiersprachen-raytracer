#include "camera.hpp"

Camera::Camera(std::string name, glm::vec3 pos, float fovX,  float resX) :
	name_{name}, 
	position_{pos}, 
	fovX_{fovX}, 
	distance_{0} 
{
	compute_distance();
}
	
// glm::vec3 Camera::translate() {};
// glm::vec3 Camera::rotate() {};

void Camera::compute_distance() {
	// todo calculate Distance
	// distance_= ;
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
	input.compute_distance();
	return ins; // should be empty
}