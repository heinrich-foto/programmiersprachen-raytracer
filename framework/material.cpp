#include "material.hpp"

Material(): name_("d_black"), ka_{0,0,0}, kd_{0,0,0}, ks_{0,0,0}, m(0) {}
~Material() {}


std::string name() const {
	return name_;
}

Color ka() const {
	return ka_;
}

Color kd() const {
	return kd_;
}

Color ks() const {
	return ks_;
}

float m() const {
	return m_;
}


friend std::ostream& operator<<(std::ostream& os, Material const& input) {
	return os << input.name_ << " with:"
			<< "\n\t" 	<< input.ka_
			<< "\n\t" 	<< input.kd_
			<< "\n\t" 	<< input.ks_
			<< "\n\t" 	<< input.m_ 
			<< std::endl;
}
