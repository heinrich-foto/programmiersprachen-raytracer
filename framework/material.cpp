#include "material.hpp"

Material::Material(): name_("d_black"), ka_{0,0,0}, kd_{0,0,0}, ks_{0,0,0}, m_(0) {}

Material::Material(std::string const& name, Color const& ka, Color const& kd, Color const& ks, float const m) :
	name_{name},
	ka_{ka},
	kd_{kd},
	ks_{ks},
	m_{m}
	{}
Material::Material(std::string const& name, Color const& k, float const m):
	name_{name},
	ka_{k},
	kd_{k},
	ks_{k},
	m_{m}
	{}

std::string Material::name() const {
	return name_;
}

Color Material::ka() const {
	return ka_;
}

Color Material::kd() const {
	return kd_;
}

Color Material::ks() const {
	return ks_;
}

float Material::m() const {
	return m_;
}


std::ostream& operator<<(std::ostream& os, Material const& input) {
	return os << input.name_ << " with:"
			<< "\n\t ka: " 	<< input.ka_
			<< "\n\t kd: " 	<< input.kd_
			<< "\n\t ks: " 	<< input.ks_
			<< "\n\t m:  " 	<< input.m_ 
			<< std::endl;
}
