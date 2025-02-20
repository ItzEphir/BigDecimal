//
// Created by ephir on 20.02.2025.
//

#include <gtest/gtest.h>
#include "../include/BigDecimal.h"
#include <vector>

namespace ephir::bigdecimal {
    TEST(BIG_DECIMAL, CreateByString) {
        const auto given = "3";
        auto expected = BigDecimal();
        expected.get_raw() = {true, true};
        const auto actual = BigDecimal::create(given);
        ASSERT_EQ(expected, actual);
    }

    TEST(BIG_DECIMAL, CreateByStringWithTrailingZeros) {
        const auto given = "12";
        auto expected = BigDecimal();
        expected.get_raw() = {true, true};
        expected.set_exp(2);
        const auto actual = BigDecimal::create(given);
        ASSERT_EQ(expected, actual);
    }

    TEST(BIG_DECIMAL, CreateByStringFloatingPoint) {
        const auto given = "12.25";
        auto expected = BigDecimal();
        expected.get_raw() = {true, true, false, false, false, true};
        expected.set_exp(-2);
        const auto actual = BigDecimal::create(given);
        ASSERT_EQ(expected, actual);
    }
} // ephir::bigdecimal
