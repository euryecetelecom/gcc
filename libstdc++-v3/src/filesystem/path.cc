// Class filesystem::path -*- C++ -*-

// Copyright (C) 2014 Free Software Foundation, Inc.
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

// Under Section 7 of GPL version 3, you are granted additional
// permissions described in the GCC Runtime Library Exception, version
// 3.1, as published by the Free Software Foundation.

// You should have received a copy of the GNU General Public License and
// a copy of the GCC Runtime Library Exception along with this program;
// see the files COPYING3 and COPYING.RUNTIME respectively.  If not, see
// <http://www.gnu.org/licenses/>.

#include <experimental/filesystem>

using std::experimental::filesystem::path;

constexpr path::value_type path::preferred_separator;

path&
path::remove_filename()
{
  if (_M_type == _Type::_Multi)
    {
      if (!_M_cmpts.empty())
	{
	  auto cmpt = --_M_cmpts.end();
	  _M_pathname.erase(cmpt->_M_pos);
	  _M_cmpts.erase(cmpt);
	  _M_trim();
	}
    }
  else
    clear();
  return *this;
}

path&
path::replace_filename(const path& replacement)
{
  remove_filename();
  operator/=(replacement);
  return *this;
}

path&
path::replace_extension(const path& replacement)
{
  path fname = _M_split_filename(filename(), _Split::_Stem);
  if (!replacement.empty() && replacement.native()[0] != '.')
    fname._M_pathname += '.';
  // TODO fname += replacement;
  replace_filename(fname);
  return *this;
}

namespace
{
  template<typename Iter1, typename Iter2>
    int do_compare(Iter1 begin1, Iter1 end1, Iter2 begin2, Iter2 end2)
    {
      int cmpt = 1;
      while (begin1 != end1 && begin2 != end2)
	{
	  if (begin1->native() < begin2->native())
	    return -cmpt;
	  if (begin1->native() > begin2->native())
	    return +cmpt;
	  ++begin1;
	  ++begin2;
	  ++cmpt;
	}
      if (begin1 == end1)
	{
	  if (begin2 == end2)
	    return 0;
	  return -cmpt;
	}
      return +cmpt;
    }
}

int
path::compare(const path& p) const noexcept
{
  if (_M_type == _Type::_Multi && p._M_type == _Type::_Multi)
    return do_compare(_M_cmpts.begin(), _M_cmpts.end(),
		   p._M_cmpts.begin(), p._M_cmpts.end());
  else if (_M_type == _Type::_Multi)
    {
      _Cmpt c[1] = { { p._M_pathname, p._M_type, 0 } };
      return do_compare(_M_cmpts.begin(), _M_cmpts.end(), c, c+1);
    }
  else if (p._M_type == _Type::_Multi)
    {
      _Cmpt c[1] = { { _M_pathname, _M_type, 0 } };
      return do_compare(c, c+1, p._M_cmpts.begin(), p._M_cmpts.end());
    }
  else
    return _M_pathname.compare(p._M_pathname);
}

path
path::root_name() const
{
  path __ret;
  if (_M_type == _Type::_Root_name)
    __ret = *this;
  else if (_M_cmpts.size()
      && _M_cmpts.begin()->_M_type == _Type::_Root_name)
    __ret = *_M_cmpts.begin();
  return __ret;
}

path
path::root_directory() const
{
  path __ret;
  if (_M_type == _Type::_Root_dir)
    __ret = *this;
  else if (!_M_cmpts.empty())
    {
      auto __it = _M_cmpts.begin();
      if (__it->_M_type == _Type::_Root_name)
        ++__it;
      if (__it != _M_cmpts.end() && __it->_M_type == _Type::_Root_dir)
        __ret = *__it;
    }
  return __ret;
}


