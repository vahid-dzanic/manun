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

#include "utilities.h"

#include <functional>
#include <string>
#include <typeindex>
#include <unordered_map>

namespace chili::manun {
class ITypeIndex
{
public:
  virtual ~ITypeIndex() {}
  virtual std::type_index typeIndex() const = 0;
  virtual const std::string& typeName() const = 0;
};

template<typename value_t>
using string2value_func_t = std::function<value_t(const std::vector<std::string>&)>;
template<typename value_t>
using value2string_func_t = std::function<std::string(const value_t&)>;

template<typename value_t>
class converter_functions : public ITypeIndex
{
public:
  converter_functions(const std::string& name,
                      string2value_func_t<value_t> objectCreateFunc,
                      value2string_func_t<value_t> stringCreateFunc)
    : mTypeName(name)
    , m_string2value_func(objectCreateFunc)
    , m_value2string_func(stringCreateFunc)
  {
    if (objectCreateFunc == nullptr || stringCreateFunc == nullptr)
    {
      throw chili::manun::NullptrException();
    }
  }
  converter_functions(const converter_functions& rhs)
    : m_string2value_func(rhs.m_string2value_func)
    , m_value2string_func(rhs.m_value2string_func)
  {}

  virtual std::type_index typeIndex() const { return std::type_index(typeid(value_t)); }
  virtual const std::string& typeName() const { return mTypeName; }
  value_t string2value(const std::vector<std::string>& value) { return m_string2value_func(value); }
  std::string value2string(const value_t& value) { return m_value2string_func(value); }

private:
  std::string mTypeName;
  string2value_func_t<value_t> m_string2value_func;
  value2string_func_t<value_t> m_value2string_func;
};

class converter_factory
{
public:
  template<typename value_t>
  static void add(converter_functions<value_t>* creator)
  {
    if (creator == nullptr)
    {
      throw chili::manun::NullptrException();
    }
    tCreatorMap& localMap = map();
    auto iter = localMap.find(creator->typeIndex());
    if (iter != localMap.end())
    {
      throw chili::manun::EntryAlreadyExistsException();
    }
    localMap.emplace(std::make_pair(creator->typeIndex(), creator));
    type_name_map::add<value_t>(creator->typeName());
  }
  template<typename value_t>
  static void add(const std::string& name,
                  string2value_func_t<value_t> objectCreateFunc,
                  value2string_func_t<value_t> stringCreateFunc)
  {
    converter_factory::add<value_t>(new converter_functions<value_t>(name, objectCreateFunc, stringCreateFunc));
  }
  template<typename value_t>
  static void remove()
  {
    map().erase(std::type_index(typeid(value_t)));
  }
  static void removeAll();

  template<typename value_t>
  static value_t string2value(const std::string& value)
  {
    auto content = extractContent<value_t>(value.substr(1, value.size() - 2));
    content = content.substr(1, content.size() - 2);
    if (std::is_pointer<value_t>::value && content == "nullptr")
    {
      return nullptr;
    }
    return get<value_t>()->string2value(extractGroups(content));
  }
  template<typename value_t>
  static std::string value2string(const value_t& value)
  {
    std::string val2str;
    if (std::is_pointer<value_t>::value && value == nullptr)
    {
      val2str = "nullptr";
    }
    else
    {
      val2str = get<value_t>()->value2string(value);
    }
    return std::string("{" + chili::manun::type_name_map::name<value_t>() + "={" + val2str + "}}");
  }

private:
  using tCreatorMap = std::unordered_map<std::type_index, ITypeIndex*>;

  converter_factory() = default;
  ~converter_factory();

  template<typename value_t>
  static converter_functions<value_t>* get()
  {
    static_assert_by_type<value_t>();
    auto localMap = map();
    auto iter = localMap.find(std::type_index(typeid(value_t)));
    if (iter == localMap.end())
    {
      throw chili::manun::EntryDoesNotExistsException(typeid(value_t).name());
    }
    auto retVal = dynamic_cast<converter_functions<value_t>*>((*iter).second);
    if (retVal == nullptr)
    {
      throw chili::manun::NullptrException();
    }
    return retVal;
  }

  static tCreatorMap& map();

  tCreatorMap mObjCreatorFuncMap;

  converter_factory(const converter_factory&); // not impl.
  void operator=(const converter_factory&); // not impl.
};
} // namespace chili::manun
