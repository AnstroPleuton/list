////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2023 Anstro Pleuton (@AnstroPleuton)
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//
// A C++ Wrapper and controller for the Minimal C Dynamic List
//
// Usage and other information is provided in the README.md file from the
// repository. Please refer to that to know how to use this library.
////////////////////////////////////////////////////////////////////////////////

#ifndef LIST_HPP
#define LIST_HPP "list.hpp"

// This header is just a wrapper for the Minimal C Dynamic List
#include "list.h"

namespace aplib
{
template<typename type_t>
class list
{
public:
	class iterator;
private:
	list_t *internal_list;
public:

	list();
	~list();

	list<type_t> &insert(size_t index);
	list<type_t> &insert(size_t index, type_t value);
	list<type_t> &erase(size_t index);

	size_t size();
	type_t &at(size_t index);
	list<type_t> &clear();

	list<type_t> &push_back();
	list<type_t> &push_back(type_t value);
	list<type_t> &pop_back();

	class iterator
	{
		list_t *list;
		size_t index;
	public:
		iterator(list_t *internal_list);
		iterator() = default;

		iterator &operator++();
		bool operator!=(const iterator &compare);
		type_t &operator*();

		friend class list;
	};
	friend class iterator;

	iterator begin();
	iterator end();

	type_t &operator[](size_t index);
};
}

#ifdef LIST_IMPL

template<typename type_t>
aplib::list<type_t>::list()
{
	internal_list = create_list(sizeof(type_t));
}

template<typename type_t>
aplib::list<type_t>::~list()
{
	delete_list(internal_list);
}

template<typename type_t>
aplib::list<type_t> &aplib::list<type_t>::insert(size_t index)
{
	add_element(internal_list, index);
	return *this;
}

template<typename type_t>
aplib::list<type_t> &aplib::list<type_t>::insert(size_t index, type_t value)
{
	*(type_t *) add_element(internal_list, index)->data = value;
	return *this;
}

template<typename type_t>
aplib::list<type_t> &aplib::list<type_t>::erase(size_t index)
{
	remove_element(internal_list, index);
	return *this;
}

template<typename type_t>
size_t aplib::list<type_t>::size()
{
	return get_list_size(internal_list);
}

template<typename type_t>
type_t &aplib::list<type_t>::at(size_t index)
{
	return *(type_t *) get_element(internal_list, index)->data;
}

template<typename type_t>
aplib::list<type_t> &aplib::list<type_t>::clear()
{
	clear_list(internal_list);
	return *this;
}

template<typename type_t>
aplib::list<type_t> &aplib::list<type_t>::push_back()
{
	insert(size());
	return *this;
}

template<typename type_t>
aplib::list<type_t> &aplib::list<type_t>::push_back(type_t value)
{
	insert(size(), value);
	return *this;
}

template<typename type_t>
aplib::list<type_t> &aplib::list<type_t>::pop_back()
{
	erase(size());
	return *this;
}

template<typename type_t>
aplib::list<type_t>::iterator::iterator(list_t *internal_list)
	: list(internal_list)
{
	index = 0;
}

template<typename type_t>
typename aplib::list<type_t>::iterator &
aplib::list<type_t>::iterator::operator++()
{
	index++;
	return *this;
}

template<typename type_t>
bool aplib::list<type_t>::iterator::operator!=(const
        aplib::list<type_t>::iterator& compare)
{
	return index != compare.index;
}

template<typename type_t>
type_t &aplib::list<type_t>::iterator::operator*()
{
	return *(type_t *) get_element(list, index)->data;
}

template<typename type_t>
typename aplib::list<type_t>::iterator aplib::list<type_t>::begin()
{
	iterator beginning(internal_list);
	beginning.index = 0;
	return beginning;
}

template<typename type_t>
typename aplib::list<type_t>::iterator aplib::list<type_t>::end()
{
	iterator ending(internal_list);
	ending.index = size();
	return ending;
}

template<typename type_t>
type_t &aplib::list<type_t>::operator[](size_t index)
{
	return at(index);
}

// LIST_IMPL
#endif

// LIST_HPP
#endif
