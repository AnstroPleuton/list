################################################################################
# Copyright (c) 2023 Anstro Pleuton (@AnstroPleuton)
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sub-license, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.
#
# A Minimal Makefile to build the tests
################################################################################

.PHONY: all clean install uninstall

CC = gcc
CXX = g++
AR = ar

all: build static

clean:
	rm ctest.out
	rm cpptest.out
	rm clist.o
	rm cpplist.o
	rm liblist.a
	rm liblistpp.a

build: test.c test.cpp list.h list.hpp
	$(CC) -o ctest.out -Wall -Wextra test.c
	$(CXX) -o cpptest.out -Wall -Wextra test.cpp

static: list.c list.cpp list.h list.hpp
	$(CC) -c -o clist.o -Wall -Wextra list.c
	$(CXX) -c -o cpplist.o -Wall -Wextra list.cpp
	$(AR) r liblist.a clist.o
	$(AR) r liblistpp.a cpplist.o

install: static
ifeq ($(shell whoami), root)
	cp list.h /usr/local/include/
	cp list.hpp /usr/local/include/
	cp liblist.a /usr/local/lib/
	cp liblistpp.a /usr/local/lib/
else
	echo "Root permissions required, try sudo make install"
endif

uninstall:
ifeq ($(shell whoami), root)
	rm /usr/local/include/list.h
	rm /usr/local/include/list.hpp
	rm /usr/local/lib/liblist.a
	rm /usr/local/lib/liblistpp.a
else
	echo "Root permissions required, try sudo make install"
endif
