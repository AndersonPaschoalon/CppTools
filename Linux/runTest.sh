#!/bin/bash
g++ -std=gnu++17 -Wdeprecated-declarations -fdiagnostics-color=always \
    -I./include/  \
	./test/*.cpp  \
    -o ./test/utest.exe \
	bin/libcpptools.a 




