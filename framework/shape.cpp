#include "shape.hpp"

std::ostream& Shape::print(std::ostream& os) const
{
	return os << name_ << ": with color " << color_;
}

bool Shape::intersect(Ray const& ray, float& t) const {
	auto value = intersect(ray);
	t = value.second;
	return value.first;
}

std::ostream& operator<<(std::ostream& os, Shape const& s)
{
	s.print(os);
	return os;
}

std::string Shape::print_point(glm::vec3 const& vec) const
{
	return "[" + std::to_string(vec.x) + ";" + std::to_string(vec.y) + ";" + std::to_string(vec.z) + "]";
}