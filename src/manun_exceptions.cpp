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

namespace chili::manun {

TypemismatchException::TypemismatchException(const std::string& expectedType,
                                                           const std::string& parsedType)
  : mWhat("Type mismatch, expected is [" + expectedType + "] parsed from text is [" + parsedType + "].")
{}
const char* TypemismatchException::what() const throw() { return mWhat.c_str(); }

NullptrException::NullptrException()
  : mWhat("Pointer is not initialized.")
{}
const char* NullptrException::what() const throw() { return mWhat.c_str(); }

EntryAlreadyExistsException::EntryAlreadyExistsException()
  : mWhat("Type entry already exists.")
{}
const char* EntryAlreadyExistsException::what() const throw() { return mWhat.c_str(); }

EntryDoesNotExistsException::EntryDoesNotExistsException(const std::string& entry)
  : mWhat("Type specific converter functions doesn't exists. typid( of_your_type ).name=[" + entry + "]")
{}
const char* EntryDoesNotExistsException::what() const throw() { return mWhat.c_str(); }

CurlyBracesNotEvenCountException::CurlyBracesNotEvenCountException(const std::string& txt)
  : mWhat("Missing one curly brace in the current string: " + txt)
{}
const char* CurlyBracesNotEvenCountException::what() const throw() { return mWhat.c_str(); }

NoEqualSignAfterTypeNameException::NoEqualSignAfterTypeNameException(const std::string& txt)
  : mWhat("Missing equal sign [=] after type name in the current string: " + txt)
{}
const char* NoEqualSignAfterTypeNameException::what() const throw() { return mWhat.c_str(); }

TypeIsNotAFunctionException::TypeIsNotAFunctionException()
  : mWhat("Type is not a function")
{}
const char* TypeIsNotAFunctionException::what() const throw() { return mWhat.c_str(); }

ToManyArgumentsException::ToManyArgumentsException(std::size_t current, std::size_t max)
  : mWhat("To many arguments: " + std::to_string(current) + " Maximum supported are : " + std::to_string(max))
{}
const char* ToManyArgumentsException::what() const throw() { return mWhat.c_str(); }

FunctionNotFoundException::FunctionNotFoundException(const std::string& function)
  : mWhat("Function [" + function + "] not found in function container")
{}
const char* FunctionNotFoundException::what() const throw() { return mWhat.c_str(); }

CanNotParseFunctionNameException::CanNotParseFunctionNameException(const std::string& text)
  : mWhat("Can not parse function name: " + text)
{}
const char* CanNotParseFunctionNameException::what() const throw() { return mWhat.c_str(); }

FunctionAlreadyRegisteredException::FunctionAlreadyRegisteredException(const std::string& function)
  : mWhat("Function [" + function + "] already registered")
{}
const char* FunctionAlreadyRegisteredException::what() const throw() { return mWhat.c_str(); }

} // namespace chili::manun
