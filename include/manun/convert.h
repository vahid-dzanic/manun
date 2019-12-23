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

namespace manun::convert {

template<typename _Tp>
std::string to_string(const _Tp& value)
{
  static_assert_by_type<_Tp>();
  return convert_proxy::value2string<_Tp>(value);
}

class to_value
{
public:
  to_value(const std::string& text)
    : text_(text)
  {}
  to_value(std::string&& text)
    : text_(std::move(text))
  {}
  to_value() = delete; //! No default-constructor
  to_value(const to_value&) = delete; //! No copy-constructor
  to_value& operator=(const to_value&) = delete; //! No copy-assignment operator
  void* operator new(std::size_t) = delete; //! No create on the heap
  void* operator new[](std::size_t) = delete; //! No create on the heap
  to_value* operator&() = delete; //! No pointer alias
  const to_value* operator&() const = delete; //! No const pointer alias

  template<typename _Tp>
  operator _Tp()
  {
    static_assert_by_type<_Tp>();
    return convert_proxy::string2value<_Tp>(text_);
  }

private:
  const std::string& text_;
};

class func
{
public:
  static std::string to_string(const std::string& pretty_function)
  {
    std::string ret_val("{");
    std::size_t end_pos = pretty_function.find('(');
    if (end_pos != std::string::npos)
    {
      std::string temp = pretty_function.substr(0, end_pos);
      stdex::replace(temp, "*", " ");
      stdex::replace(temp, "&", " ");
      ret_val += stdex::split(temp, " ").back();
    }
    else
    {
      ret_val += pretty_function;
    }
    ret_val += "()";
    ret_val.push_back('}');
    return ret_val;
  }

  template<typename... _Args>
  static std::string to_string(const std::string& pretty_function, _Args... __args)
  {
    std::string ret_val("{");
    std::size_t end_pos = pretty_function.find('(');
    if (end_pos != std::string::npos)
    {
      std::string temp = pretty_function.substr(0, end_pos);
      stdex::replace(temp, "*", " ");
      stdex::replace(temp, "&", " ");
      ret_val += stdex::split(temp, " ").back();
    }
    else
    {
      ret_val += pretty_function;
    }
    auto tpl = std::make_tuple(__args...);
    ret_val.push_back('(');
    ret_val += types(tpl);
    ret_val += ")(";
    ret_val += types_with_value(tpl);
    ret_val.push_back(')');
    ret_val.push_back('}');
    return ret_val;
  }

private:
  template<typename _Tpl>
  static std::string types(const _Tpl& arguments)
  {
    std::string ret_val;
    for (const auto& val : tuple2array_impl<_Tpl>(arguments, false, std::make_index_sequence<std::tuple_size<_Tpl>::value>()))
    {
      ret_val += val;
    }
    ret_val.pop_back();
    return ret_val;
  }
  template<typename _Tpl>
  static std::string types_with_value(const _Tpl& arguments)
  {
    std::string ret_val;
    for (const auto& val : tuple2array_impl<_Tpl>(arguments, true, std::make_index_sequence<std::tuple_size<_Tpl>::value>()))
    {
      ret_val += val;
    }
    return ret_val;
  }
  template<typename _Tpl, std::size_t... _I>
  static std::array<std::string, std::tuple_size<_Tpl>::value> tuple2array_impl(const _Tpl& tpl,
                                                                                bool with_value,
                                                                                std::index_sequence<_I...>)
  {
    if (with_value)
    {
      return std::array<std::string, std::tuple_size<_Tpl>::value> {{convert::to_string(std::get<_I>(tpl))...}};
    }
    else
    {
      return std::array<std::string, std::tuple_size<_Tpl>::value> {
        {(type_name_map::name<typename std::tuple_element<_I, _Tpl>::type>() + ",")...}};
    }
  }
};
} // namespace manun::convert
