#include "manun/converter_factory.h"

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

namespace chili::manun {

void converter_factory::removeAll()
{
  auto localmap = map();
  for (auto ptr : localmap)
  {
    delete ptr.second;
  }
  localmap.clear();
}

converter_factory::~converter_factory()
{
  for (auto ptr : mObjCreatorFuncMap)
  {
    delete ptr.second;
  }
  mObjCreatorFuncMap.clear();
}

converter_factory::tCreatorMap& converter_factory::map()
{
  static converter_factory oF;
  return oF.mObjCreatorFuncMap;
}

} // namespace chili::manun
