#------------------------------------------------------------------------------
# @file Makefile
# @brief Build configuration for the Load Balancer Simulation project.
#
# This Makefile compiles all source files into object files and links them
# into a single executable target.
#
# Targets:
#   all    - Builds the executable
#   clean  - Removes compiled objects and executable
#
# Usage:
#   make        # Build the project
#   make clean  # Remove build artifacts
#------------------------------------------------------------------------------

#------------------------------------------------------------------------------
# Compiler configuration
#------------------------------------------------------------------------------

# C++ compiler to use
CXX = g++

# Compiler flags:
#   -std=c++17  → Use C++17 standard
#   -Wall       → Enable common warnings
#   -Wextra     → Enable additional warnings
#   -O2         → Enable optimization level 2
CXXFLAGS = -std=c++17 -Wall -Wextra -O2

#------------------------------------------------------------------------------
# Source files
#------------------------------------------------------------------------------

# List of all .cpp source files in the project
SRCS = main.cpp IPAddress.cpp Request.cpp RequestQueue.cpp WebServer.cpp LoadBalancer.cpp Switch.cpp SwitchConfig.cpp

# Automatically generate object file names from source files
OBJS = $(SRCS:.cpp=.o)

#------------------------------------------------------------------------------
# Target executable
#------------------------------------------------------------------------------

# Name of the final executable
TARGET = test

#------------------------------------------------------------------------------
# Build rules
#------------------------------------------------------------------------------

# Default target
all: $(TARGET)

# Link object files into final executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

#------------------------------------------------------------------------------
# Cleanup
#------------------------------------------------------------------------------

# Remove compiled object files and executable
clean:
	rm -f $(OBJS) $(TARGET)

# Declare phony targets (not actual files)
.PHONY: all clean