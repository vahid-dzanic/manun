#include "manun/convert.h"

#include <functional>
#include <iostream>

int main(int argc, char* argv[])
{
  (void)argc;
  (void)argv;

  //  std::deque<int> vec(5, 0);
  //  for (decltype(vec.size()) i = 0; i < vec.size(); ++i)
  //  {
  //    vec[i] = i;
  //  }
  //  std::string txt = "deque<I32>={{0}{1}{2}{";

  //  auto vecStr = chili::manun::Convert::toString(vec);
  //  auto strStr = chili::manun::Convert::toString(txt);
  //  std::cout << vecStr << "\n\n";

  //  //...

  //  std::function<void(decltype(vec), decltype(txt))> func = std::bind(&foo, std::placeholders::_1,
  //  std::placeholders::_2); std::function<void(decltype(vec), decltype(txt))> func2 = std::bind(&fuu,
  //  std::placeholders::_1, std::placeholders::_2);

  //  func(chili::manun::Convert::toValue(vecStr), chili::manun::Convert::toValue(strStr));

  return 0;
}

////#include "Convert.h"

////#include <string>
////#include <type_traits>
////#include <typeinfo>
////#include <iostream>
////#include <functional>

////void foo(float value)
////{
////  std::cout << value << std::endl;
////}

//// For any dynamic stuff (names or payload) which are not part of the protocol use ASCII STX ('\x02') as prefix and
///ETX ('\x03') as postfix.

////<func name="\x02...\x03"></func>
////<args count="."></args>
////<built>/<enum>/<array>/<struct>/<user>
////  attributes: type="\x02...\x03" value="\x02...\x03"
////  <struct>
////    <members count="."></members>
////      <built>/<enum>/<array>/<struct>/<user>

//// keep in mind that a struct which has a member on it self wouldn't work. use for that <user>

////<func name="\x02 addIntAndFloat \x03">
////  <arg type="primitive/enum/class" typename="\x02 UI32 \x03" value="\x02 42 \x03"/>
////  <arg type="\x02 F32 \x03">
////    \x02 42.42 \x03
////  </arg>
////</func>

////<class>
////  <arg type="\x02 UI32 \x03">
////    \x02 42 \x03
////  </arg>
////  <arg type="\x02 MYSuperClass \x03">
////    <class>
////      <arg type="\x02 F32 \x03">
////        \x02 42.42 \x03
////      </arg>
////    </class>
////  </arg>
////</class>

//#include "StandardTypeConverter.h"
//#include <iostream>

// class TestClassA
//{
// public:
//  static TestClassA string2value(const std::string& txt)
//  {
//    auto sub = txt.substr(1, txt.size()-2);
//    TestClassA a;
//    a.abc = chili::manun::std_t::string2value<std::uint16_t>(sub);
//    return a;
//  }
//  static std::string value2string(const TestClassA& value)
//  {
//    std::string retVal("{");
//    retVal.append(chili::manun::std_t::value2string(value.abc));
//    retVal.append("}");
//    return retVal;
//  }

//  TestClassA()
//    : abc(0)
//  {

//  }
//  TestClassA(const TestClassA& rhs)
//    : abc(rhs.abc)
//  {

//  }

//  TestClassA(std::uint16_t value)
//    : abc(value)
//  {

//  }

//  std::uint16_t abc;
//};

// void registerConverter()
//{
//  chili::manun::ConverterFactory::add<TestClassA>(std::bind(&TestClassA::string2value, std::placeholders::_1),
//                                                  std::bind(&TestClassA::value2string, std::placeholders::_1));
//  chili::manun::TypeNameMap::add<TestClassA>("TestClassA");
//}

//#include "Convert.h"

// int main(int argc, char *argv[])
//{
//  //Teststdex::doTest();

//  std::string abc("abcdefghijklmnop");

//  std::string tr = chili::manun::Convert::toString(abc);
//  std::cout << tr << std::endl << std::endl;
//  decltype(abc) x = chili::manun::std_t::string2value<decltype(abc)>(tr);
//  std::cout << x << std::endl;

