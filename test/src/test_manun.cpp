#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <manun/convert.h>

// This file is part of manun library, manun is a marshalling / unmarshalling library,
// which requires only a C++17 compatible compiler.
//
// Copyright (C) 2019 Vahid Dzanic <vdc@gmx.ch>
//
// manun is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 3 of the License, or (at your option) any later version.
//
// Alternatively, you can redistribute it and/or
// modify it under the terms of the GNU General Public License as
// published by the Free Software Foundation; either version 2 of
// the License, or (at your option) any later version.
//
// manun is distributed in the hope that it will be useful, but WITHOUT ANY
// WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
// FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License or the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License and a copy of the GNU General Public License along with
// manun. If not, see <http://www.gnu.org/licenses/>.

template<typename _Tp>
class test_fixture_convert1 : public ::testing::Test
{};
template<typename _Tp>
class test_fixture_convert2 : public ::testing::Test
{};

typedef ::testing::Types<bool,
                         char,
                         //wchar_t
                         char16_t,
                         char32_t,
                         float,
                         double,
                         long long,
                         unsigned long long,
                         std::int8_t,
                         std::int16_t,
                         std::int32_t,
                         std::int64_t,
                         std::uint8_t,
                         std::uint16_t,
                         std::uint32_t,
                         std::uint64_t,
                         std::string,
                         std::array<char, 1>,
                         std::vector<char>,
                         std::deque<char>,
                         std::forward_list<char>,
                         std::list<char>,
                         std::stack<char>,
                         std::queue<char>,
                         std::priority_queue<char>,
                         std::set<char>,
                         std::multiset<char>,
                         std::unordered_set<char>,
                         std::unordered_multiset<char>,
                         std::map<char, char>,
                         std::multimap<char, char>,
                         std::unordered_map<char, char>,
                         std::unordered_multimap<char, char>,
                         std::pair<char, char>,
                         std::tuple<char, std::string, int>>
  builtin_and_std_types;

typedef ::testing::Types<bool,
                         char,
                         //wchar_t
                         char16_t,
                         char32_t,
                         float,
                         double,
                         long long,
                         unsigned long long,
                         std::int8_t,
                         std::int16_t,
                         std::int32_t,
                         std::int64_t,
                         std::uint8_t,
                         std::uint16_t,
                         std::uint32_t,
                         std::uint64_t>
  builtin;

TYPED_TEST_CASE(test_fixture_convert1, builtin_and_std_types);
TYPED_TEST_CASE(test_fixture_convert2, builtin);

TYPED_TEST(test_fixture_convert1, test_convert_to_string)
{
  TypeParam param;
  auto str = manun::convert::to_string(param);
  (void)str;
}

TYPED_TEST(test_fixture_convert1, test_convert_to_string_and_to_value)
{
  TypeParam param;
  auto str = manun::convert::to_string(param);
  TypeParam paramRet = manun::convert::to_value(str);
  (void)paramRet;
}

TYPED_TEST(test_fixture_convert2, test_convert_builtin_to_string)
{
  TypeParam param = 17;
  auto str = manun::convert::to_string(param);
  (void)str;
}

TYPED_TEST(test_fixture_convert2, test_convert_builtin_to_string_and_to_value)
{
  TypeParam min = std::numeric_limits<TypeParam>::min();
  auto str = manun::convert::to_string(min);
  TypeParam ret = manun::convert::to_value(str);
  EXPECT_EQ(min, ret);

  min += 1;
  str = manun::convert::to_string(min);
  ret = manun::convert::to_value(str);
  EXPECT_EQ(min, ret);

  min -= 2;
  str = manun::convert::to_string(min);
  ret = manun::convert::to_value(str);
  EXPECT_EQ(min, ret);

  TypeParam max = std::numeric_limits<TypeParam>::max();
  str = manun::convert::to_string(max);
  ret = manun::convert::to_value(str);
  EXPECT_EQ(max, ret);

  max += 1;
  str = manun::convert::to_string(max);
  ret = manun::convert::to_value(str);
  EXPECT_EQ(max, ret);

  max -= 2;
  str = manun::convert::to_string(max);
  ret = manun::convert::to_value(str);
  EXPECT_EQ(max, ret);

  TypeParam null = 0;
  str = manun::convert::to_string(null);
  ret = manun::convert::to_value(str);
  EXPECT_EQ(null, ret);

  null += 1;
  str = manun::convert::to_string(null);
  ret = manun::convert::to_value(str);
  EXPECT_EQ(null, ret);

  null -= 2;
  str = manun::convert::to_string(null);
  ret = manun::convert::to_value(str);
  EXPECT_EQ(null, ret);

  auto min1 = std::numeric_limits<TypeParam>::min();
  auto max1 = std::numeric_limits<TypeParam>::max() - (std::numeric_limits<TypeParam>::max() / 15.0);
  auto delta = std::numeric_limits<TypeParam>::max() / 16.0;
  for (TypeParam i = min1; i < max1; i += delta)
  {
    auto str = manun::convert::to_string(i);
    TypeParam paramRet = manun::convert::to_value(str);
    EXPECT_EQ(i, paramRet);
  }
}

