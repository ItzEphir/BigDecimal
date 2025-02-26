//
// Created by ephir on 20.02.2025.
//

#include <gtest/gtest.h>
#include "../include/StringHelper.h"

namespace ephir::bigdecimal {
    class StringHelperTests : public testing::Test {};

    TEST_F(StringHelperTests, ContainsOnlyDigitsWithDigits) {
        const auto given = "123456789";
        constexpr auto expected = true;
        const auto actual = StringHelper::containsOnlyDigit(given);
        ASSERT_EQ(expected, actual);
    }

    TEST_F(StringHelperTests, ContaintsOnlyDigitsWithAlphas) {
        const auto given = "a123456789";
        constexpr auto expected = false;
        const auto actual = StringHelper::containsOnlyDigit(given);
        ASSERT_EQ(expected, actual);
    }

    TEST_F(StringHelperTests, ContainsOnlyDigitsWithNegative) {
        const auto given = "-123456789";
        constexpr auto expected = true;
        const auto actual = StringHelper::containsOnlyDigit(given);
        ASSERT_EQ(expected, actual);
    }

    TEST_F(StringHelperTests, ContainsOnlyDigitsWithPoint) {
        const auto given = "123456789.1";
        constexpr auto expected = true;
        const auto actual = StringHelper::containsOnlyDigit(given);
        ASSERT_EQ(expected, actual);
    }

    TEST_F(StringHelperTests, ContainsOnlyDigitsWithTwoPoints) {
        const auto given = "123456789.123456789.12133";
        constexpr auto expected = false;
        const auto actual = StringHelper::containsOnlyDigit(given);
        ASSERT_EQ(expected, actual);
    }

    TEST_F(StringHelperTests, Split) {
        const auto given = "12345.123.23";
        const std::vector<std::string_view> expected = {"12345", "123", "23"};
        const auto actual = StringHelper::split(given, '.');
        ASSERT_EQ(expected, actual);
    }
} // ephir::bigdecimal
