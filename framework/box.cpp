#include "box.hpp"
#include <cmath>
#include <algorithm>
#include <limits>
#include <vector>

Box::Box() : Shape{"box_default"}, min_{}, max_{} {}
Box::Box(glm::vec3 const& min, glm::vec3 const& max) : 
	Shape{"box_mm_w"}, 
	min_{min}, 
	max_{max} 
	{}

Box::Box(std::string const name, Color const color):
	Shape("box_default_"+name,color),
	min_{},
	max_{}
	{}
Box::Box(std::string const name, Color const color, glm::vec3 const& min, glm::vec3 const& max):
	Shape("box_mm_"+name, color),
	min_{min},
	max_{max}
	{}

Box::~Box() {}

glm::vec3 Box::min() const
{
	return min_;
}
glm::vec3 Box::max() const
{
	return max_;
}

/*virtual*/ double Box::area() const
{
	glm::vec3 tmp = abs(min_-max_); // abs from Shape
	return 2*(tmp.x * tmp.y)+2*(tmp.x * tmp.z)+2*(tmp.y* tmp.z);
}
/*virtual*/ double Box::volume() const
{
	glm::vec3 tmp = abs(min_-max_); // abs from Shape
	return tmp.x * tmp.y * tmp.z;
}

std::pair<float,bool> Box::intersect(Ray const& ray) const 
{
	float t = 0;
	glm::vec3 r = glm::normalize(ray.direction);
	glm::vec3 dirfrac{0,0,0};
	// http://gamedev.stackexchange.com/questions/18436/most-efficient-aabb-vs-ray-collision-algorithms
	// r is unit direction vector of ray (glm::normalize)
	dirfrac.x = 1.0f / r.x;
	dirfrac.y = 1.0f / r.y;
	dirfrac.z = 1.0f / r.z;
	// lb is the corner of AABB with minimal coordinates - left bottom, rt is maximal corner
	// r.org is origin of ray
	std::vector<float> t_stack;
	t_stack.push_back( (min_.x - ray.origin.x)*dirfrac.x );
	t_stack.push_back( (max_.x - ray.origin.x)*dirfrac.x );
	t_stack.push_back( (min_.y - ray.origin.y)*dirfrac.y );
	t_stack.push_back( (max_.y - ray.origin.y)*dirfrac.y );
	t_stack.push_back( (min_.z - ray.origin.z)*dirfrac.z );
	t_stack.push_back( (max_.z - ray.origin.z)*dirfrac.z );

	for (auto iter  = t_stack.begin(); iter != t_stack.end(); ) {
		if (*iter!=*iter || !isfinite(*iter)) {
			t_stack.erase(iter); 
		}
		else {
			std::cout << *iter << std::endl;
			++iter;
		}
	}
	if (t_stack.size() >= 2) 
	{
		std::sort(t_stack.begin(),t_stack.end());
		
		double tmax = t_stack.front();
		double tmin = t_stack.back();

		std::cout << "min: "<< tmin << " max: " << tmax << " length: " << t_stack.size() << std::endl;
		// if tmax < 0, ray (line) is intersecting AABB, but whole AABB is behing us
		if (tmax < 0)
		{
		    t = tmax;
		    return std::make_pair(t,false);
		}

		// if tmin > tmax, ray doesn't intersect AABB
		if (tmin > tmax)
		{
		    t = tmax;
		    return std::make_pair(t,false);
		}

		t = tmin;
		return std::make_pair(t,true);
	}
}

std::ostream& Box::print(std::ostream& os) const
{
	Shape::print(os);
	return os << "  " << print_point(min_) << " " << print_point(max_) << std::endl;
}

