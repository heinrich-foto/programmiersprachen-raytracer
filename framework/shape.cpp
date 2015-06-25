#include "shape.hpp"

std::ostream& Shape::print(std::ostream& os) const
{
	os << name_ << ": with color " << color_;
	return os;
}


std::ostream& operator<<(std::ostream& os, Shape const& s)
{
	s.print(os);
	return os;
}