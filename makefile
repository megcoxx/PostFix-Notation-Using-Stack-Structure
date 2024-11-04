# Makefile for compiling stack and in2post

# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -Wall -Wextra -std=c++11

# Target executable
TARGET = in2post

# Source files
SRCS = in2post.cpp

# Header files
HEADERS = stack.h stack.hpp

# Build the target
all: $(TARGET)

$(TARGET): $(SRCS) $(HEADERS)
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(TARGET)

# Clean up build files
clean:
	rm -f $(TARGET)

.PHONY: all clean