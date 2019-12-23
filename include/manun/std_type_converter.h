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

#include "converter_factory.h"
#include "utilities.h"

#include <ios>
#include <sstream>

namespace manun {
class std_type_converter
{
public:
  std_type_converter() = delete;
  std_type_converter(const std_type_converter&) = delete;
  void operator=(const std_type_converter&) = delete;

  template<typename TYP, typename std::enable_if<stdex::traits::is_string<TYP>::value>::type* = nullptr>
  static TYP string2value(const std::string& txt)
  {
    auto sub = extract_content<TYP>(txt.substr(1, txt.size() - 2));
    return sub.substr(1, sub.size() - 2); // remove STX/ETX
  }
  template<typename TYP, typename std::enable_if<std::is_arithmetic<TYP>::value>::type* = nullptr>
  static TYP string2value(const std::string& txt)
  {
    static_assert(not std::is_same<long double, TYP>::value, "Not supported type: long double");
    static_assert(not std::is_same<wchar_t, TYP>::value, "Not supported type: wchar_t");
    return string2arithmetic<TYP>(extract_content<TYP>(txt.substr(1, txt.size() - 2)));
  }
  template<typename TYP, typename std::enable_if<stdex::traits::is_container<TYP>::value>::type* = nullptr>
  static TYP string2value(const std::string& txt)
  {
    return string2valueInternal<TYP>(extract_content<TYP>(txt.substr(1, txt.size() - 2)));
  }

  template<typename TYP>
  static std::string value2string(const TYP& value,
                                  typename std::enable_if<stdex::traits::is_string<TYP>::value>::type* = nullptr)
  {
    std::string::size_type nSTX = value.find(STX);
    std::string::size_type nETX = value.find(ETX);
    if (nSTX != std::string::npos || nETX != std::string::npos)
    {
      // assert
    }
    return std::string(SGP + type_name_map::name<TYP>() + "=" + STX + value + ETX + EGP);
  }
  template<typename TYP>
  static std::string value2string(const TYP& value,
                                  typename std::enable_if<std::is_arithmetic<TYP>::value>::type* = nullptr)
  {
    static_assert(not std::is_same<long double, TYP>::value, "Not supported type: long double");
    static_assert(not std::is_same<wchar_t, TYP>::value, "Not supported type: wchar_t");
    return std::string(SGP + type_name_map::name<TYP>() + "=" + arithmetic2string(value) + EGP);
  }
  template<typename TYP>
  static std::string value2string(const TYP& value,
                                  typename std::enable_if<stdex::traits::is_container<TYP>::value>::type* = nullptr)
  {
    return std::string(SGP + type_name_map::name<TYP>() + "=" + value2stringInternal(value) + EGP);
  }

