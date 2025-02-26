//
// Created by ephir on 26.02.2025.
//

#include <gtest/gtest.h>

#include "../include/Maths.h"

namespace ephir::bigdecimal::maths {
    class MathsTests : public testing::Test {};

    TEST_F(MathsTests, TestLogTwos) {
        constexpr auto given = 128ull;
        constexpr auto expected = 7ll;
        const auto actual = fast_log2(given);
        ASSERT_EQ(expected, actual);
    }
}
