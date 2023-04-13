# Specify the C++ compiler to use
CXX=g++

# Specify the flags to use for compiling C++ code
CXXFLAGS=-std=c++11 -Wall -Wextra -pedantic -Iinclude/ -Iinclude/utils 

# Specify the flags to use for creating a static library
ARFLAGS=rcs

# Specify the source files to compile
SRCS=$(wildcard src/*.cpp)

# Specify the object files to create from the source files
OBJS=$(patsubst src/%.cpp,obj/%.o,$(SRCS))

# Specify the name of the library to create
LIB=bin/libcpptools.a

# Specify the name of the shared library to create
SHLIB=bin/libcpptools.so

#pkg name
PKG=cpptools

# pkg version
VERSION=0.0.0.1

PKG_FILE=$(PKG)_$(VERSION).tar.gz

# Specify the targets that are not files
.PHONY: all clean pkg

# Specify the default target to build
all: $(LIB) $(SHLIB) pkg

# Specify the target to build the static library
$(LIB): $(OBJS)
	ar $(ARFLAGS) $@ $^

# Specify the target to build the shared library
$(SHLIB): $(OBJS)
	$(CXX) -shared -o $@ $^

# Specify the target to clean up the object and library files
clean:
	rm -f $(OBJS) $(LIB) $(SHLIB)

# Specify the target to create object files from source files
obj/%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

pkg:
	mkdir -p pkg
	tar -czvf $(PKG_FILE) bin/ include/
	mv $(PKG_FILE)  pkg/




