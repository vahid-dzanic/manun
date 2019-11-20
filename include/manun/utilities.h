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

#include "manun_exceptions.h"
#include "type_name_map.h"

#include <stdex/functional_ex.h>

namespace chili::manun {

static constexpr char STX = '\x02'; // ascii --> start of text
static constexpr char ETX = '\x03'; // ascii --> end of text
static constexpr char SGP = '{'; // start of group
static constexpr char EGP = '}'; // end of group

template<typename TYP>
static constexpr void static_assert_by_type()
{
  static_assert(not std::is_same<long double, TYP>::value, "Not supported type: long double");
  static_assert(not std::is_same<wchar_t, TYP>::value, "Not supported type: wchar_t");
  static_assert(not std::is_same<std::wstring, TYP>::value, "Not supported type: std::wstring");
  static_assert(not std::is_null_pointer<TYP>::value, "Not supported type: nullptr");
  static_assert(not std::is_array<TYP>::value, "Not supported type: C style arrays");
  static_assert(not is_std_function<TYP>::value,
                "Not supported type: std::function use chili::manun::convert::func::toString");
  static_assert(not std::is_function<TYP>::value, "Not supported type: function");
  static_assert(not std::is_union<TYP>::value, "Not supported type: union");
  static_assert(not std::is_void<TYP>::value, "Not supported type: void");
}

std::vector<std::string> extractGroups(const std::string& text, char sgp = SGP, char egp = EGP);
std::size_t positionOfFirstEqualSign(const std::string& text);
template<typename TYP>
std::string extractContent(const std::string& text)
{
  std::size_t pos = positionOfFirstEqualSign(text);
  if (pos == std::string::npos)
  {
    throw NoEqualSignAfterTypeNameException(text);
  }
  std::string name(type_name_map::name<TYP>());
  std::string parsedName(text.substr(0, pos));
  if (name != parsedName)
  {
    if (stdex::starts_with(text, name))
    {
      throw NoEqualSignAfterTypeNameException(text);
    }
    else
    {
      throw TypemismatchException(name, parsedName);
    }
  }
  return text.substr(name.size() + 1); // + 1 --> removes [=] too
}

std::string rm_edge_identifier(const std::string& txt);

} // namespace chili::manun
