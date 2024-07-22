#include <catch2/catch_test_macros.hpp>
#include <cmath>

#include "src/core/tools/tools.h"


bool FloatEqual(float a, float b) {
    return math_abs(a - b) <= kEps;
}

TEST_CASE("Projection simple") {
    auto result_vec = Projection(Vector2f{3.f, -8.f}, Vector2f{1.f, 2.f});
    REQUIRE(result_vec == Vector2f{-2.6f, -5.2f});
}
