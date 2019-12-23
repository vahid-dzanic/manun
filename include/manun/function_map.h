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

#include <stdex/functional_ex.h>

namespace manun {

class function_map
{
public:
  function_map() = default;
  function_map(function_map&& rhs);
  ~function_map();

  void execute(const std::string& value);

  template<typename _TFunc>
  void add(const _TFunc& func)
  {
    static_assert(stdex::is_function<_TFunc>::value, "2nd argument must be a function<void(...)>");
    static_assert(std::is_same<typename _TFunc::result_type, void>::value,
                  "Only functions with [void] return type are supported --> function<void(...)>");
    auto func_name = func.name() + types<typename _TFunc::arguments>();
    auto iter = func_map_.find(func_name);
    if (iter != func_map_.end())
    {
      throw function_already_registered_exception(func_name);
    }
    func_map_.insert(std::make_pair(func_name, new func_container<_TFunc>(func)));
  }
  template<typename _TFunc>
  void remove(const _TFunc& func)
  {
    static_assert(stdex::is_function<_TFunc>::value, "2nd argument must be a function<void(...)>");
    static_assert(std::is_same<typename _TFunc::result_type, void>::value,
                  "Only functions with [void] return type are supported --> function<void(...)>");
    auto func_name = func.name() + types<typename _TFunc::arguments>();
    remove(func_name);
  }

private:
  void remove(const std::string& name);

  class executer
  {
  public:
    virtual ~executer() = default;
    virtual void execute(const std::vector<std::string>& arguments) = 0;
  };
  template<typename _TFunc>
  class func_container : public executer
  {
  public:
    func_container(const _TFunc& func)
      : func_(func)
    {}

    void execute(const std::vector<std::string>& arguments) override
    {
      auto index_seq = std::make_index_sequence<std::tuple_size<_Tpl>::value>();
      invoke(vec2tup(arguments, index_seq), index_seq);
    }

  private:
    using _Tpl = typename _TFunc::arguments;

    template<typename _Tpl, std::size_t... _I>
    void invoke(_Tpl&& args, std::index_sequence<_I...>)
    {
      func_(std::get<_I>(std::forward<_Tpl>(args))...);
    }
    template<std::size_t... _I>
    _Tpl vec2tup(const std::vector<std::string>& vec, std::index_sequence<_I...>)
    {
      return std::make_tuple(convert_proxy::string2value<typename std::tuple_element<_I, _Tpl>::type>(vec[_I])...);
    }

    _TFunc func_;
  };

  template<typename _Tpl>
  std::string types()
  {
    if (std::tuple_size<_Tpl>::value == 0)
    {
      return "";
    }
    std::string ret_val("(");
    for (const auto& val : tuple2array_impl<_Tpl>(std::make_index_sequence<std::tuple_size<_Tpl>::value>()))
    {
      ret_val += val;
    }
    ret_val.pop_back();
    ret_val.push_back(')');
    return ret_val;
  }
  template<typename _Tpl, std::size_t... _I>
  std::array<std::string, std::tuple_size<_Tpl>::value> tuple2array_impl(std::index_sequence<_I...>)
  {
    return std::array<std::string, std::tuple_size<_Tpl>::value> {
      {(type_name_map::name<typename std::tuple_element<_I, _Tpl>::type>() + ",")...}};
  }

  std::map<std::string, executer*> func_map_;
};
} // namespace manun
