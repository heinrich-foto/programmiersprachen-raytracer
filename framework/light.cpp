#include "light.hpp"

Light::Light():
	name_{"default_light"},
	position_{200,200,0},
	la_{0,0,0},
	ld_{0,0,0},
	lp_{0,0,0}
	{}

Light::Light(std::string const& name, glm::vec3 const& position, Color const& ambient, Color const& diffuse, Color const& hu):
	name_{name},
	position_{position},
	la_{ambient},
	ld_{diffuse},
	lp_{hu}
	{}

Color Light::color() const {
	return (lighttype_=="ambient")? la_ : ld_;
}

Color Light::ambient() const {
	return la_;
}

Color Light::diffuse() const {
	return ld_;
}

glm::vec3 Light::position() const {
	// if (lighttype_=="ambient") throw std::invalid_argument("Ambient light dosnt have a position.");
	return position_;
}

std::ostream& operator<<(std::ostream& os, Light const& input) {
	return os << "Light: " << input.lighttype_ << " "
	<< input.name_ << " " 
	<< "[" << input.position_.x << "," << input.position_.y << "," << input.position_.z << "]" 
	<< input.color() << std::endl;
}

std::istream& operator>>(std::istream & ins, Light & input) {
	// define light ambient name pos La
	// define light diffuse name     Ld
	ins >> std::ws >> input.lighttype_;
	ins >> std::ws >> input.name_;
	if (input.lighttype_=="diffuse") {
		float x,y,z;
		ins >> std::ws >> x;
		ins >> std::ws >> y;
		ins >> std::ws >> z;
		input.position_={x,y,z};
		ins >> std::ws >> input.ld_;
	} else if (input.lighttype_=="ambient") {
		ins >> std::ws >> input.la_;
	} else {
		throw("invalid Light Type.");
	}
	ins >> std::ws;
	return ins; // should be empty
}