path
path::root_path() const
{
  path __ret;
  if (_M_type == _Type::_Root_name || _M_type == _Type::_Root_dir)
    __ret = *this;
  else if (!_M_cmpts.empty())
    {
      auto __it = _M_cmpts.begin();
      if (__it->_M_type == _Type::_Root_name)
        {
          __ret = *__it++;
          if (__it != _M_cmpts.end() && __it->_M_type == _Type::_Root_dir)
            {
              __ret._M_pathname += preferred_separator;
              __ret._M_split_cmpts();
            }
        }
      else if (__it->_M_type == _Type::_Root_dir)
        __ret = *__it;
    }
  return __ret;
}

path
path::relative_path() const
{
  path __ret;
  if (_M_type == _Type::_Filename)
    __ret = *this;
  else if (!_M_cmpts.empty())
    {
      auto __it = _M_cmpts.begin();
      if (__it->_M_type == _Type::_Root_name)
        ++__it;
      if (__it != _M_cmpts.end() && __it->_M_type == _Type::_Root_dir)
        ++__it;
      if (__it != _M_cmpts.end())
        __ret.assign(_M_pathname.substr(__it->_M_pos));
    }
  return __ret;
}

path
path::parent_path() const
{
  path __ret;
  if (_M_cmpts.size() < 2)
    return __ret;
  for (auto __it = _M_cmpts.begin(), __end = --_M_cmpts.end();
      __it != __end; ++__it)
    {
      __ret /= *__it;
    }
  return __ret;
}

path
path::_M_split_filename(path filename, _Split which) const
{
  auto pos = string_type::npos;
  if (filename._M_pathname.size() < 3
      && filename._M_pathname.find_first_not_of('.') == string_type::npos)
    pos = filename._M_pathname.size();
  else
    pos = filename._M_pathname.find_last_of('.');
  if (which == _Split::_Stem)
    filename._M_pathname.erase(pos);
  else
    filename._M_pathname.erase(0, pos);
  return filename;
}

bool
path::has_root_name() const
{
  if (_M_type == _Type::_Root_name)
    return true;
  if (!_M_cmpts.empty() && _M_cmpts.begin()->_M_type == _Type::_Root_name)
    return true;
  return false;
}

bool
path::has_root_directory() const
{
  if (_M_type == _Type::_Root_dir)
    return true;
  if (!_M_cmpts.empty())
    {
      auto __it = _M_cmpts.begin();
      if (__it->_M_type == _Type::_Root_name)
        ++__it;
      if (__it != _M_cmpts.end() && __it->_M_type == _Type::_Root_dir)
        return true;
    }
  return false;
}

bool
path::has_root_path() const
{
  if (_M_type == _Type::_Root_name || _M_type == _Type::_Root_dir)
    return true;
  if (!_M_cmpts.empty())
    {
      auto __type = _M_cmpts.front()._M_type;
      if (__type == _Type::_Root_name || __type == _Type::_Root_dir)
        return true;
    }
  return false;
}

bool
path::has_relative_path() const
{
  if (_M_type == _Type::_Filename)
    return true;
  if (!_M_cmpts.empty())
    {
      auto __it = _M_cmpts.begin();
      if (__it->_M_type == _Type::_Root_name)
        ++__it;
      if (__it != _M_cmpts.end() && __it->_M_type == _Type::_Root_dir)
        ++__it;
      if (__it != _M_cmpts.end())
        return true;
    }
  return false;
}


bool
path::has_parent_path() const
{
  return _M_cmpts.size() > 1;
}

bool
path::has_filename() const
{
  return !empty();
}

bool
path::has_stem() const
{
  return false; // TODO
}

bool
path::has_extension() const
{
  return false; // TODO
}

