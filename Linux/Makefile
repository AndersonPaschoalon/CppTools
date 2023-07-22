# Specify the C++ compiler to use
CXX=g++

# lib include directories
LIB_INCLUDES=-Iinclude/ -Iinclude/console -Iinclude/csv -Iinclude/utils -Iinclude/unity  -Iinclude/thread

# Specify the flags to use for compiling C++ code
CXXFLAGS=-std=c++11 -Wall -Wextra -Wunused -pedantic -fPIC $(LIB_INCLUDES)


# Specify the flags to use for creating a static library
ARFLAGS=rcs

# Specify the source files to compile
SRCS=$(wildcard src/*.cpp)

# Specify the source files to compile
UTEST_SRCS=$(wildcard test/src/*.cpp)

# Specify the source files to compile
UTEST_INCLUDES=-Itest/include

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

# lib package
PKG_FILE=$(PKG)_$(VERSION).tar.gz

# test exe
UTEST_EXE=./test/utest.exe

# Specify the targets that are not files
.PHONY: all clean pkg run-test

# Specify the default target to build
all: $(LIB) $(SHLIB) pkg build-test run-test

# Specify the target to build the static library
$(LIB): $(OBJS)
	printf "\n\n# Building static library...\n"
	ar $(ARFLAGS) $@ $^

# Specify the target to build the shared library
$(SHLIB): $(OBJS)
	printf "\n\n# Building shared library...\n"
	$(CXX) -shared -o $@ $^

# Specify the target to clean up the object and library files
clean:
	printf "\n\n# Cleaning project...\n"
	rm -f $(OBJS) $(LIB) $(SHLIB) pkg/$(PKG_FILE) $(UTEST_EXE)

# Specify the target to create object files from source files
obj/%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

# create a package to be used on other projects
pkg:
	printf "# Packaging library..."
	mkdir -p pkg
	tar -czvf $(PKG_FILE) bin/ include/
	mv $(PKG_FILE)  pkg/

build-test: $(LIB) $(UTEST_SRCS)
	printf "# Building Unity Tests..."
	$(CXX) $(CXXFLAGS) $(UTEST_INCLUDES) $(UTEST_SRCS) -o ${UTEST_EXE} $(LIB)

run-test:
	printf "\n\n# Running Unity Tests...\n"
	$(UTEST_EXE)












