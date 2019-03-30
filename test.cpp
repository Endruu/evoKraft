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

TEST_CASE("absoluteRotation")
{
    static const auto pi = std::atan(1.0f) * 4.0f;
    GameObject go{};

    CHECK(absoluteRotation(go, 1.0f, 0.0f) == 0.0f);
    CHECK(absoluteRotation(go, 1.0f, 1.0f) == pi / 4.0f);
    CHECK(absoluteRotation(go, 0.0f, 1.0f) == pi / 2.0f);
}

TEST_CASE("distanceFromLine")
{

	CHECK(std::isnan(distanceFromLine(Line(0.0f, 0.0f, 0.0f, 0.0f), 0.0f, 0.0f)));
	CHECK(distanceFromLine(Line(0.0f, 0.0f, 10.0f, 0.0f), 5.0f, 0.0f) == 0.0f);
	CHECK(distanceFromLine(Line(0.0f, 0.0f, 10.0f, 0.0f), 5.0f, 5.0f) == 5.0f);
	CHECK(distanceFromLine(Line(0.0f, 0.0f, 10.0f, 0.0f), 5.0f, 15.0f) == 15.0f);
	CHECK(distanceFromLine(Line(0.0f, 5.0f, 10.0f, 5.0f), 5.0f, 15.0f) == 10.0f);
	CHECK(distanceFromLine(Line(0.0f, -5.0f, -10.0f, -5.0f), -5.0f, -15.0f) == 10.0f);
	CHECK(distanceFromLine(Line(0.0f, 5.0f, 10.0f, 5.0f), 7.0f, 0.0f) == 5.0f);
	CHECK(distanceFromLine(Line(0.0f, 0.0f, 10.0f, 10.0f), 10.0f, 0.0f) == 5.0f*sqrt(2.0f));
	CHECK(distanceFromLine(Line(0.0f, 0.0f, 10.0f, 10.0f), 20.0f, 20.0f) == 0.0f);
}

#endif