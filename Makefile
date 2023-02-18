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
#
# NOTE: Static/Dynamic Library support is not yet added
################################################################################

CTEST         ?= test.c
CPPTEST       ?= test.cpp

ifeq ($(OS), Windows_NT)
	CTESTOUT   ?= ctest.exe
	CPPTESTOUT ?= cpptest.exe
else
	CTESTOUT   ?= ctest.out
	CPPTESTOUT ?= cpptest.out
endif

CFLAGS        ?= -Wall -Wextra
CPPFLAGS      ?= -Wall -Wextra

CINCLUDEDIR   ?= -I.
CPPINCLUDEDIR ?= -I.

CC            ?= gcc
CXX           ?= g++

CHEADER       ?= list.h
CPPHEADER     ?= list.hpp

.PHONY: all clean install uninstall

all: ctest cpptest

ctest: $(CTEST) $(CHEADER)
	$(CC) -o $(CTESTOUT) $(CTEST) $(CINCLUDEDIR) $(CFLAGS)

cpptest: $(CPPTEST) $(CPPHEADER)
	$(CXX) -o $(CPPTESTOUT) $(CPPTEST) $(CPPINCLUDEDIR) $(CPPFLAGS)

# Only works on GNU/Linux systems
install:
ifeq ($(shell whoami), root)
	cp ./list.h /usr/local/include/list.h
	cp ./list.hpp /usr/local/include/list.hpp
else
	echo "Root required, try sudo make install"
endif

uninstall:
ifeq ($(shell whoami), root)
	rm /usr/local/include/list.h
	rm /usr/local/include/list.hpp
else
	echo "Root required, try sudo make uninstall"
endif

clean:
ifeq ($(OS), Windows_NT)
	del ctest.exe
	del cpptest.exe
else
	rm ctest.out
	rm cpptest.out
endif