  union tF64_U64
  {
    double F64;
    std::uint64_t U64;
  };
  union tF32_U32
  {
    float F32;
    std::uint32_t U32;
  };
#ifdef __VDC_CONVERT_ARITHMETIC_IN_DEC
  template<typename TYP,
           typename std::enable_if<std::is_integral<TYP>::value && std::is_unsigned<TYP>::value>::type* = nullptr>
  static TYP string2arithmetic(const std::string& txt)
  {
    return static_cast<TYP>(std::stoull(txt));
  }
  template<typename TYP,
           typename std::enable_if<std::is_integral<TYP>::value && std::is_signed<TYP>::value>::type* = nullptr>
  static TYP string2arithmetic(const std::string& txt)
  {
    return static_cast<TYP>(std::stoll(txt));
  }
#else // convert in hex
  template<typename TYP,
           typename std::enable_if<std::is_integral<TYP>::value &&
                                   not(std::is_same<TYP, char>::value || std::is_same<TYP, signed char>::value ||
                                       std::is_same<TYP, unsigned char>::value)>::type* = nullptr>
  static TYP string2arithmetic(const std::string& txt)
  {
    std::uintmax_t ret_val = 0;
    std::istringstream(txt) >> std::hex >> ret_val;
    return static_cast<TYP>(ret_val);
  }
  template<typename TYP,
           typename std::enable_if<std::is_integral<TYP>::value &&
                                   (std::is_same<TYP, char>::value || std::is_same<TYP, signed char>::value ||
                                    std::is_same<TYP, unsigned char>::value)>::type* = nullptr>
  static TYP string2arithmetic(const std::string& txt)
  {
    TYP ret_val;
    std::istringstream(txt) >> std::hex >> ret_val;
    return static_cast<TYP>(ret_val);
  }
//  template<typename TYP, typename std::enable_if<std::is_integral<TYP>::value && std::is_signed<TYP>::value && not (
//                                                 std::is_same<TYP, char>::value ||
//                                                 std::is_same<TYP, signed char>::value)>::type* = nullptr>
//  static TYP string2arithmetic(const std::string& txt)
//  {
////    std::intmax_t ret_val = 0;
////    std::istringstream(txt) >> std::hex >> ret_val;
////    return static_cast<TYP>(ret_val);
//    std::uintmax_t ret_val = 0;
//    std::istringstream(txt) >> std::hex >> ret_val;
//    return static_cast<TYP>(ret_val);
//  }
//  template<typename TYP, typename std::enable_if<std::is_integral<TYP>::value && std::is_signed<TYP>::value && (
//                                                 std::is_same<TYP, char>::value ||
//                                                 std::is_same<TYP, signed char>::value)>::type* = nullptr>
//  static TYP string2arithmetic(const std::string& txt)
//  {
//    TYP ret_val;
//    std::istringstream(txt) >> std::hex >> ret_val;
//    return static_cast<TYP>(ret_val);
//  }
#endif //__VDC_CONVERT_ARITHMETIC_IN_DEC
  template<typename TYP, typename std::enable_if<std::is_floating_point<TYP>::value>::type* = nullptr>
  static TYP string2arithmetic(const std::string& txt)
  {
    if (std::is_same<TYP, float>::value)
    {
      tF32_U32 val{};
      val.U32 = string2arithmetic<std::uint32_t>(txt);
      return val.F32;
    }
    else if (std::is_same<TYP, double>::value)
    {
      tF64_U64 val{};
      val.U64 = string2arithmetic<std::uint64_t>(txt);
      return val.F64;
    }
    // assert
    return 0;
  }
  template<typename TYP>
  static std::string arithmetic2string(TYP value,
                                       typename std::enable_if<std::is_integral<TYP>::value>::type* = nullptr)
  {
#ifdef __VDC_CONVERT_ARITHMETIC_IN_DEC
    return std::to_string(value);
#else // convert in hex
    std::ostringstream buffer;
    buffer << std::hex << value;
    return buffer.str();
#endif //__VDC_CONVERT_ARITHMETIC_IN_DEC
  }
  template<typename TYP>
  static std::string arithmetic2string(TYP value,
                                       typename std::enable_if<std::is_floating_point<TYP>::value>::type* = nullptr)
  {
    if (std::is_same<TYP, float>::value)
    {
      tF32_U32 val{};
      val.F32 = value;
      return arithmetic2string<std::uint32_t>(val.U32);
    }
    else if (std::is_same<TYP, double>::value)
    {
      tF64_U64 val{};
      val.F64 = value;
      return arithmetic2string<std::uint64_t>(val.U64);
    }
    // assert
    return "";
  }

private:
  template<typename TYP, typename std::enable_if<stdex::traits::is_string<TYP>::value>::type* = nullptr>
  static TYP string2valueInternal(const std::string& txt)
  {
    return txt.substr(2, txt.size() - 4); // remove {} and STX/ETX
  }
  template<typename TYP, typename std::enable_if<std::is_arithmetic<TYP>::value>::type* = nullptr>
  static TYP string2valueInternal(const std::string& txt)
  {
    return string2arithmetic<TYP>(txt.substr(1, txt.size() - 2));
  }
  template<typename TYP, typename std::enable_if<stdex::traits::is_array<TYP>::value>::type* = nullptr>
  static TYP string2valueInternal(const std::string& txt)
  {
    TYP ret_val;
    auto sub = txt.substr(1, txt.size() - 2);
    std::vector<std::string> vecTxt = extract_groups(sub);
    for (std::size_t i = 0; i < vecTxt.size(); ++i)
    {
      ret_val[i] = string2valueInternal<typename TYP::value_type>(vecTxt[i]);
    }
    return ret_val;
  }
  template<typename TYP,
           typename std::enable_if<stdex::traits::is_vector<TYP>::value || stdex::traits::is_deque<TYP>::value>::type* =
             nullptr>
  static TYP string2valueInternal(const std::string& txt)
  {
    TYP ret_val;
    auto sub = txt.substr(1, txt.size() - 2);
    std::vector<std::string> vecTxt = extract_groups(sub);
    ret_val.resize(vecTxt.size());
    for (std::size_t i = 0; i < vecTxt.size(); ++i)
    {
      ret_val[i] = string2valueInternal<typename TYP::value_type>(vecTxt[i]);
    }
    return ret_val;
  }
  template<typename TYP,
           typename std::enable_if<stdex::traits::is_list<TYP>::value ||
                                   stdex::traits::is_forward_list<TYP>::value>::type* = nullptr>
  static TYP string2valueInternal(const std::string& txt)
  {
    TYP ret_val;
    auto sub = txt.substr(1, txt.size() - 2);
    std::vector<std::string> vecTxt = extract_groups(sub);
    for (std::vector<std::string>::const_reverse_iterator i = vecTxt.crbegin(); i != vecTxt.crend(); ++i)
    {
      ret_val.push_front(string2valueInternal<typename TYP::value_type>(*i));
    }
    return ret_val;
  }
  template<typename TYP,
           typename std::enable_if<stdex::traits::is_stack<TYP>::value ||
                                   stdex::traits::is_priority_queue<TYP>::value>::type* = nullptr>
  static TYP string2valueInternal(const std::string& txt)
  {
    TYP ret_val;
    auto sub = txt.substr(1, txt.size() - 2);
    std::vector<std::string> vecTxt = extract_groups(sub);
    for (std::vector<std::string>::const_reverse_iterator i = vecTxt.crbegin(); i != vecTxt.crend(); ++i)
    {
      ret_val.push(string2valueInternal<typename TYP::value_type>(*i));
    }
    return ret_val;
  }
  template<typename TYP, typename std::enable_if<stdex::traits::is_queue<TYP>::value>::type* = nullptr>
  static TYP string2valueInternal(const std::string& txt)
  {
    TYP ret_val;
    auto sub = txt.substr(1, txt.size() - 2);
    std::vector<std::string> vecTxt = extract_groups(sub);
    for (const auto& val : vecTxt)
    {
      ret_val.push(string2valueInternal<typename TYP::value_type>(val));
    }
    return ret_val;
  }
  template<typename TYP, typename std::enable_if<stdex::traits::is_associative_container<TYP>::value>::type* = nullptr>
  static TYP string2valueInternal(const std::string& txt)
  {
    TYP ret_val;
    auto sub = txt.substr(1, txt.size() - 2);
    std::vector<std::string> vecTxt = extract_groups(sub);
    for (std::size_t i = 0; i < vecTxt.size(); ++i)
    {
      ret_val.insert(string2valueInternal<typename TYP::value_type>(vecTxt[i]));
    }
    return ret_val;
  }
  template<typename TYP, typename std::enable_if<stdex::traits::is_pair<TYP>::value>::type* = nullptr>
  static TYP string2valueInternal(const std::string& txt)
  {
    auto sub = txt.substr(1, txt.size() - 2);
    std::vector<std::string> vecTxt = extract_groups(sub);
    // assert if vecTxt.size() != 2
    return std::make_pair(string2valueInternal<typename TYP::first_type>(vecTxt.at(0)),
                          string2valueInternal<typename TYP::second_type>(vecTxt.at(1)));
  }
  template<typename TYP, typename std::enable_if<stdex::traits::is_tuple<TYP>::value>::type* = nullptr>
  static TYP string2valueInternal(const std::string& txt)
  {
    auto sub = txt.substr(1, txt.size() - 2);
    std::vector<std::string> vecTxt = extract_groups(sub);
    return stringvector2tuple<TYP>(vecTxt, std::make_index_sequence<std::tuple_size<TYP>::value>());
  }
  template<typename _Tpl, std::size_t... _I>
  static _Tpl stringvector2tuple(const std::vector<std::string>& vec, std::index_sequence<_I...>)
  {
    return std::make_tuple(string2valueInternal<typename std::tuple_element<_I, _Tpl>::type>(vec[_I])...);
  }
  template<
    typename TYP,
    typename std::enable_if<not(stdex::traits::is_std_type<TYP>::value || std::is_enum<TYP>::value)>::type* = nullptr>
  static TYP string2valueInternal(const std::string& txt)
  {
    return converter_factory::string2value<TYP>(txt);
  }
  template<typename TYP, typename std::enable_if<std::is_enum<TYP>::value>::type* = nullptr>
  static TYP string2valueInternal(const std::string& txt)
  {
    return static_cast<TYP>(std::stoll(txt.substr(1, txt.size() - 2)));
  }

