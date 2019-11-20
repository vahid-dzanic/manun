#pragma once

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

#include "convert_proxy.h"

#include <tuple>
#include <utility>

namespace chili::manun::convert {

template<typename TYP>
std::string toString(const TYP& value)
{
  static_assert_by_type<TYP>();
  return convert_proxy::value2string<TYP>(value);
}

class toValue
{
public:
  toValue(const std::string& text)
    : mText(text)
  {}
  toValue() = delete; //! No default-constructor
  toValue(const toValue&) = delete; //! No copy-constructor
  toValue& operator=(const toValue&) = delete; //! No copy-assignment operator
  void* operator new(std::size_t) = delete; //! No create on the heap
  void* operator new[](std::size_t) = delete; //! No create on the heap
  toValue* operator&() = delete; //! No pointer alias
  const toValue* operator&() const = delete; //! No const pointer alias
  //  toValue(std::string&& text)
  //    : mText(std::move(text))
  //  {
  //  }

  template<typename TYP>
  operator TYP()
  {
    static_assert_by_type<TYP>();
    return convert_proxy::string2value<TYP>(mText);
  }

private:
  const std::string& mText;
};

class func
{
public:
  static std::string toString(const std::string& pretty_function)
  {
    std::string retVal("{");
    std::size_t end_pos = pretty_function.find('(');
    if (end_pos != std::string::npos)
    {
      std::string temp = pretty_function.substr(0, end_pos);
      chili::stdex::replace(temp, "*", " ");
      chili::stdex::replace(temp, "&", " ");
      retVal += chili::stdex::split(temp, " ").back();
    }
    else
    {
      retVal += pretty_function;
    }
    retVal += "()";
    retVal.push_back('}');
    return retVal;
  }

  template<typename... _Args>
  static std::string toString(const std::string& pretty_function, _Args... __args)
  {
    std::string retVal("{");
    std::size_t end_pos = pretty_function.find('(');
    if (end_pos != std::string::npos)
    {
      std::string temp = pretty_function.substr(0, end_pos);
      chili::stdex::replace(temp, "*", " ");
      chili::stdex::replace(temp, "&", " ");
      retVal += chili::stdex::split(temp, " ").back();
    }
    else
    {
      retVal += pretty_function;
    }
    auto tpl = std::make_tuple(__args...);
    retVal.push_back('(');
    retVal += types(tpl);
    retVal += ")(";
    retVal += types_with_value(tpl);
    retVal.push_back(')');
    retVal.push_back('}');
    return retVal;
  }

private:
  template<typename _Tpl>
  static std::string types(const _Tpl& arguments)
  {
    std::string retVal;
    for (auto val : tuple2array_impl<_Tpl>(arguments, false, std::make_index_sequence<std::tuple_size<_Tpl>::value>()))
    {
      retVal += val;
    }
    retVal.pop_back();
    return retVal;
  }
  template<typename _Tpl>
  static std::string types_with_value(const _Tpl& arguments)
  {
    std::string retVal;
    for (auto val : tuple2array_impl<_Tpl>(arguments, true, std::make_index_sequence<std::tuple_size<_Tpl>::value>()))
    {
      retVal += val;
    }
    return retVal;
  }
  template<typename _Tpl, std::size_t... _I>
  static std::array<std::string, std::tuple_size<_Tpl>::value> tuple2array_impl(const _Tpl& tpl,
                                                                                bool with_value,
                                                                                std::index_sequence<_I...>)
  {
    if (with_value)
    {
      return std::array<std::string, std::tuple_size<_Tpl>::value>{{convert::toString(std::get<_I>(tpl))...}};
    }
    else
    {
      return std::array<std::string, std::tuple_size<_Tpl>::value>{
        {(type_name_map::name<typename std::tuple_element<_I, _Tpl>::type>() + ",")...}};
    }
  }
};
} // namespace chili::manun::convert
