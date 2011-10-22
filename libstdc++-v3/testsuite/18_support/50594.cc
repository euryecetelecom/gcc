// { dg-options "-fwhole-program" }

// Copyright (C) 2011 Free Software Foundation
//
// This file is part of the GNU ISO C++ Library.  This library is free
// software; you can redistribute it and/or modify it under the
// terms of the GNU General Public License as published by the
// Free Software Foundation; either version 3, or (at your option)
// any later version.

// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License along
// with this library; see the file COPYING3.  If not see
// <http://www.gnu.org/licenses/>.

#include <new>
#include <string>
#include <cstdlib>
#include <testsuite_hooks.h>

bool user_new_called;
bool user_delete_called;

void* operator new(std::size_t n)
#ifndef __GXX_EXPERIMENTAL_CXX0X__
  throw(std::bad_alloc)
#endif
{
  user_new_called = true;

  void* p = std::malloc(n);

  if (!p)
    throw std::bad_alloc();

  return p;
}

void operator delete(void* p)
#ifdef __GXX_EXPERIMENTAL_CXX0X__
  noexcept
#else
  throw()
#endif
{
  user_delete_called = true;

  std::free(p);
}

// libstdc++/50594
void test01()
{
  bool test __attribute__((unused)) = true;

  {
    std::string s = "Hello World.";
  }

  VERIFY( user_new_called );
  VERIFY( user_delete_called );
}

int main()
{
  test01();
  return 0;
}
