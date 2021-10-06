OBJDIR=build
VPATH=$(OBJDIR)

all: main test
main: main.cpp funcs.o
	mkdir -p  -p $(OBJDIR)
	g++ -lm -O2 -fno-stack-limit -std=c++1z -x c++ main.cpp funcs.cpp -o $(OBJDIR)/main

test: funcs.o test.o
	mkdir -p  $(OBJDIR)
	g++ -o $(OBJDIR)/test \
		$(OBJDIR)/test.o $(OBJDIR)/funcs.o \
		-g -ggdb -lm -O0 -fno-stack-limit -std=c++1z -x c++ \
		-I./include/Catch/single_include/catch2 \

test.o: funcs.o test.cpp include/Catch/single_include/catch2/catch.hpp
	mkdir -p  $(OBJDIR)
	g++ -o $(OBJDIR)/test.o \
		-g -ggdb -lm -O0 -fno-stack-limit -std=c++1z -x c++ \
		-I./include/Catch/single_include/catch2 \
		-c test.cpp

funcs.o: funcs.cpp funcs.h
	mkdir -p  $(OBJDIR)
	g++ -o $(OBJDIR)/funcs.o \
		-g -ggdb -lm -O0 -fno-stack-limit -std=c++1z -x c++ \
		-I../ \
		-c funcs.cpp

clean:
	rm -rf *.o ./build/*
