#ifndef PARSETEST_HPP
#define PARSETEST_HPP

#include <string>
#include <gtest/gtest.h>

template <typename T>
class ParseTest : public testing::TestWithParam<std::tuple<std::string, T>>
{
};

#endif // PARSETEST_HPP
