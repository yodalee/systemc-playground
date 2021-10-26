
all: main

CXXFLAGS = -lsystemc

main: main.cpp counter.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@
