CXX=nvcc
CXXFLAGS=-std=c++17 -O3 

all: a3

a3: a3.cu a3.hpp a3.cpp
	$(CXX) $(CXXFLAGS) a3.cpp a3.cu -o a3

clean:
	rm -rf a3
