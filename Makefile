CXX=nvcc
CXXFLAGS=-std=c++11 -O3

all: a3

a3: a3_cu.o a3_host.o
	$(CXX) $(CXXFLAGS) a3_cu.o a3_host.o -o a3 -lcudart -lstdc++

a3_cu.o: a3.cu a3.hpp
	$(CXX) $(CXXFLAGS) -c a3.cu -o a3_cu.o

a3_host.o: a3.cpp a3.hpp
	$(CXX) $(CXXFLAGS) -c a3.cpp -o a3_host.o

clean:
	rm -rf a3 a3_cu.o a3_host.o