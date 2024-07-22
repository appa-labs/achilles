#include <catch2/catch_test_macros.hpp>
#include <cmath>

#include "src/core/tools/tools.h"

#define math_abs(x) std::abs(x)

const static inline float kEps = 1e-6;

bool FloatEqual(float a, float b) {
    return math_abs(a - b) <= kEps;
}

bool VecEqual(const Vector2f& a, const Vector2f& b) {
    return FloatEqual(a.x, b.x) && FloatEqual(a.y, b.y);
}

TEST_CASE("Projection simple") {
    auto result_vec = Projection(Vector2f{3.f, -8.f}, Vector2f{1.f, 2.f});
    REQUIRE(VecEqual(result_vec, Vector2f{-2.6f, -5.2f}));
}
