#include "manun/type_name_map.h"

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

namespace manun {

type_name_map::type_name_map() { addBuiltInTypeNames(); }

type_name_map::tTypeMap& type_name_map::map()
{
  static type_name_map tn;
  return tn.type_map_;
}

void type_name_map::addBuiltInTypeNames()
{
  type_map_.insert(std::make_pair(std::type_index(typeid(bool)), "B8"));
  type_map_.insert(std::make_pair(std::type_index(typeid(char)), "C8"));
  //  mTypeMap.insert(std::make_pair(std::type_index(typeid(wchar_t           )), "WC16")); //not supported
  type_map_.insert(std::make_pair(std::type_index(typeid(char16_t)), "C16"));
  type_map_.insert(std::make_pair(std::type_index(typeid(char32_t)), "C32"));
  type_map_.insert(std::make_pair(std::type_index(typeid(float)), "F32"));
  type_map_.insert(std::make_pair(std::type_index(typeid(double)), "F64"));
  //  mTypeMap.insert(std::make_pair(std::type_index(typeid(long double       )), "F96" )); //not supported yet
  type_map_.insert(std::make_pair(std::type_index(typeid(std::int8_t)), "I8"));
  type_map_.insert(std::make_pair(std::type_index(typeid(std::int16_t)), "I16"));
  type_map_.insert(std::make_pair(std::type_index(typeid(std::int32_t)), "I32"));
  type_map_.insert(std::make_pair(std::type_index(typeid(std::int64_t)), "I64"));
  type_map_.insert(std::make_pair(std::type_index(typeid(long long)), "L64"));
  type_map_.insert(std::make_pair(std::type_index(typeid(std::uint8_t)), "UI8"));
  type_map_.insert(std::make_pair(std::type_index(typeid(std::uint16_t)), "UI16"));
  type_map_.insert(std::make_pair(std::type_index(typeid(std::uint32_t)), "UI32"));
  type_map_.insert(std::make_pair(std::type_index(typeid(std::uint64_t)), "UI64"));
  type_map_.insert(std::make_pair(std::type_index(typeid(unsigned long long)), "UL64"));
  type_map_.insert(std::make_pair(std::type_index(typeid(std::string)), "STR"));
  //  mTypeMap.insert(std::make_pair(std::type_index(typeid(std::wstring      )), "WSTR")); //not supported

  /* TODO: check if this is an issue: The width of wchar_t is compiler-specific and can be as small as 8 bits.
           Consequently, programs that need to be portable across any C or C++ compiler should not use wchar_t
           for storing Unicode text. The wchar_t type is intended for storing compiler-defined wide characters,
           which may be Unicode characters in some compilers. */
}

} // namespace manun
