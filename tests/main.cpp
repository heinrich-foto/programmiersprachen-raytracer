#define CATCH_CONFIG_RUNNER
#include <catch.hpp>
#include <glm/vec3.hpp>
#include <glm/glm.hpp>
#include <glm/gtx/intersect.hpp>

#include "shape.hpp"
#include "sphere.hpp"
#include "box.hpp"
#include "ray.hpp"

TEST_CASE("Sphere default","[sphere]")
{
	Sphere object{};
	glm::vec3 vec{0,0,0};

	REQUIRE(vec == object.center());
	REQUIRE(0 == object.area());
	REQUIRE(0 == object.volume());
	REQUIRE(0 == object.radius());
}

TEST_CASE("Box default","[box]")
{
	Box object{};
	glm::vec3 vec{0,0,0};

	REQUIRE(vec == object.min());
	REQUIRE(vec == object.max());
	REQUIRE(0 == object.area());
	REQUIRE(0 == object.volume());
}
TEST_CASE("Sphere area volume","[sphare]")
{
	Sphere object{0.2};
	REQUIRE(glm::vec3 (0,0,0) == object.center());
	REQUIRE(0.502655 == Approx(object.area()));
	REQUIRE(0.0335103 == Approx(object.volume()));

	Sphere object2{{1,1,1},-1};
	REQUIRE(glm::vec3(1,1,1) == object2.center());
	REQUIRE(-1 == object2.radius());
	REQUIRE(0 == Approx(object2.area()));
	REQUIRE(0 == Approx(object2.volume()));
}

TEST_CASE("Box area, volume","[box]")
{
	Box object{glm::vec3{0,0,0},glm::vec3{1,1,1}};
	REQUIRE(6 == object.area());
	REQUIRE(1 == object.volume());

	Box object2{glm::vec3{0,0,0},glm::vec3{-1,-1,1}};
	REQUIRE(6 == object2.area());
	REQUIRE(1 == object2.volume());

	Box object3{glm::vec3{2,2,2},glm::vec3{2,2,2}};
	REQUIRE(0 == object3.area());
	REQUIRE(0 == object3.volume());
}

TEST_CASE("name of shapes","[name]")
{
	Box box("hallo",Color{0,0,0});
	REQUIRE("box_default_hallo" == box.name());

	Sphere sphere("world",Color{0,0,0});
	REQUIRE("sphere_default_world" == sphere.name());

	Box box2{"hallo",Color{0.2,0.1,0.0},glm::vec3{1,1,0}, glm::vec3{3,2,3}};
	REQUIRE("box_mm_hallo" == box2.name());

	Sphere sphere2("world",Color{0.1,0.2,0.3}, 0.2);
	REQUIRE("sphere_r_world"==sphere2.name());

	Sphere sphere3("123_02",Color{0,0,0}, glm::vec3{1,2,3}, 0.2);
	REQUIRE("sphere_cr_123_02"==sphere3.name());

	Box box3{};
	REQUIRE("box_default"==box3.name());

	Sphere sphere4{};
	REQUIRE("sphere_default"==sphere4.name());
}

TEST_CASE("ostream sphere and box","[ostream]")
{
	Box 	object ("hallo",Color{0.1,0.03,0.02});
	Sphere  object2("world",Color{1,2,3});
	std::stringstream os;
	os << object;
	REQUIRE("box_default_hallo: with color (0.1,0.03,0.02)\n[0.000000;0.000000;0.000000] [0.000000;0.000000;0.000000]"==os.str());
	os.str( std::string() );
	os.clear();
	os << object2;
	REQUIRE("sphere_default_world: with color (1,2,3)\n[0.000000;0.000000;0.000000] with radius 0"==os.str());
}

TEST_CASE("intersectRaySphere", "[intersect]")
{
	// Ray
	glm::vec3 ray_origin(0.0,0.0,0.0);
	// ray direction has to be normalized ! // you can use:
	// v = glm::normalize(some_vector) 
	glm::vec3 ray_direction(0.0,0.0,1.0);
	// Sphere
	glm::vec3 sphere_center(0.0,0.0,5.0); 
	float sphere_radius (1.0);
	float distance (0.0);
	auto result = glm::intersectRaySphere(
	ray_origin , ray_direction , sphere_center , sphere_radius , distance );
	REQUIRE(distance == Approx(4.0f)); 

	Sphere sphere (sphere_center, sphere_radius);
	Ray ray(ray_origin,ray_direction);
	REQUIRE(Approx(4) == sphere.intersect(ray));
}

TEST_CASE("destructor","[destructor]")
{
	Color red(255, 0, 0); 
	glm::vec3 position(0,0);
	// Sphere* s1 = new Sphere(position, 1.2, red, "sphere0"); 
	// Shape*  s2 = new Sphere(position, 1.2, red, "sphere1");
	Sphere* s1 = new Sphere("sphere0", red, position, 1.2); 
	Shape*  s2 = new Sphere("sphere1", red, position, 1.2);
	
	s1->print(std::cout); 
	s2->print(std::cout);
	
	delete s1; delete s2;
}

int main(int argc, char *argv[])
{
  return Catch::Session().run(argc, argv);
}
