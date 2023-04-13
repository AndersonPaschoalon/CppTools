# Specify the C++ compiler to use
CXX=g++

# Specify the flags to use for compiling C++ code
CXXFLAGS=-std=c++11 -Wall -Wextra -pedantic -Iheaders

# Specify the flags to use for creating a static library
ARFLAGS=rcs

# Specify the source files to compile
SRCS=$(wildcard src/*.cpp)

# Specify the object files to create from the source files
OBJS=$(patsubst src/%.cpp,obj/%.o,$(SRCS))

# Specify the name of the library to create
LIB=bin/libcpputils.a

# Specify the name of the shared library to create
SHLIB=bin/libcpputils.so

# Specify the targets that are not files
.PHONY: all clean

# Specify the default target to build
all: $(LIB) $(SHLIB)

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