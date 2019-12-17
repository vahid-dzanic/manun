#include "manun/function_map.h"

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

function_map::function_map(function_map&& rhs)
  : func_map_(std::move(rhs.func_map_))
{}

function_map::~function_map()
{
  for (auto val : func_map_)
  {
    delete val.second;
  }
  func_map_.clear();
}

void function_map::execute(const std::string& value)
{
  std::string raw = rm_edge_identifier(value);
  std::size_t pos1 = raw.find('(');
  if (pos1 == std::string::npos)
  {
    throw can_not_parse_function_name_exception(value);
  }
  std::size_t pos2 = std::string::npos;
  if (raw.at(pos1 + 1) == ')') // does function has no arguments
  {
    pos2 = pos1;
  }
  else
  {
    pos2 = raw.find('(', pos1 + 1);
  }
  if (pos2 == std::string::npos)
  {
    throw can_not_parse_function_name_exception(value);
  }
  std::string func_name = raw.substr(0, pos2);
  std::vector<std::string> args = extract_groups(rm_edge_identifier(raw.substr(pos2)));
  auto iter = func_map_.find(func_name);
  if (iter == func_map_.end())
  {
    throw function_not_found_exception(func_name);
  }
  (*iter).second->execute(args);
}

void function_map::remove(const std::string& name)
{
  auto iter = func_map_.find(name);
  if (iter == func_map_.end())
  {
    throw function_not_found_exception(name);
  }
  delete (*iter).second;
  func_map_.erase(iter);
}

} // namespace manun
