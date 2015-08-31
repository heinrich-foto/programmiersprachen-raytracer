#include "box.hpp"
#include <cmath>
#include <algorithm>
#include <vector>

Box::Box() : Shape{"box_default"}, min_{}, max_{} {}
Box::Box(glm::vec3 const& min, glm::vec3 const& max) : 
	Shape{"box_mm_b"}, 
	min_{min}, 
	max_{max} 
	{
		if (min_.x>max_.x) std::swap(min_.x,max_.x);
		if (min_.y>max_.y) std::swap(min_.y,max_.y);
		if (min_.z>max_.z) std::swap(min_.z,max_.z);
	}

Box::Box(std::string const& name, Material const& material):
	Shape("box_default_"+name,material),
	min_{},
	max_{}
	{}
Box::Box(std::string const& name, Material const& material, glm::vec3 const& min, glm::vec3 const& max):
	Shape("box_mm_"+name, material),
	min_{min},
	max_{max}
	{
		if (min_.x>max_.x) std::swap(min_.x,max_.x);
		if (min_.y>max_.y) std::swap(min_.y,max_.y);
		if (min_.z>max_.z) std::swap(min_.z,max_.z);
	}

Box::~Box() {}

glm::vec3 Box::min() const
{
	return min_;
}
glm::vec3 Box::max() const
{
	return max_;
}
// Intersection with triangle
Hit Box::intersect(const Ray &r) const {
	Hit minHit{};

	for (auto const& item : Seiten) {
		try {
			auto hit = item->intersect(r);
			if (hit.hit() && hit < minHit) { // if (hit)
				minHit = hit;
			}
		} catch (...) {
			std::cout << "Bad weak in Box" << std::endl;
			return Hit {};
		}
		
	}
	if (minHit.hit())
	{
		return {minHit.hit(),minHit.distance(), minHit.hitPoint(), minHit.normal(),shared_from_this()};
	} else {
		return Hit {};
	}
}

// Hit Box::intersect(const Ray &r) const{
  
//   float tmp, tmpX, tmpY, tmpZ, xLimit, yLimit, zLimit;
//   glm::vec3 xHitNormal, yHitNormal, zHitNormal;

//   if(max_.x < r.origin.x) {
//     xLimit = max_.x;
//     xHitNormal = {1,0,0};
//   } else {
//     xLimit = min_.x;
//     xHitNormal = {-1,0,0};
//   }

//   if(max_.y < r.origin.y) {
//     yLimit = max_.y;
//     yHitNormal = {0,1,0};
//   } else {
//     yLimit = min_.y;
//     yHitNormal = {0,-1,0};
//   }

//   if(max_.z < r.origin.z) {
//     zLimit = max_.z;
//     zHitNormal = {0,0,1};
//   } else {
//     zLimit = min_.z;
//     zHitNormal = {0,0,-1};
//   }

//   float xHitDistance, yHitDistance, zHitDistance;
//   glm::vec3 xHitPoint, yHitPoint, zHitPoint;
//   bool xHit, yHit, zHit;
//   float eps = 0.001;

//   glm::vec3 normDir = glm::normalize(r.direction);
//   xHitDistance = (xLimit - r.origin.x) / normDir.x;
//   tmpY = r.origin.y + xHitDistance * normDir.y;
//   tmpZ = r.origin.z + xHitDistance * normDir.z;
//   xHitPoint = {xLimit,  tmpY, tmpZ};
//   xHit = xHitDistance>0 && tmpY<=max_.y+eps && tmpY+eps>=min_.y && tmpZ<=max_.z+eps && tmpZ+eps>=min_.z ? true : false;

//   yHitDistance = (yLimit - r.origin.y) / normDir.y;
//   tmpX = r.origin.x + yHitDistance * normDir.x;
//   tmpZ = r.origin.z + yHitDistance * normDir.z;
//   yHitPoint = {tmpX, yLimit, tmpZ};
//   yHit = yHitDistance>0 && tmpX<=max_.x+eps && tmpX+eps>=min_.x && tmpZ<=max_.z+eps && tmpZ+eps>=min_.z ? true : false;

