#define CATCH_CONFIG_RUNNER
#include <catch.hpp>
#include <glm/vec3.hpp>
#include "shape.hpp"
#include "sphere.hpp"

TEST_CASE("Sphere","[sphere]")
{
	Sphere object{};
	glm::vec3 vec{0,0,0};

	REQUIRE(vec == object.center());
	REQUIRE(0 == object.area());
	REQUIRE(0 == object.volume());
	REQUIRE(0 == object.radius());
}

int main(int argc, char *argv[])
{
  return Catch::Session().run(argc, argv);
}
