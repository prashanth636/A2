CXX=nvcc
CXXFLAGS=-std=c++11

all: a3

a3: a3.cu a3.hpp a3.cpp
	$(CXX) $(CXXFLAGS) a3.cu -o a3_cu.o
	$(CXX) $(CXXFLAGS) a3.cpp a3_cu.o -o a3