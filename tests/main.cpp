#define CATCH_CONFIG_RUNNER
#include <catch.hpp>
#include <glm/vec3.hpp>
#include "shape.hpp"
#include "sphere.hpp"
#include "box.hpp"

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
	Box object{{0,0,0},{1,1,1}};
	REQUIRE(6 == object.area());
	REQUIRE(1 == object.volume());

	Box object2{{0,0,0},{-1,-1,1}};
	REQUIRE(6 == object2.area());
	REQUIRE(1 == object2.volume());

	Box object3{{2,2,2},{2,2,2}};
	REQUIRE(0 == object3.area());
	REQUIRE(0 == object3.volume());
}

int main(int argc, char *argv[])
{
  return Catch::Session().run(argc, argv);
}
