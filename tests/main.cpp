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

int main(int argc, char *argv[])
{
  return Catch::Session().run(argc, argv);
}
