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

#include "std_type_converter.h"

namespace chili::manun {
class convert_proxy
{
public:
  template<typename TYP>
  static std::string value2string(const TYP& value,
                                  typename std::enable_if<stdex::traits::is_std_type<TYP>::value>::type* = nullptr)
  {
    return std_type_converter::value2string(value);
  }
  template<typename TYP>
  static std::string value2string(const TYP& value, typename std::enable_if<std::is_enum<TYP>::value>::type* = nullptr)
  {
    return std::string("{" + type_name_map::name<TYP>() + "=" + std::to_string(static_cast<std::int64_t>(value)) + "}");
  }
  template<typename TYP>
  static std::string value2string(
    const TYP& value,
    typename std::enable_if<not(stdex::traits::is_std_type<TYP>::value || std::is_enum<TYP>::value)>::type* = nullptr)
  {
    return converter_factory::value2string(value);
  }

  template<typename TYP, typename std::enable_if<stdex::traits::is_std_type<TYP>::value>::type* = nullptr>
  static TYP string2value(const std::string& txt)
  {
    return std_type_converter::string2value<TYP>(txt);
  }
  template<typename TYP, typename std::enable_if<std::is_enum<TYP>::value>::type* = nullptr>
  static TYP string2value(const std::string& txt)
  {
    return static_cast<TYP>(std::stoll(extractContent<TYP>(txt.substr(1, txt.size() - 2))));
  }
  template<
    typename TYP,
    typename std::enable_if<not(stdex::traits::is_std_type<TYP>::value || std::is_enum<TYP>::value)>::type* = nullptr>
  static TYP string2value(const std::string& txt)
  {
    return converter_factory::string2value<TYP>(txt);
  }

private:
  convert_proxy(); // not impl.
  convert_proxy(const convert_proxy&); // not impl.
  void operator=(const convert_proxy&); // not impl.
};
} // namespace chili::manun
