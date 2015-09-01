#define CATCH_CONFIG_RUNNER
#include <catch.hpp>
#include <glm/vec3.hpp>
#include <glm/glm.hpp>
#include <glm/gtx/intersect.hpp>

#include "shape.hpp"
#include "sphere.hpp"
#include "box.hpp"
#include "ray.hpp"
#include "sdfloader.hpp"

TEST_CASE("Sphere default","[sphere]")
{
	Sphere object{};
	glm::vec3 vec{0,0,0};

	REQUIRE(vec == object.center());
	// REQUIRE(0 == object.area());
	// REQUIRE(0 == object.volume());
	REQUIRE(0 == object.radius());
}

TEST_CASE("Box default","[box]")
{
	Box object{};
	glm::vec3 vec{0,0,0};

	REQUIRE(vec == object.min());
	REQUIRE(vec == object.max());
}

TEST_CASE("name of shapes","[name]")
{
	Box box("hallo",Material{});
	REQUIRE("box_default_hallo" == box.name());

	Sphere sphere("world",Material{});
	REQUIRE("sphere_default_world" == sphere.name());

	Box box2{"hallo",Material{},glm::vec3{1,1,0}, glm::vec3{3,2,3}};
	REQUIRE("box_mm_hallo" == box2.name());

	Sphere sphere2("world",Material{}, 0.2);
	REQUIRE("sphere_r_world"==sphere2.name());

	Sphere sphere3("123_02",Material{}, glm::vec3{1,2,3}, 0.2);
	REQUIRE("sphere_cr_123_02"==sphere3.name());

	Box box3{};
	REQUIRE("box_default"==box3.name());

	Sphere sphere4{};
	REQUIRE("sphere_default"==sphere4.name());
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

	auto sphere = std::make_shared<Sphere> (Sphere {sphere_center, sphere_radius});
	Ray ray(ray_origin,ray_direction);
	REQUIRE(Approx(4) == sphere->intersect(ray).distance());
	REQUIRE(true == sphere->intersect(ray).hit());

	Ray ray2(ray_origin,glm::vec3{0,0,3});
	REQUIRE(Approx(4) == sphere->intersect(ray2).distance());
	REQUIRE(true == sphere->intersect(ray2).hit());	
}

TEST_CASE("box ray intersect", "[intersct]") 
{
	// Ray
	glm::vec3 ray_origin(0.0,0.0,0.0);
	// ray direction has to be normalized ! // you can use:
	// v = glm::normalize(some_vector) 

	auto box1 = std::make_shared<Box> ( Box {glm::vec3{1,1,1}, glm::vec3{2,2,2}});
	auto box2 = std::make_shared<Box> ( Box {glm::vec3{-2,-2,-2},glm::vec3{1,1,1}});
	auto box3 = std::make_shared<Box> ( Box {glm::vec3{1,1,1},glm::vec3{-1,-1,-1}});

	Ray ray_x (ray_origin,glm::vec3{1,0,0});
	Ray ray_y (ray_origin,glm::vec3{0,1,0});
	Ray ray_z (ray_origin,glm::vec3{0,0,1});

	Ray ray_xy  (ray_origin,glm::vec3{1,1,0});
	Ray ray_xz  (ray_origin,glm::vec3{1,0,1});
	Ray ray_yz  (ray_origin,glm::vec3{0,1,1});
	Ray ray_xyz (ray_origin,glm::vec3{1,1,1});

	Ray ray_ (ray_origin,glm::vec3{8,9,8});

	REQUIRE(true  == box1->intersect(ray_xyz).hit());
	REQUIRE(true  == box1->intersect(ray_).hit());
	REQUIRE(false == box1->intersect(ray_x).hit());
	REQUIRE(false == box1->intersect(ray_y).hit());
	// REQUIRE(false == box1->intersect(ray_z).hit()); // with expansion: false == true
	REQUIRE(false == box1->intersect(ray_xy).hit());
	REQUIRE(false == box1->intersect(ray_yz).hit());
	REQUIRE(false == box1->intersect(ray_xz).hit());

	REQUIRE(true  == box2->intersect(ray_xyz).hit());
	REQUIRE(true  == box2->intersect(ray_).hit());
	REQUIRE(true  == box2->intersect(ray_x).hit());
	REQUIRE(true  == box2->intersect(ray_y).hit());
	REQUIRE(true  == box2->intersect(ray_z).hit());
	REQUIRE(true  == box2->intersect(ray_xy).hit());
	REQUIRE(true  == box2->intersect(ray_yz).hit());
	REQUIRE(true  == box2->intersect(ray_xz).hit());

	auto b = std::make_shared<Box> (Box {glm::vec3{0.5, 0.5, 0.5}, glm::vec3{0.1, 0.0, 0.0}});
	Ray ray1(glm::vec3{0.0, 0.0, 0.0}, glm::vec3{0.2, 0.2, 0.2});
	Ray ray2(glm::vec3{1.0, 1.0, 1.0}, glm::vec3{0.0, 0.0, 0.0});

	REQUIRE(b->intersect(ray1).hit() == true);
	REQUIRE(b->intersect(ray2).hit() == false);
}


TEST_CASE("SDFLoader","[sdf::load()]"){
	auto SDF = SDFLoader::instance();
	auto scene = SDF->load("../material.sdf");

	for (auto const& item : scene.material) std::cout << item << std::endl;

	Color red{1,0,0};
	Color blue{0,0,1};
	Color green{0,1,0};
	REQUIRE(4 == scene.material.size());
	REQUIRE("red" == scene.material.at(0).name());
	REQUIRE(red == scene.material.at(0).ka());
	REQUIRE(red == scene.material.at(0).kd());
	REQUIRE(red == scene.material.at(0).ks());
	REQUIRE(1 == scene.material.at(0).m());

	REQUIRE("blue"== scene.material.at(1).name());
	REQUIRE(blue == scene.material.at(1).ka());
	REQUIRE(blue == scene.material.at(1).kd());
	REQUIRE(blue == scene.material.at(1).ks());
	REQUIRE(1 == scene.material.at(1).m());

	REQUIRE("green"== scene.material.at(2).name());
	REQUIRE(green == scene.material.at(2).ka());
	REQUIRE(green == scene.material.at(2).kd());
	REQUIRE(green == scene.material.at(2).ks());
	REQUIRE(11 == scene.material.at(2).m());
}

int main(int argc, char *argv[])
{
  return Catch::Session().run(argc, argv);
}
