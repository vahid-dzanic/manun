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

#include <exception>
#include <string>

namespace chili::manun {

class TypemismatchException : public std::exception
{
public:
  TypemismatchException(const std::string& expectedType, const std::string& parsedType);
  virtual const char* what() const throw();

private:
  std::string mWhat;
};
class NullptrException : public std::exception
{
public:
  NullptrException();
  virtual const char* what() const throw();

private:
  std::string mWhat;
};
class EntryAlreadyExistsException : public std::exception
{
public:
  EntryAlreadyExistsException();
  virtual const char* what() const throw();

private:
  std::string mWhat;
};
class EntryDoesNotExistsException : public std::exception
{
public:
  EntryDoesNotExistsException(const std::string& entry);
  virtual const char* what() const throw();

private:
  std::string mWhat;
};
class CurlyBracesNotEvenCountException : public std::exception
{
public:
  CurlyBracesNotEvenCountException(const std::string& txt);
  virtual const char* what() const throw();

private:
  std::string mWhat;
};
class NoEqualSignAfterTypeNameException : public std::exception
{
public:
  NoEqualSignAfterTypeNameException(const std::string& txt);
  virtual const char* what() const throw();

private:
  std::string mWhat;
};
class TypeIsNotAFunctionException : public std::exception
{
public:
  TypeIsNotAFunctionException();
  virtual const char* what() const throw();

private:
  std::string mWhat;
};
class ToManyArgumentsException : public std::exception
{
public:
  ToManyArgumentsException(std::size_t current, std::size_t max);
  virtual const char* what() const throw();

private:
  std::string mWhat;
};
class FunctionNotFoundException : public std::exception
{
public:
  FunctionNotFoundException(const std::string& function);
  virtual const char* what() const throw();

private:
  std::string mWhat;
};
class CanNotParseFunctionNameException : public std::exception
{
public:
  CanNotParseFunctionNameException(const std::string& text);
  virtual const char* what() const throw();

private:
  std::string mWhat;
};
class FunctionAlreadyRegisteredException : public std::exception
{
public:
  FunctionAlreadyRegisteredException(const std::string& function);
  virtual const char* what() const throw();

private:
  std::string mWhat;
};
} // namespace chili::manun
