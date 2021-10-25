
all: main

CXXFLAGS = -lsystemc

main: main.cpp simple_process_ex.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@