  template<typename TYP>
  static std::string value2stringInternal(
    const TYP& value,
    typename std::enable_if<stdex::traits::is_string<TYP>::value>::type* = nullptr)
  {
    std::string::size_type nSTX = value.find(STX);
    std::string::size_type nETX = value.find(ETX);
    if (nSTX != std::string::npos || nETX != std::string::npos)
    {
      // assert
    }
    //    return std::string(SGP + STX + value + ETX + EGP);
    std::string ret_val;
    ret_val.reserve(value.size() + 4);
    ret_val.push_back(SGP);
    ret_val.push_back(STX);
    ret_val.append(value);
    ret_val.push_back(ETX);
    ret_val.push_back(EGP);
    return ret_val;
  }
  template<typename TYP>
  static std::string value2stringInternal(const TYP& value,
                                          typename std::enable_if<std::is_arithmetic<TYP>::value>::type* = nullptr)
  {
    return std::string(SGP + arithmetic2string<TYP>(value) + EGP);
  }
  template<typename TYP>
  static std::string value2stringInternal(
    const TYP& container,
    typename std::enable_if<stdex::traits::is_sequential_container<TYP>::value>::type* = nullptr)
  {
    std::string ret_val;
    ret_val.push_back(SGP);
    for (auto value : container)
    {
      ret_val.append(value2stringInternal(value));
    }
    ret_val.push_back(EGP);
    return ret_val;
  }
  template<typename TYP>
  static std::string value2stringInternal(
    const TYP& container,
    typename std::enable_if<stdex::traits::is_stack<TYP>::value ||
                            stdex::traits::is_priority_queue<TYP>::value>::type* = nullptr)
  {
    std::string ret_val;
    ret_val.push_back(SGP);
    TYP localContainer(container);
    while (!localContainer.empty())
    {
      ret_val.append(value2stringInternal(localContainer.top()));
      localContainer.pop();
    }
    ret_val.push_back(EGP);
    return ret_val;
  }
  template<typename TYP>
  static std::string value2stringInternal(const TYP& container,
                                          typename std::enable_if<stdex::traits::is_queue<TYP>::value>::type* = nullptr)
  {
    std::string ret_val;
    ret_val.push_back(SGP);
    TYP localContainer(container);
    while (!localContainer.empty())
    {
      ret_val.append(value2stringInternal(localContainer.front()));
      localContainer.pop();
    }
    ret_val.push_back(EGP);
    return ret_val;
  }
  template<typename TYP>
  static std::string value2stringInternal(
    const TYP& container,
    typename std::enable_if<stdex::traits::is_set_container<TYP>::value>::type* = nullptr)
  {
    std::string ret_val;
    ret_val.push_back(SGP);
    for (auto value : container)
    {
      ret_val.append(value2stringInternal(value));
    }
    ret_val.push_back(EGP);
    return ret_val;
  }
  template<typename TYP>
  static std::string value2stringInternal(
    const TYP& container,
    typename std::enable_if<stdex::traits::is_map_container<TYP>::value>::type* = nullptr)
  {
    std::string ret_val;
    ret_val.push_back(SGP);
    for (auto value : container)
    {
      ret_val.append(value2stringInternal(value));
    }
    ret_val.push_back(EGP);
    return ret_val;
  }
  template<typename TYP>
  static std::string value2stringInternal(const TYP& value,
                                          typename std::enable_if<stdex::traits::is_pair<TYP>::value>::type* = nullptr)
  {
    return std::string(SGP + value2stringInternal(value.first) + value2stringInternal(value.second) + EGP);
  }
  template<typename TYP>
  static std::string value2stringInternal(const TYP& value,
                                          typename std::enable_if<stdex::traits::is_tuple<TYP>::value>::type* = nullptr)
  {
    return std::string(SGP + tuple2string(value) + EGP);
  }
  template<typename _Tpl>
  static std::string tuple2string(const _Tpl& arguments)
  {
    std::string ret_val;
    for (auto val : tuple2array_of_strings<_Tpl>(arguments, std::make_index_sequence<std::tuple_size<_Tpl>::value>()))
    {
      ret_val += val;
    }
    return ret_val;
  }
  template<typename _Tpl, std::size_t... _I>
  static std::array<std::string, std::tuple_size<_Tpl>::value> tuple2array_of_strings(const _Tpl& tpl,
                                                                                      std::index_sequence<_I...>)
  {
    return std::array<std::string, std::tuple_size<_Tpl>::value> {{value2stringInternal(std::get<_I>(tpl))...}};
  }
  template<typename TYP>
  static std::string value2stringInternal(
    const TYP& value,
    typename std::enable_if<not(stdex::traits::is_std_type<TYP>::value || std::is_enum<TYP>::value)>::type* = nullptr)
  {
    return converter_factory::value2string(value);
  }
  template<typename TYP>
  static std::string value2stringInternal(const TYP& value,
                                          typename std::enable_if<std::is_enum<TYP>::value>::type* = nullptr)
  {
    return std::string(SGP + std::to_string(static_cast<std::int64_t>(value)) + EGP);
  }
};
} // namespace manun
