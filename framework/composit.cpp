#include "composit.hpp"


Composit::Composit():
	Shape{"Composit_default"},
	shape_{}
{ }
Composit::Composit(std::string const& name, Material const& material):  
	Shape{"Composit_default-m_"+name, material},
	shape_{}
{ }


bool Composit::add_child(std::shared_ptr<Shape> const& shape) {
	if (shape!=nullptr) {
		shape_.push_back(shape);
		return true;
	} else {
		return false;
	}
}

/*virtual*/ Hit Composit::intersect(const Ray &r) const {
	// Redundant!!!!!
	Hit minHit{};
	for (auto const& item : shape_) {
		try {
			Hit hit = item->intersect(r);
		
			if (hit.hit() && hit < minHit) { // if (hit)
				minHit = hit;
			}
		} catch (...) {
			std::cout << "Bad weak in Composit" << std::endl;
			return Hit {};
		}
	}
	if (minHit.hit())
	{
		if (minHit.distance()>r.max_t) { minHit.hit(false); }
		return minHit;
	} else {
		return Hit {};
	}
}

/*virtual*/ std::ostream& Composit::print(std::ostream& os) const {
	os << "Composit: " << name_ << std::endl;
	for (auto const& item  : shape_) {
		os << "\t" << item->name() << "\n";
	}
	return os;
}

/*virtual*/ void Composit::readFromStream (std::istream & ins) {
	ins >> std::ws >> name_ >> std::ws;
}
