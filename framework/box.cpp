#include "box.hpp"
#include <cmath>
#include <algorithm>
<<<<<<< HEAD
#include <limits>
#include <vector>
=======
>>>>>>> master

Box::Box() : Shape{"box_default"}, min_{}, max_{} {}
Box::Box(glm::vec3 const& min, glm::vec3 const& max) : 
	Shape{"box_mm_w"}, 
	min_{min}, 
	max_{max} 
	{}

Box::Box(std::string const& name, Color const& color):
	Shape("box_default_"+name,color),
	min_{},
	max_{}
	{}
Box::Box(std::string const& name, Color const& color, glm::vec3 const& min, glm::vec3 const& max):
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

<<<<<<< HEAD
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
	
	float t1 = (min_.x - ray.origin.x) * dirfrac.x ;
	float t2 = (max_.x - ray.origin.x) * dirfrac.x ;
	
	float t3 = (min_.y - ray.origin.y) * dirfrac.y ;
	float t4 = (max_.y - ray.origin.y) * dirfrac.y ;
	
	float t5 = (min_.z - ray.origin.z) * dirfrac.z ;
	float t6 = (max_.z - ray.origin.z) * dirfrac.z ;

		float tmin = std::max(std::max(std::min(t1, t2), std::min(t3, t4)), std::min(t5, t6));
		float tmax = std::min(std::min(std::max(t1, t2), std::max(t3, t4)), std::max(t5, t6));

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
=======
// bool Box::intersect(const Ray &r, float t0, float t1) const {
std::pair<bool,float> Box::intersect(const Ray &r) const {
/* 
	the computet distence is untestet, 
	and at the moment not implemented!! 
	at the moment the boolean value returns 
	true if the ray intersects the box. 

	possible could be a input double vlaue per reference for distance.
	its an more better way maybe, for returning values. (intersection Hitpoint, distance etc.)
*/
	float tmin, tmax, tmin_y, tmax_y, tmin_z, tmax_z;

	tmin  = (min_.x - r.origin.x) * r.inv_direction.x;
	tmax  = (max_.x - r.origin.x) * r.inv_direction.x;
	tmin_y = (min_.y - r.origin.y) * r.inv_direction.y;
	tmax_y = (max_.y - r.origin.y) * r.inv_direction.y;
	
	if ( (tmin > tmax_y) || (tmin_y > tmax) )
	{ 
		//std::cout << tmin <<" > " << tmax_y << " || " <<  tmin_y << " > "  << tmax << std::endl;
		return std::make_pair(false,tmax); 
	}
	if (tmin_y > tmin)
		tmin = tmin_y;
	if (tmax_y < tmax)
		tmax = tmax_y;
	tmin_z = (min_.z - r.origin.z) * r.inv_direction.z;
	tmax_z = (max_.z - r.origin.z) * r.inv_direction.z;
	if ( (tmin > tmax_z) || (tmin_z > tmax) )
	{
		//std::cout << tmin <<" > "<< tmax_z<< " || " <<tmin_z<< " > " << tmax << std::endl;
		return std::make_pair(false,tmax);
	}
	if (tmin_z > tmin)
		tmin = tmin_z;
	if (tmax_z < tmax)
		tmax = tmax_z;

	//std::cout << "min: " << tmin << " max: " << tmax << std::endl;
 	return std::make_pair(true, tmin);
>>>>>>> master
}

std::ostream& Box::print(std::ostream& os) const
{
	Shape::print(os);
	return os << "  " << print_point(min_) << " " << print_point(max_) << std::endl;
}