//   zHitDistance = (zLimit - r.origin.z) / normDir.z;
//   tmpX = r.origin.x + zHitDistance * normDir.x;
//   tmpY = r.origin.y + zHitDistance * normDir.y;
//   zHitPoint = {tmpX, tmpY, zLimit};
//   zHit = zHitDistance>0 && tmpX<=max_.x+eps && tmpX+eps>=min_.x && tmpY<=max_.y+eps && tmpY+eps>=min_.y ? true : false;

//   Hit xH {xHit, xHitDistance, xHitNormal, xHitPoint, shared_from_this()};
//   Hit yH {yHit, yHitDistance, yHitNormal, yHitPoint, shared_from_this()};
//   Hit zH {zHit, zHitDistance, zHitNormal, zHitPoint, shared_from_this()};

//   Hit hit{false, INFINITY, {INFINITY, INFINITY, INFINITY}, {0,0,0}, nullptr};
//   hit = xH.hit() && xH.distance() < hit.distance() ? xH : hit;
//   hit = yH.hit() && yH.distance() < hit.distance() ? yH : hit;
//   hit = zH.hit() && zH.distance() < hit.distance() ? zH : hit;

//   return hit;
// }


// Hit Box::intersect(const Ray &r) const {
	
// 	float tmin_x  = (min_.x - r.origin.x) * r.inv_direction.x;
// 	float tmax_x  = (max_.x - r.origin.x) * r.inv_direction.x;
// 	if (tmin_x > tmax_x) std::swap(tmin_x,tmax_x);

// 	float tmin_y = (min_.y - r.origin.y) * r.inv_direction.y;
// 	float tmax_y = (max_.y - r.origin.y) * r.inv_direction.y;
// 	if (tmin_y > tmax_y) std::swap(tmin_y,tmax_x);
	
// 	if ( (tmin_x > tmax_y) || (tmin_y > tmax_x) )
// 	{ 
// 		//std::cout << tmin <<" > " << tmax_y << " || " <<  tmin_y << " > "  << tmax << std::endl;
// 		return Hit {false,tmax_x, r.origin, shared_from_this()}; 
// 		// return Hit {false,tmax, r.origin, name_};
// 	}
// 	if (tmin_y > tmin_x)
// 		tmin_x = tmin_y;
// 	if (tmax_y < tmax_x)
// 		tmax_x = tmax_y;

// 	float tmin_z = (min_.z - r.origin.z) * r.inv_direction.z;
// 	float tmax_z = (max_.z - r.origin.z) * r.inv_direction.z;
// 	if (tmin_z > tmax_z) std::swap(tmin_z,tmax_z);

// 	if ( (tmin_x > tmax_z) || (tmin_z > tmax_x) )
// 	{
// 		//std::cout << tmin <<" > "<< tmax_z<< " || " <<tmin_z<< " > " << tmax << std::endl;
// 		return Hit {false,tmax_x, r.origin, shared_from_this()};
// 		// return Hit {false,tmax, r.origin, name_};
// 	}
// 	if (tmin_z > tmin_x)
// 		tmin_x = tmin_z;
// 	if (tmax_z < tmax_x)
// 		tmax_x = tmax_z;

// 	// std::cout << name_ << " min: " << tmin << " max: " << tmax << r << std::endl;
//  	return Hit {true, tmin_x, r.origin, shared_from_this()};
//  	// return {bool,distance, hitPoint, normal,shared_from_this()};
//  	// return Hit {true, tmin, r.origin, name_};
// }
// Hit Box::intersect(const Ray &r) const {
//  	float tx1 = (min_.x - r.origin.x)* r.inv_direction.x;
// 	float tx2 = (max_.x - r.origin.x)* r.inv_direction.x;
// 	float tmin_x = std::min(tx1, tx2);
// 	float tmax_x = std::max(tx1, tx2);

// 	float tx3 = (min_.y - r.origin.y)* r.inv_direction.y;
// 	float tx4 = (max_.y - r.origin.y)* r.inv_direction.y;
// 	float tmin_y = std::min(tx3, tx4);
// 	float tmax_y = std::max(tx3, tx4);

