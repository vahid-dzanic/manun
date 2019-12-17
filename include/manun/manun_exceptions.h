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

namespace manun {

class type_mismatch_exception : public std::exception
{
public:
  type_mismatch_exception(const std::string& expectedType, const std::string& parsedType);
  virtual const char* what() const throw();

private:
  std::string mWhat;
};
class nullptr_exception : public std::exception
{
public:
  nullptr_exception();
  virtual const char* what() const throw();

private:
  std::string mWhat;
};
class entry_already_exists_exception : public std::exception
{
public:
  entry_already_exists_exception();
  virtual const char* what() const throw();

private:
  std::string mWhat;
};
class entry_does_not_exists_exception : public std::exception
{
public:
  entry_does_not_exists_exception(const std::string& entry);
  virtual const char* what() const throw();

private:
  std::string mWhat;
};
class curly_braces_not_even_count_exception : public std::exception
{
public:
  curly_braces_not_even_count_exception(const std::string& txt);
  virtual const char* what() const throw();

private:
  std::string mWhat;
};
class no_equal_sign_after_type_name_exception : public std::exception
{
public:
  no_equal_sign_after_type_name_exception(const std::string& txt);
  virtual const char* what() const throw();

private:
  std::string mWhat;
};
class type_is_not_a_function_exception : public std::exception
{
public:
  type_is_not_a_function_exception();
  virtual const char* what() const throw();

private:
  std::string mWhat;
};
class to_many_arguments_exception : public std::exception
{
public:
  to_many_arguments_exception(std::size_t current, std::size_t max);
  virtual const char* what() const throw();

private:
  std::string mWhat;
};
class function_not_found_exception : public std::exception
{
public:
  function_not_found_exception(const std::string& function);
  virtual const char* what() const throw();

private:
  std::string mWhat;
};
class can_not_parse_function_name_exception : public std::exception
{
public:
  can_not_parse_function_name_exception(const std::string& text);
  virtual const char* what() const throw();

private:
  std::string mWhat;
};
class function_already_registered_exception : public std::exception
{
public:
  function_already_registered_exception(const std::string& function);
  virtual const char* what() const throw();

private:
  std::string mWhat;
};
} // namespace manun
