#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <manun/convert.h>
#include <manun/function_map.h>
#include <stdex/tuple_ex.h>

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

void foo(std::list<std::uint32_t> data)
{
  std::cout << "--------------------------------------------\n";
  std::cout << "function call: " << __PRETTY_FUNCTION__ << "  data argument size: " << data.size() << "\n";
  //  for (decltype(data.size()) i = 0; i < data.size(); ++i)
  //  {
  //    std::cout << "value " << i << ": " << data[i] << "\n";
  //  }
  for (auto val : data)
  {
    std::cout << "value "
              << ": " << val << "\n";
  }
  std::cout << std::endl;
}

TEST(test_manun_func, test_simple_function_call)
{
  manun::function_map fmap;
  auto f1 = stdex_create(foo);
  fmap.add(f1);

  std::list<std::uint32_t> data(9, 42);
  std::cout << manun::convert::func::toString(f1.name(), data);
  fmap.execute(manun::convert::func::toString(f1.name(), data));
}

namespace def {
void func1(std::int32_t a) { std::cout << a << std::endl; }
void func2(double a) { std::cout << a << std::endl; }
void func3(std::uint32_t a) { std::cout << a << std::endl; }
void func4(std::string a, std::uint32_t b, double c)
{
  std::cout << a << " " << b << " " << c << std::endl;
  std::cout << manun::convert::func::toString(__PRETTY_FUNCTION__, a, b, c) << std::endl;
}
} // namespace def

namespace abc { namespace def {
void func3(std::uint32_t a) { std::cout << manun::convert::func::toString(__PRETTY_FUNCTION__, a) << std::endl; }
}} // namespace abc::def

struct ABC
{
  void func5(std::string a, std::uint32_t b, double c)
  {
    std::cout << a << " " << b << " " << c << std::endl;
    std::cout << manun::convert::func::toString(__PRETTY_FUNCTION__, a, b, c) << std::endl;
  }
  void func7()
  {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    std::cout << manun::convert::func::toString(__PRETTY_FUNCTION__) << std::endl;
  }
};

void func6()
{
  std::cout << " VOID " << std::endl;
  std::cout << manun::convert::func::toString(__PRETTY_FUNCTION__) << std::endl;
}

// TEST(test_manun_func, test1)
//{
//  std::cout << std::endl;
//  std::cout << std::endl;

////  std::cout << std::boolalpha << stdex::traits::is_tuple<std::tuple<int, double>>::value << std::endl;
////  std::cout << std::boolalpha << stdex::traits::is_tuple<A>::value << std::endl;
////  std::cout << std::boolalpha << (stdex::traits::array_size<std::array<int, 17>>::value == 17) << std::endl;
////  std::cout << std::boolalpha << (stdex::traits::array_size<A>::value == 0) << std::endl;

//  manun::function_map map;

//  std::function<void(std::int32_t)> fA = std::bind(def::func1, std::placeholders::_1);
//  std::function<void(double)> fB = std::bind(def::func2, std::placeholders::_1);
//  std::function<void(std::uint32_t)> fC = std::bind(def::func3, std::placeholders::_1);
//  std::function<void(std::string, std::uint32_t, double)> fD = std::bind(def::func4, std::placeholders::_1,
//  std::placeholders::_2, std::placeholders::_3); map.add(std::string("def::func1"), fA);
//  map.add(std::string("def::func2"), fB);
//  map.add(std::string("def::func3"), fC);
//  map.add(std::string("def::func4"), fD);

//  map.execute("{def::func3(UI32)({UI32=2A})}");
//  map.execute("{def::func4(STR,UI32,F64)({STR=abcdefgahlkasjdf}{UI32=2a}{F64=3fd41b2f769cf0e0})}");
//}

// TEST(test_manun_func, test1)
//{
//  std::cout << std::endl;
//  std::cout << std::endl;

//  manun::function_map map;

//  ABC* a = new ABC();

//  auto fA = stdex_create(def::func1);
//  map.add(fA);
//  auto fB = stdex_create(def::func2);
//  map.add(fB);
//  auto fC = stdex_create(def::func3);
//  map.add(fC);
//  auto fD = stdex_create(def::func4);
//  map.add(fD);
//  map.add(stdex_bind(&ABC::func5, a, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
//  map.add(stdex_create(func6));
//  map.add(stdex_create(&ABC::func7, a));

//  map.execute(manun::convert::func::toString(fC.name(), static_cast<std::uint32_t>(3)));

////  map.execute("{def::func3(UI32)({UI32=2A})}");
////  map.execute("{def::func4(STR,UI32,F64)({STR=abcdefgahlkasjdf}{UI32=2a}{F64=3fd41b2f769cf0e0})}");
////  map.execute("{ABC::func5(STR,UI32,F64)({STR=abcdefgahlkasjdf}{UI32=2a}{F64=3fd41b2f769cf0e0})}");
////  map.execute("{func6()}");
////  map.execute("{ABC::func7()}");

////  fD(std::make_tuple(std::string("hallo du"), std::uint32_t(1), double(2)));
//}
TEST(test_manun_func, test1)
{
  std::cout << std::endl;
  std::cout << std::endl;

  manun::function_map map;

  ABC* a = new ABC();

  int abc = 15;
  int* cdf = &abc;

  delete cdf;

  auto fA = stdex_create(def::func1);
  map.add(fA);
  auto fB = stdex_create(def::func2);
  map.add(fB);
  auto fC = stdex_create(def::func3);
  map.add(fC);
  auto fD = stdex_create(def::func4);
  map.add(fD);
  map.add(stdex_bind(&ABC::func5, a, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
  map.add(stdex_create(func6));
  map.add(stdex_create(&ABC::func7, a));

  map.execute("{def::func3(UI32)({UI32=2A})}");
  map.execute("{def::func4(STR,UI32,F64)({STR=abcdefgahlkasjdf}{UI32=2a}{F64=3fd41b2f769cf0e0})}");
  map.execute("{ABC::func5(STR,UI32,F64)({STR=abcdefgahlkasjdf}{UI32=2a}{F64=3fd41b2f769cf0e0})}");
  map.execute("{func6()}");
  map.execute("{ABC::func7()}");

  std::string jdjdjd =
    manun::convert::toString(std::make_tuple(std::string("hallo du"), std::uint32_t(1), double(2)));

  fD(manun::convert::toValue(jdjdjd));
  fD(manun::convert::toValue("{STR=abcdefgahlkasjdf}"),
     manun::convert::toValue("{UI32=2a}"),
     manun::convert::toValue("{F64=3fd41b2f769cf0e0}"));
  fD(manun::convert::toValue("{STR=abcdefgahlkasjdf}"),
     manun::convert::toValue("{F64=3fd41b2f769cf0e0}"),
     manun::convert::toValue("{UI32=2a}"));
  std::cout << "----------------------------------------------------------------------------------------------"
            << std::endl;
}