// 	float tx5 = (min_.z - r.origin.z)* r.inv_direction.z;
// 	float tx6 = (max_.z - r.origin.z)* r.inv_direction.z;
// 	float tmin_z = std::min(tx5, tx6);
// 	float tmax_z = std::max(tx5, tx6);

// 	float tmin = std::max(tmin_x, tmin_y);
// 	float tmax = std::min(tmax_x, tmax_y);
// 	tmin = std::max(tmin, tmin_z);
// 	tmax = std::min(tmax, tmax_z);

// 	return Hit {tmax >= tmin, tmax, r.origin, shared_from_this()};
// 	// return Hit {tmax >= tmin, tmax, r.origin, name_};
// }

std::ostream& Box::print(std::ostream& os) const
{
	Shape::print(os);
	return os << "  " << print_point(min_) << " " << print_point(max_) << std::endl;
}

void Box::readFromStream (std::istream & ins) {
	ins >> std::ws >> name_;
	if (name_=="root") { throw std::invalid_argument("There can only be one root as composit.");}
	float x,y,z;
	ins >> std::ws >> x;
	ins >> std::ws >> y;
	ins >> std::ws >> z;
	min_= glm::vec3 {x,y,z};
    
    ins >> std::ws >> x;
	ins >> std::ws >> y;
	ins >> std::ws >> z;
	max_= glm::vec3 {x,y,z};

	if (min_.x>max_.x) std::swap(min_.x,max_.x);
	if (min_.y>max_.y) std::swap(min_.y,max_.y);
	if (min_.z>max_.z) std::swap(min_.z,max_.z);

	glm::vec3 A  = {min_.x, min_.y , min_.z };
	glm::vec3 C_ = {max_.x, max_.y , max_.z };

	glm::vec3 B  = {  C_.x,    A.y ,    A.z };
	glm::vec3 C  = {   B.x ,  C_.y ,    A.z };
	glm::vec3 D  = {   A.x ,   C.y ,    A.z };

	glm::vec3 A_ = {   A.x ,   A.y ,   C_.z };
	glm::vec3 B_ = {   B.x ,   B.y ,   C_.z };
	glm::vec3 D_ = {   D.x ,   D.y  ,  C_.z };
	// Vorderseite
	Seiten.push_back(std::make_shared<Triangle> (Triangle {"",{}, A,B,C}));
	Seiten.push_back(std::make_shared<Triangle> (Triangle {"",{}, A,C,D}));
	// Rückseite
	Seiten.push_back(std::make_shared<Triangle> (Triangle {"",{}, A_,B_,C_}));
	Seiten.push_back(std::make_shared<Triangle> (Triangle {"",{}, A_,C_,D_}));
	// Linke
	Seiten.push_back(std::make_shared<Triangle> (Triangle {"",{}, A,D,A_}));
	Seiten.push_back(std::make_shared<Triangle> (Triangle {"",{}, D,D_,A_}));
	// Rechte
	Seiten.push_back(std::make_shared<Triangle> (Triangle {"",{}, B,B_,C_}));
	Seiten.push_back(std::make_shared<Triangle> (Triangle {"",{}, B,C_,C}));
	// Unten
	Seiten.push_back(std::make_shared<Triangle> (Triangle {"",{}, A_,B,A}));
	Seiten.push_back(std::make_shared<Triangle> (Triangle {"",{}, A_,B_,B}));
	// Oben
	Seiten.push_back(std::make_shared<Triangle> (Triangle {"",{}, D,C,C_}));
	Seiten.push_back(std::make_shared<Triangle> (Triangle {"",{}, D,C_,D_}));
	// return ins;
}

// std::istream& operator>>(std::istream & ins, Box & input) {
// 	ins >> std::ws >> input.name_;
// 	float x,y,z;
// 	ins >> std::ws >> x;
// 	ins >> std::ws >> y;
// 	ins >> std::ws >> z;
// 	input.min_= glm::vec3 {x,y,z};
    
//     ins >> std::ws >> x;
// 	ins >> std::ws >> y;
// 	ins >> std::ws >> z;
// 	input.max_= glm::vec3 {x,y,z};
// 	return ins;
// }

