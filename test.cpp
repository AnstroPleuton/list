////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2023 Anstro Pleuton (@AnstroPleuton)
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sub-license, and/or sell
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
// Feature tests for the C++ Wrapper for the Minimal C Array
////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#define ARRAY_IMPL
#define PRINT_ERROR
#include "list.hpp"

int main()
{
	// Create an list
	aplib::list<int> myArray;

	// Print the size of the list
	std::cout << "Number of elements in list: "
	          << myArray.size() << std::endl;

	// Add an element at the end of an list
	myArray.insert(myArray.size());

	// Print the size of the list again
	std::cout << "Number of elements in list: "
	          << myArray.size() << std::endl;

	// Get the first element of an list
	int &element = myArray.at(0);

	// Alternative way using an operator
	element = myArray[0];

	// Set the first element of an list to 20
	element = 20;

	// Add an element at the beginning of an list
	myArray.insert(0);

	// Set the first element of an list to 40 in a different way
	myArray.at(0) = 40;

	// Alternative way using an operator
	myArray[0] = 40;

	// Immediately set the added element to 60
	myArray.insert(1, 60);

	// Print the size of the list again
	std::cout << "Number of elements in list: "
	          << myArray.size() << std::endl;

	// Print all the elements from an list
	for (size_t i = 0; i < myArray.size(); i++) {
		std::cout << "Element #" << i << ": "
		          << myArray[i] << std::endl;
	}

	// Print all the elements from an list using ranged for loop
	int n = 0;
	for (int &number : myArray) {
		std::cout << "Element #" << n++ << ": "
		          << number << std::endl;
	}

	// Remove an element from the end of an list
	myArray.erase(myArray.size() - 1);

	// Print the size of the list again
	std::cout << "Number of elements in list: "
	          << myArray.size() << std::endl;

	// Remove an element from the beginning of an list
	myArray.erase(0);

	// Clear the elements from the list
	myArray.clear();

	// Print the size of the list again
	std::cout << "Number of elements in list: "
	          << myArray.size() << std::endl;

	// Array is automatically deleted when it goes out of scope
}

// Expected output:
//
// Number of elements in list: 0
// Number of elements in list: 1
// Number of elements in list: 3
// Element #0: 40
// Element #1: 60
// Element #2: 20
// Element #0: 40
// Element #1: 60
// Element #2: 20
// Number of elements in list: 2
// Number of elements in list: 0
