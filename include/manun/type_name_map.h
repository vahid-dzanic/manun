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

#include <stdex/std_type_sets.h>
#include <typeindex>

namespace chili::manun {
class type_name_map
{
public:
  template<typename TYP>
  static void add(const std::string& name)
  {
    map().insert(std::make_pair(std::type_index(typeid(TYP)), name));
  }
  template<typename TYP, typename std::enable_if<not stdex::traits::is_container<TYP>::value>::type* = nullptr>
  static std::string name()
  {
    static_assert(not std::is_same<long double, TYP>::value, "Not supported type: long double");
    return map().at(std::type_index(typeid(TYP)));
  }
  template<typename TYP,
           typename std::enable_if<stdex::traits::is_sequential_container<TYP>::value ||
                                   stdex::traits::is_adaptor_container<TYP>::value>::type* = nullptr>
  static std::string name()
  {
    auto result = map().find(std::type_index(typeid(TYP)));
    if (result != map().end())
    {
      return result->second;
    }
    std::string retVal(containerName<TYP>());
    retVal.append("<");
    retVal.append(name<typename TYP::value_type>());
    if (stdex::traits::is_array<TYP>::value)
    {
      retVal.append(",");
      retVal.append(std::to_string(stdex::traits::array_size<TYP>::value));
    }
    retVal.append(">");
    add<TYP>(retVal);
    return retVal;
  }
  template<typename TYP, typename std::enable_if<stdex::traits::is_associative_container<TYP>::value>::type* = nullptr>
  static std::string name()
  {
    auto result = map().find(std::type_index(typeid(TYP)));
    if (result != map().end())
    {
      return result->second;
    }
    std::string retVal(containerName<TYP>());
    retVal.append("<");
    if (stdex::traits::is_map_container<TYP>::value)
    {
      retVal.append(name<typename TYP::value_type>());
    }
    else
    {
      retVal.append(name<typename TYP::key_type>());
    }
    retVal.append(">");
    add<TYP>(retVal);
    return retVal;
  }
  template<typename TYP, typename std::enable_if<stdex::traits::is_pair<TYP>::value>::type* = nullptr>
  static std::string name()
  {
    auto result = map().find(std::type_index(typeid(TYP)));
    if (result != map().end())
    {
      return result->second;
    }
    std::string retVal(containerName<TYP>() + "<" + name<typename TYP::first_type>() + "," +
                       name<typename TYP::second_type>() + ">");
    add<TYP>(retVal);
    return retVal;
  }
  template<typename TYP, typename std::enable_if<stdex::traits::is_tuple<TYP>::value>::type* = nullptr>
  static std::string name()
  {
    auto result = map().find(std::type_index(typeid(TYP)));
    if (result != map().end())
    {
      return result->second;
    }
    std::string retVal(containerName<TYP>() + "<" + tuple_types_in_a_row<TYP>() + ">");
    add<TYP>(retVal);
    return retVal;
  }

private:
  using tTypeMap = std::unordered_map<std::type_index, std::string>;

  template<typename _Tpl>
  static std::string tuple_types_in_a_row()
  {
    std::string retVal;
    for (auto val : tuple_types_to_array_of_str<_Tpl>(std::make_index_sequence<std::tuple_size<_Tpl>::value>()))
    {
      retVal += val;
    }
    retVal.pop_back(); // remove last [,] sign
    return retVal;
  }
  template<typename _Tpl, std::size_t... _I>
  static std::array<std::string, std::tuple_size<_Tpl>::value> tuple_types_to_array_of_str(std::index_sequence<_I...>)
  {
    return std::array<std::string, std::tuple_size<_Tpl>::value>{
      {(name<typename std::tuple_element<_I, _Tpl>::type>() + ",")...}};
  }

  type_name_map();
  static tTypeMap& map();
  void addBuiltInTypeNames();
  template<typename TYP, typename std::enable_if<stdex::traits::is_pair<TYP>::value>::type* = nullptr>
  static std::string containerName()
  {
    return "std::pair";
  }
  template<typename TYP, typename std::enable_if<stdex::traits::is_array<TYP>::value>::type* = nullptr>
  static std::string containerName()
  {
    return "std::array";
  }
  template<typename TYP, typename std::enable_if<stdex::traits::is_vector<TYP>::value>::type* = nullptr>
  static std::string containerName()
  {
    return "std::vector";
  }
  template<typename TYP, typename std::enable_if<stdex::traits::is_deque<TYP>::value>::type* = nullptr>
  static std::string containerName()
  {
    return "std::deque";
  }
  template<typename TYP, typename std::enable_if<stdex::traits::is_list<TYP>::value>::type* = nullptr>
  static std::string containerName()
  {
    return "std::list";
  }
  template<typename TYP, typename std::enable_if<stdex::traits::is_forward_list<TYP>::value>::type* = nullptr>
  static std::string containerName()
  {
    return "std::forward_list";
  }
  template<typename TYP, typename std::enable_if<stdex::traits::is_stack<TYP>::value>::type* = nullptr>
  static std::string containerName()
  {
    return "std::stack";
  }
  template<typename TYP, typename std::enable_if<stdex::traits::is_queue<TYP>::value>::type* = nullptr>
  static std::string containerName()
  {
    return "std::queue";
  }
  template<typename TYP, typename std::enable_if<stdex::traits::is_priority_queue<TYP>::value>::type* = nullptr>
  static std::string containerName()
  {
    return "std::priority_queue";
  }
  template<typename TYP, typename std::enable_if<stdex::traits::is_map<TYP>::value>::type* = nullptr>
  static std::string containerName()
  {
    return "std::map";
  }
  template<typename TYP, typename std::enable_if<stdex::traits::is_set<TYP>::value>::type* = nullptr>
  static std::string containerName()
  {
    return "std::set";
  }
  template<typename TYP, typename std::enable_if<stdex::traits::is_multimap<TYP>::value>::type* = nullptr>
  static std::string containerName()
  {
    return "std::multimap";
  }
  template<typename TYP, typename std::enable_if<stdex::traits::is_multiset<TYP>::value>::type* = nullptr>
  static std::string containerName()
  {
    return "std::multiset";
  }
  template<typename TYP, typename std::enable_if<stdex::traits::is_unordered_map<TYP>::value>::type* = nullptr>
  static std::string containerName()
  {
    return "std::unordered_map";
  }
  template<typename TYP, typename std::enable_if<stdex::traits::is_unordered_set<TYP>::value>::type* = nullptr>
  static std::string containerName()
  {
    return "std::unordered_set";
  }
  template<typename TYP, typename std::enable_if<stdex::traits::is_unordered_multimap<TYP>::value>::type* = nullptr>
  static std::string containerName()
  {
    return "std::unordered_multimap";
  }
  template<typename TYP, typename std::enable_if<stdex::traits::is_unordered_multiset<TYP>::value>::type* = nullptr>
  static std::string containerName()
  {
    return "std::unordered_multiset";
  }
  template<typename TYP, typename std::enable_if<stdex::traits::is_tuple<TYP>::value>::type* = nullptr>
  static std::string containerName()
  {
    return "std::tuple";
  }

  tTypeMap mTypeMap;

  type_name_map(const type_name_map&); // not impl.
  void operator=(const type_name_map&); // not impl.
};
} // namespace chili::manun