void
path::_M_split_cmpts()
{
  _M_type = _Type::_Multi;
  _M_cmpts.clear();

  if (_M_pathname.empty())
    return;

  size_t pos = 0;
  const size_t len = _M_pathname.size();

  // look for root name or root directory
  if (_S_is_dir_sep(_M_pathname[0]))
    {
      // look for root name, such as "//" or "//foo"
      if (len > 1 && _M_pathname[1] == _M_pathname[0])
	{
	  if (len == 2)
	    {
	      // entire path is just "//"
	      _M_type = _Type::_Root_name;
	      return;
	    }

	  if (!_S_is_dir_sep(_M_pathname[2]))
	    {
	      // got root name, find its end
	      pos = 3;
	      while (pos < len && !_S_is_dir_sep(_M_pathname[pos]))
		++pos;
	      _M_add_root_name(pos);
	      if (pos < len) // also got root directory
		_M_add_root_dir(pos);
	    }
	  else
	    {
	      // got something like "///foo" which is just a root directory
	      // composed of multiple redundant directory separators
	      _M_add_root_dir(0);
	    }
	}
      else // got root directory
	_M_add_root_dir(0);
      ++pos;
    }
#ifdef _GLIBCXX_FILESYSTEM_IS_WINDOWS
  else if (len > 1 && _M_pathname[1] == L':')
    {
      // got disk designator
      _M_add_root_name(2);
      if (len > 2 && _S_is_dir_sep(_M_pathname[2]))
	_M_add_root_dir(2);
      pos = 2;
    }
#endif

  size_t back = pos;
  while (pos < len)
    {
      if (_S_is_dir_sep(_M_pathname[pos]))
	{
	  if (back != pos)
	    _M_add_filename(back, pos - back);
	  back = ++pos;
	}
      else
	++pos;
    }

  if (back != pos)
    _M_add_filename(back, pos - back);
  else if (_S_is_dir_sep(_M_pathname.back()))
    {
      // [path.itr]/8
      // "Dot, if one or more trailing non-root slash characters are present."
      if (_M_cmpts.back()._M_type == _Type::_Filename)
	{
	  const auto& last = _M_cmpts.back();
	  pos = last._M_pos + last._M_pathname.size();
	  _M_cmpts.emplace_back(string_type(1, '.'), _Type::_Filename, pos);
	}
    }

  _M_trim();
}

void
path::_M_add_root_name(size_t n)
{
  _M_cmpts.emplace_back(_M_pathname.substr(0, n), _Type::_Root_name, 0);
}

void
path::_M_add_root_dir(size_t pos)
{
  _M_cmpts.emplace_back(_M_pathname.substr(pos, 1), _Type::_Root_dir, pos);
}

void
path::_M_add_filename(size_t pos, size_t n)
{
  _M_cmpts.emplace_back(_M_pathname.substr(pos, n), _Type::_Filename, pos);
}

void
path::_M_trim()
{
  if (_M_cmpts.size() == 1)
    {
      _M_type = _M_cmpts.front()._M_type;
      _M_cmpts.clear();
    }
}

path::string_type
path::_S_convert_loc(const char* __first, const char* __last,
               const std::locale& __loc)
{
  auto& __cvt = use_facet<std::codecvt<wchar_t, char, mbstate_t>>(__loc);
  mbstate_t __st = mbstate_t();
  size_t __len = __cvt.length(__st, __first, __last,
                              (__last - __first) * __cvt.max_length());
  std::wstring __out(__len, L'\0');
  auto __outnext = &__out.front();
  __st = mbstate_t();
  auto __res = __cvt.in(__st, __first, __last, __first,
                        __outnext, &__out.back() + 1, __outnext);
  if (__res == codecvt_base::ok && __first == __last)
    return _Cvt<wchar_t>::_S_convert(&__out.front(), __outnext);
  _GLIBCXX_THROW_OR_ABORT(filesystem_error(
	"Cannot convert character sequence",
	std::make_error_code(errc::illegal_byte_sequence)));
}

#if 0
// template class std::list<path::_Cmpt>;

template void std::list<path::_Cmpt>::_M_assign_dispatch<std::experimental::filesystem::v1::path::_Cmpt const*>(path::_Cmpt const*, path::_Cmpt const*, std::__false_type);
#endif
