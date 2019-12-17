#include "manun/utilities.h"

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

std::vector<std::string> extract_groups(const std::string& text, char sgp, char egp)
{
  bool opened = false;
  std::size_t openPosition = 0;
  std::size_t charCount = 0;
  std::uint64_t openingBracketCount = 0;
  std::uint64_t closingBracketCount = 0;
  std::vector<std::string> retVal;
  bool ignore = false;
  for (std::size_t i = 0; i < text.size(); ++i)
  {
    char c = text.at(i);
    ++charCount;
    if (!ignore && c == STX)
    {
      ignore = true;
    }
    else if (ignore && c == ETX)
    {
      ignore = false;
    }
    else if (!ignore && c == sgp)
    {
      ++openingBracketCount;
      if (!opened)
      {
        opened = true;
        openPosition = i;
        charCount = 0;
      }
    }
    else if (!ignore && c == egp)
    {
      ++closingBracketCount;
      if (opened && openingBracketCount == closingBracketCount)
      {
        retVal.push_back(text.substr(openPosition, charCount + 1));
        opened = false;
        openPosition = 0;
        openingBracketCount = 0;
        closingBracketCount = 0;
      }
    }
  }
  return retVal;
}

std::size_t position_of_first_equal_sign(const std::string& text) { return text.find('='); }

std::string rm_edge_identifier(const std::string& txt)
{
  if (!txt.empty())
  {
    return txt.substr(1, txt.size() - 2);
  }
  return "";
}

} // namespace manun
