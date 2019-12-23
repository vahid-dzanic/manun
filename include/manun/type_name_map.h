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

namespace manun {
class type_name_map
{
public:
  type_name_map(const type_name_map&) = delete;
  void operator=(const type_name_map&) = delete;

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
    std::string ret_val(container_name<TYP>());
    ret_val.append("<");
    ret_val.append(name<typename TYP::value_type>());
    if (stdex::traits::is_array<TYP>::value)
    {
      ret_val.append(",");
      ret_val.append(std::to_string(stdex::traits::array_size<TYP>::value));
    }
    ret_val.append(">");
    add<TYP>(ret_val);
    return ret_val;
  }
  template<typename TYP, typename std::enable_if<stdex::traits::is_associative_container<TYP>::value>::type* = nullptr>
  static std::string name()
  {
    auto result = map().find(std::type_index(typeid(TYP)));
    if (result != map().end())
    {
      return result->second;
    }
    std::string ret_val(container_name<TYP>());
    ret_val.append("<");
    if (stdex::traits::is_map_container<TYP>::value)
    {
      ret_val.append(name<typename TYP::value_type>());
    }
    else
    {
      ret_val.append(name<typename TYP::key_type>());
    }
    ret_val.append(">");
    add<TYP>(ret_val);
    return ret_val;
  }
  template<typename TYP, typename std::enable_if<stdex::traits::is_pair<TYP>::value>::type* = nullptr>
  static std::string name()
  {
    auto result = map().find(std::type_index(typeid(TYP)));
    if (result != map().end())
    {
      return result->second;
    }
    std::string ret_val(container_name<TYP>() + "<" + name<typename TYP::first_type>() + "," +
                       name<typename TYP::second_type>() + ">");
    add<TYP>(ret_val);
    return ret_val;
  }
  template<typename TYP, typename std::enable_if<stdex::traits::is_tuple<TYP>::value>::type* = nullptr>
  static std::string name()
  {
    auto result = map().find(std::type_index(typeid(TYP)));
    if (result != map().end())
    {
      return result->second;
    }
    std::string ret_val(container_name<TYP>() + "<" + tuple_types_in_a_row<TYP>() + ">");
    add<TYP>(ret_val);
    return ret_val;
  }

private:
  using tTypeMap = std::unordered_map<std::type_index, std::string>;

  template<typename _Tpl>
  static std::string tuple_types_in_a_row()
  {
    std::string ret_val;
    for (auto val : tuple_types_to_array_of_str<_Tpl>(std::make_index_sequence<std::tuple_size<_Tpl>::value>()))
    {
      ret_val += val;
    }
    ret_val.pop_back(); // remove last [,] sign
    return ret_val;
  }
  template<typename _Tpl, std::size_t... _I>
  static std::array<std::string, std::tuple_size<_Tpl>::value> tuple_types_to_array_of_str(std::index_sequence<_I...>)
  {
    return std::array<std::string, std::tuple_size<_Tpl>::value> {
      {(name<typename std::tuple_element<_I, _Tpl>::type>() + ",")...}};
  }

  type_name_map();
  static tTypeMap& map();
  void add_built_in_type_names();
  template<typename TYP, typename std::enable_if<stdex::traits::is_pair<TYP>::value>::type* = nullptr>
  static std::string container_name()
  {
    return "std::pair";
  }
  template<typename TYP, typename std::enable_if<stdex::traits::is_array<TYP>::value>::type* = nullptr>
  static std::string container_name()
  {
    return "std::array";
  }
  template<typename TYP, typename std::enable_if<stdex::traits::is_vector<TYP>::value>::type* = nullptr>
  static std::string container_name()
  {
    return "std::vector";
  }
  template<typename TYP, typename std::enable_if<stdex::traits::is_deque<TYP>::value>::type* = nullptr>
  static std::string container_name()
  {
    return "std::deque";
  }
  template<typename TYP, typename std::enable_if<stdex::traits::is_list<TYP>::value>::type* = nullptr>
  static std::string container_name()
  {
    return "std::list";
  }
  template<typename TYP, typename std::enable_if<stdex::traits::is_forward_list<TYP>::value>::type* = nullptr>
  static std::string container_name()
  {
    return "std::forward_list";
  }
  template<typename TYP, typename std::enable_if<stdex::traits::is_stack<TYP>::value>::type* = nullptr>
  static std::string container_name()
  {
    return "std::stack";
  }
  template<typename TYP, typename std::enable_if<stdex::traits::is_queue<TYP>::value>::type* = nullptr>
  static std::string container_name()
  {
    return "std::queue";
  }
  template<typename TYP, typename std::enable_if<stdex::traits::is_priority_queue<TYP>::value>::type* = nullptr>
  static std::string container_name()
  {
    return "std::priority_queue";
  }
  template<typename TYP, typename std::enable_if<stdex::traits::is_map<TYP>::value>::type* = nullptr>
  static std::string container_name()
  {
    return "std::map";
  }
  template<typename TYP, typename std::enable_if<stdex::traits::is_set<TYP>::value>::type* = nullptr>
  static std::string container_name()
  {
    return "std::set";
  }
  template<typename TYP, typename std::enable_if<stdex::traits::is_multimap<TYP>::value>::type* = nullptr>
  static std::string container_name()
  {
    return "std::multimap";
  }
  template<typename TYP, typename std::enable_if<stdex::traits::is_multiset<TYP>::value>::type* = nullptr>
  static std::string container_name()
  {
    return "std::multiset";
  }
  template<typename TYP, typename std::enable_if<stdex::traits::is_unordered_map<TYP>::value>::type* = nullptr>
  static std::string container_name()
  {
    return "std::unordered_map";
  }
  template<typename TYP, typename std::enable_if<stdex::traits::is_unordered_set<TYP>::value>::type* = nullptr>
  static std::string container_name()
  {
    return "std::unordered_set";
  }
  template<typename TYP, typename std::enable_if<stdex::traits::is_unordered_multimap<TYP>::value>::type* = nullptr>
  static std::string container_name()
  {
    return "std::unordered_multimap";
  }
  template<typename TYP, typename std::enable_if<stdex::traits::is_unordered_multiset<TYP>::value>::type* = nullptr>
  static std::string container_name()
  {
    return "std::unordered_multiset";
  }
  template<typename TYP, typename std::enable_if<stdex::traits::is_tuple<TYP>::value>::type* = nullptr>
  static std::string container_name()
  {
    return "std::tuple";
  }

  tTypeMap type_map_;
};
} // namespace manun
