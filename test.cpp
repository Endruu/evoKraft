#ifdef UTEST

#include "catch.hpp"

#include "GameObject.h"

#include <cassert>
#include <cmath>

TEST_CASE("normalizedRot")
{
	static const auto pi = std::atan(1.0f) * 4.0f;

	CHECK(normalizedRot(180.0f) == -pi / 2.0f);
	CHECK(normalizedRot(0.0f) == pi / 2.0f);
	CHECK(normalizedRot(270.0f) == pi);
	CHECK(normalizedRot(90.0f) == 0.0f);
	CHECK(normalizedRot(360.0f) == pi / 2.0f);

	CHECK(normalizedRot(45.0f) == pi / 4.0f);
}

#endif