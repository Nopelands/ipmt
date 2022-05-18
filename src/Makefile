SRCS = main.cpp sarr.cpp lz77.cpp boyer_moore.cpp shift_or.cpp #deflate.cpp huffman.cpp

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
