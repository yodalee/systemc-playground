
all: main

CXXFLAGS = -lsystemc

main: main.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@
