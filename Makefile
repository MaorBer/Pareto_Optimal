# Compiler
CXX := g++

# Compiler flags
CXXFLAGS := -std=c++11 -Wall -Wextra

# Executable names
TARGETS := naive dp

# Default target
all: $(TARGETS)

# Rule to build the naive solution
naive: NaiveSol.cpp
	$(CXX) $(CXXFLAGS) NaiveSol.cpp -o naive

# Rule to build the DP solution
dp: DPSol.cpp
	$(CXX) $(CXXFLAGS) DPSol.cpp -o dp

# Clean rule
clean:
	rm -f $(TARGETS) *.o