TEST(test_toStr, text_std_string_to_string)
{
  std::string param;
  auto actual = manun::convert::to_string(param);
  std::string expected("{STR=}");
  EXPECT_EQ(expected, actual);
}

// long double not supported
// TEST(test_toStr, text_longdouble_to_string)
//{
//  long double param = 3.14;
//  auto actual = manun::convert::to_string(param);
//  std::string expected("{F96=3.14}");
//  EXPECT_EQ(expected, actual);
//}

TEST(test_manun, marshalling_and_unmarshalling_with_vector_of_int32)
{
  std::vector<std::int32_t> vec(10, 0);
  for (auto i = 0u; i < vec.size(); ++i)
  {
    vec[i] = static_cast<std::int32_t>(i);
  }
  std::string marshalled = manun::convert::to_string(vec);
  std::vector<std::int32_t> unmarshalled = manun::convert::to_value(marshalled);

  for (std::size_t i = 0; i < unmarshalled.size(); ++i)
  {
    EXPECT_EQ(vec[i], unmarshalled[i]);
  }
}

class TstClass
{
public:
  TstClass()
    : member1(42)
    , member2(std::numeric_limits<std::int32_t>::max())
    , member3(0.0000000000000003)
  {}
  static void register_converter()
  {
    manun::converter_factory::add<TstClass*>("TstClass*", TstClass::string2value, TstClass::value2string);
  }
  static std::string value2string(const TstClass* tstclass)
  {
    return std::string(manun::convert::to_string(tstclass->member1) + manun::convert::to_string(tstclass->member2) +
                       manun::convert::to_string(tstclass->member3));
  }
  static TstClass* string2value(const std::vector<std::string>& vec)
  {
    TstClass* retVal = new TstClass();
    retVal->member1 = manun::convert::to_value(vec[0]);
    retVal->member2 = manun::convert::to_value(vec[1]);
    retVal->member3 = manun::convert::to_value(vec[2]);
    return retVal;
  }

  bool isSame(const TstClass& rhs)
  {
    return (member1 == rhs.member1 && member2 == rhs.member2 && member3 <= rhs.member3 + 0.0000000000000001 &&
            member3 >= rhs.member3 - 0.0000000000000001);
  }

private:
  std::int32_t member1;
  std::int32_t member2;
  double member3;
};

TEST(test_converter_factory, text_TstClass_to_string)
{
  TstClass::register_converter();
  TstClass* ptr1 = new TstClass();

  auto str = manun::convert::to_string(ptr1);
  //  std::cout << str << std::endl;

  TstClass* ptr2 = manun::convert::to_value(str);

  EXPECT_TRUE(ptr1->isSame(*ptr2));

  delete ptr1;
  delete ptr2;
}

TEST(test_converter_factory, text_TstClass_nullptr_to_string)
{
  TstClass* ptr1 = nullptr;

  auto str = manun::convert::to_string(ptr1);
  //  std::cout << str << std::endl;

  TstClass* ptr2 = manun::convert::to_value(str);

  EXPECT_EQ(nullptr, ptr1);
  EXPECT_EQ(nullptr, ptr2);
}

// nullptr is not supported
// TEST(test_converter_factory, text_nullptr_to_string)
//{
//  manun::convert::to_string(nullptr);
//}
