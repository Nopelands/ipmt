SRCS = main.cpp sarr.cpp huffman.cpp lz77.cpp deflate.cpp

KERNEL = $(shell uname -s)
ifeq ($(KERNEL),Linux)
	EXE = ../bin/ipmt
else
	EXE = ../bin/ipmt.exe
endif

build:
	@mkdir -p ../bin
	g++ -o $(EXE) $(SRCS) -O3 -Wall -Wcast-qual -std=c++20

build-old:
	@mkdir -p ../bin
	g++ -o $(EXE) $(SRCS) -O3 -w

clean:
	@rm -f -r ../bin
