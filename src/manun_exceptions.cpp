#include "manun/manun_exceptions.h"

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

type_mismatch_exception::type_mismatch_exception(const std::string& expectedType, const std::string& parsedType)
  : mWhat("Type mismatch, expected is [" + expectedType + "] parsed from text is [" + parsedType + "].")
{}
const char* type_mismatch_exception::what() const throw() { return mWhat.c_str(); }

nullptr_exception::nullptr_exception()
  : mWhat("Pointer is not initialized.")
{}
const char* nullptr_exception::what() const throw() { return mWhat.c_str(); }

entry_already_exists_exception::entry_already_exists_exception()
  : mWhat("Type entry already exists.")
{}
const char* entry_already_exists_exception::what() const throw() { return mWhat.c_str(); }

entry_does_not_exists_exception::entry_does_not_exists_exception(const std::string& entry)
  : mWhat("Type specific converter functions doesn't exists. typid( of_your_type ).name=[" + entry + "]")
{}
const char* entry_does_not_exists_exception::what() const throw() { return mWhat.c_str(); }

curly_braces_not_even_count_exception::curly_braces_not_even_count_exception(const std::string& txt)
  : mWhat("Missing one curly brace in the current string: " + txt)
{}
const char* curly_braces_not_even_count_exception::what() const throw() { return mWhat.c_str(); }

no_equal_sign_after_type_name_exception::no_equal_sign_after_type_name_exception(const std::string& txt)
  : mWhat("Missing equal sign [=] after type name in the current string: " + txt)
{}
const char* no_equal_sign_after_type_name_exception::what() const throw() { return mWhat.c_str(); }

type_is_not_a_function_exception::type_is_not_a_function_exception()
  : mWhat("Type is not a function")
{}
const char* type_is_not_a_function_exception::what() const throw() { return mWhat.c_str(); }

to_many_arguments_exception::to_many_arguments_exception(std::size_t current, std::size_t max)
  : mWhat("To many arguments: " + std::to_string(current) + " Maximum supported are : " + std::to_string(max))
{}
const char* to_many_arguments_exception::what() const throw() { return mWhat.c_str(); }

function_not_found_exception::function_not_found_exception(const std::string& function)
  : mWhat("Function [" + function + "] not found in function container")
{}
const char* function_not_found_exception::what() const throw() { return mWhat.c_str(); }

can_not_parse_function_name_exception::can_not_parse_function_name_exception(const std::string& text)
  : mWhat("Can not parse function name: " + text)
{}
const char* can_not_parse_function_name_exception::what() const throw() { return mWhat.c_str(); }

function_already_registered_exception::function_already_registered_exception(const std::string& function)
  : mWhat("Function [" + function + "] already registered")
{}
const char* function_already_registered_exception::what() const throw() { return mWhat.c_str(); }

} // namespace manun