//  registerConverter();
//  std::map<int,TestClassA> a;
//  a.insert(std::make_pair(1, TestClassA(1)));
//  a.insert(std::make_pair(2, TestClassA(2)));
//  a.insert(std::make_pair(3, TestClassA(3)));
//  a.insert(std::make_pair(4, TestClassA(4)));

////  std::map<int,float> a;
////  a.insert(std::make_pair(1, 1));
////  a.insert(std::make_pair(2, 2));
////  a.insert(std::make_pair(3, 3));
////  a.insert(std::make_pair(4, 4));

//  std::string l1 = chili::manun::std_t::value2string(a);
//  std::cout << l1 << std::endl;

//  decltype(a) b = chili::manun::std_t::string2value<decltype(a)>(l1);

//  std::cout << std::endl;

//  std::string l2 = chili::manun::std_t::value2string(b);
//  std::cout << l2 << std::endl;

////  return 0;

//  std::vector<std::vector<std::uint64_t>> vec(5, std::vector<std::uint64_t>(5,0));
//  for (std::size_t i = 0; i < vec.size(); ++i)
//  {
//    for (std::size_t e = 0; e < vec[i].size(); ++e)
//    {
//      vec[i][e] = i + (i * e) + e;
//    }
//  }
//  std::string txt = chili::manun::std_t::value2string(vec);
//  std::cout << txt << std::endl;

//  std::vector<std::vector<std::uint64_t>> vec2 =
//  chili::manun::std_t::string2value<std::vector<std::vector<std::uint64_t>>>(txt); for (std::size_t i = 0; i <
//  vec.size(); ++i)
//  {
//    for (std::size_t e = 0; e < vec[i].size(); ++e)
//    {
//      if (vec[i][e] != vec2[i][e])
//      {
//        std::cout << "not same --> " << vec[i][e] << " != " << vec2[i][e] << std::endl;
//      }
//    }
//  }

//  //  auto sub = txt.substr(1, txt.size()-2);
//  //  std::cout << sub << std::endl;

//  //  for(auto val : groups(txt))
//  //  {
//  //    std::cout << val << std::endl;
//  //  }

//  //#warning TODO: using YAML as data serialization format.
//  //#warning TODO: using JSON as data serialization format.
//  //#warning TODO: using XML as data serialization format.

//  (void)argc;
//  (void)argv;
//  //  std::uint16_t val0 = 15;
//  //  std::string txt0 = chili::Convert::toString(val0);
//  //  std::uint16_t val1 = chili::Convert::toValue(txt0);
//  //  std::cout << val0 << " == " << txt0 << " == " << val1 << std::endl;

//  //  //use explicitly std::function<...(....)>,  do not use auto !!
//  //  //auto func = std::bind(foo, std::placeholders::_1);  // <-- this would not work later on Convert::toValue()
//  //  std::function<void(float)> func = std::bind(foo, std::placeholders::_1);
//  //  func(15);
//  //  float val2 = 15.1;
//  //  std::string txt2 = chili::Convert::toString(val2);
//  //  func(chili::Convert::toValue(txt2));

//  //  std::vector<uint16_t> values({11,22,33,44,55});
//  ////  std::string txt4(chili::VectorConverter<uint16_t>::toString(values));
//  ////  std::cout << txt4 << std::endl;

//  ////  std::vector<uint16_t> values2 = chili::VectorConverter<uint16_t>::toValue(txt4);
//  ////  for (auto value : values2)
//  ////  {
//  ////    std::cout << value << std::endl;
//  ////  }
//  //  chili::registerConverter();
//  //  std::string txt5(chili::Convert::toString(values));
//  //  std::cout << txt5 << std::endl;
//  //  std::vector<uint16_t> values2 = chili::Convert::toValue(txt5);
//  //  for (auto value : values2)
//  //  {
//  //    std::cout << value << std::endl;
//  //  }

//  return 0;
//}
