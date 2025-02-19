//
// Created by ephir on 20.02.2025.
//

#include <gtest/gtest.h>
#include "../include/StringHelper.h"

namespace ephir::bigdecimal {
    TEST(STRING_HELPER, ContainsOnlyDigitsWithDigits) {
        const auto given = "123456789";
        constexpr auto expected = true;
        const auto actual = StringHelper::containsOnlyDigit(given);
        ASSERT_EQ(expected, actual);
    }

    TEST(STRING_HELPER, ContaintsOnlyDigitsWithAlphas) {
        const auto given = "a123456789";
        constexpr auto expected = false;
        const auto actual = StringHelper::containsOnlyDigit(given);
        ASSERT_EQ(expected, actual);
    }

    TEST(STRING_HELPER, ContainsOnlyDigitsWithNegative) {
        const auto given = "-123456789";
        constexpr auto expected = true;
        const auto actual = StringHelper::containsOnlyDigit(given);
        ASSERT_EQ(expected, actual);
    }

    TEST(STRING_HELPER, ContainsOnlyDigitsWithPoint) {
        const auto given = "123456789.1";
        constexpr auto expected = true;
        const auto actual = StringHelper::containsOnlyDigit(given);
        ASSERT_EQ(expected, actual);
    }

    TEST(STRING_HELPER, ContainsOnlyDigitsWithTwoPoints) {
        const auto given = "123456789.123456789.12133";
        constexpr auto expected = false;
        const auto actual = StringHelper::containsOnlyDigit(given);
        ASSERT_EQ(expected, actual);
    }
} // ephir::bigdecimal
