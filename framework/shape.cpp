#define GLM_FORCE_RADIANS

#include "shape.hpp"
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale

std::ostream& Shape::print(std::ostream& os) const
{
	return os << name_ << ": with material " << color_;
}

// bool Shape::intersect(Ray const& ray, float& t) const {
// 	auto value = intersect(ray);
// 	t = value.second;
// 	return value.first;
// }

std::ostream& operator<<(std::ostream& os, Shape const& s)
{
	s.print(os);
	return os;
}

std::istream& operator>>(std::istream & ins, Shape & input)
{	
	// Copy Input Stream ? Or reset it? --> RESET, cant copy.
	// std::istream ins{ins};
	std::string word;
	// read first word to get the keywords
	ins >> std::ws >> word;
	// // transform object scale value
	// glm::scale(/*vector*/);
	// // transform object rotate angle vec (Grad)
	// glm::rotate(/*winkel, vector*/);
	// // transform object translate vec
	// glm::translate(/*vector*/);
	// // inverse funktion
	// glm::inverse(/*mat4*/);

	// http://glm.g-truc.net/0.9.4/api/a00206.html
	if (word == "scale") {
		float x, y, z;
		ins >> std::ws >> x >> std::ws >> y >> std::ws >> z >> std::ws;
		if (!ins.good()) {
			// matrix_transform.inl:149:43: note: candidate function template not viable: requires 2 arguments, but 1 was provided
			// input.world_transformation_ = glm::dot(input.world_transformation_, glm::scale({x,y,z}));
			input.world_transformation_ = input.world_transformation_ * glm::scale(glm::mat4(),{x,y,z});
			input.world_transformation_inv_ = glm::inverse(input.world_transformation_);
			return ins;
		} else {
			return ins;
		}
	} else if (word == "rotate") {
		float degree, x, y, z;
		ins >> std::ws >> degree >> std::ws >> x >> std::ws >> y >> std::ws >> z >> std::ws;
		if (!ins.good()) {
			input.world_transformation_ = input.world_transformation_ * glm::rotate(glm::mat4(), degree,{x,y,z});
			input.world_transformation_inv_ = glm::inverse(input.world_transformation_);
			return ins;
		} else {
			return ins;
		}		
	} else if (word == "translate") {
		float x, y, z;
		ins >> std::ws >> x >> std::ws >> y >> std::ws >> z >> std::ws;
		if (!ins.good()) {
			input.world_transformation_ = input.world_transformation_ * glm::translate(glm::mat4(),{x,y,z});
			input.world_transformation_inv_ = glm::inverse(input.world_transformation_);
			return ins;
		} else {
			return ins;
		}
	}
	// Input in Abgeleiteter Klasse abarbeiten. Vorher Stream zurücksetzen (da sonst Name fehlt.)
	for (auto rit=word.rbegin(); rit!=word.rend(); ++rit) ins.putback(*rit);
	input.readFromStream(ins);
	ins >> std::ws;
	return ins;
}

std::string Shape::print_point(glm::vec3 const& vec) const
{
	return "[" + std::to_string(vec.x) + ";" + std::to_string(vec.y) + ";" + std::to_string(vec.z) + "]";
}