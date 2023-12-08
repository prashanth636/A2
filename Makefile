CXX=nvcc
CXXFLAGS=-std=c++11 -O3 

all: a3

a3: a3.cu a3.hpp a3.cpp
             $(CXX) $(CXXFLAGS) a3.cu -o a3_cu.o
	$(CXX) $(CXXFLAGS) a3.cpp a3_cu.o -o a3

a31: a32.cu a3.hpp a3.cpp
    $(CXX) $(CXXFLAGS) a3.cpp a3.cu -o a3

a32: a3.o a3_host.o
    $(CXX) $(CXXFLAGS) a3_host.o a3.o -o a3

a3.o: a3.cu a3.hpp
    $(CXX) $(CXXFLAGS) -c a3.cu -o a3.o

a3_host.o: a3.cpp a3.hpp
    $(CXX) $(CXXFLAGS) -c a3.cpp -o a3_host.o

clean:
    rm -rf a3