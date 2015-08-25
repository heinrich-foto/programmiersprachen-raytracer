#include "composit.hpp"


Composit::Composit():
	Shape{"Composit_default"},
	shape{}
{ }
Composit::Composit(std::string const& name, Material const& material):  
	Shape{"Composit_default-m_"+name, material},
	shape{}
{ }

Composit::Composit()  
{ }


bool Composit::add_child(std::shared_ptr<Shape> const& shape) {
	if (shape!=nullptr) {
		shape_.push_back{shape};
		return true;
	} else {
		return false;
	}
}

/*virtual*/ Hit Composit::intersect(const Ray &r) const override {
	// Redundant!!!!!
	Hit minHit{};
	for (auto const& item : shape_) {
		try {
			Hit hit = item->intersect(ray);
		
			if (hit.hit() && hit < minHit) { // if (hit)
				minHit = hit;
			}
		} catch (...) {
			std::cout << "Bad weak" << std::endl;
			return Hit {};
		}
	}
	if (minHit.hit())
	{
		return minHit;
	} else {
		return Hit {};
	}
}

/*virtual*/ std::ostream& Composit::print(std::ostream& os) const override {
	os << "Composit: " << name_ << std::endl;
	std::copy(std::begin(shape_), std::end(shape_), std::ostream_iterator<*Shape>(os,"/n"));
	return os;
}

/*virtual*/ void Composit::readFromStream (std::istream & ins) override {
		
}
