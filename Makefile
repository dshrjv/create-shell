# Compiler and flags
CXX = g++
CC = gcc
CXXFLAGS = -Wall -Wextra -std=c++11 -g
CFLAGS = -Wall -Wextra -g

# Target executables
TARGET = myshell
SLOW_TARGET = slow
TESTME_TARGET = testme
PRIME_TARGET = prime

# Source files
SOURCES = myshell.cpp param.cpp parse.cpp

# Object files
OBJECTS = $(SOURCES:.cpp=.o)

# Header files
HEADERS = param.hpp parse.hpp

# Default target - build all programs
all: $(TARGET) $(SLOW_TARGET) $(TESTME_TARGET) $(PRIME_TARGET)

# Link the executables
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)

$(SLOW_TARGET): slow.c
	$(CC) $(CFLAGS) -o $(SLOW_TARGET) slow.c

$(TESTME_TARGET): testme.c
	$(CC) $(CFLAGS) -o $(TESTME_TARGET) testme.c

$(PRIME_TARGET): prime.c
	$(CC) $(CFLAGS) -o $(PRIME_TARGET) prime.c

# Compile source files to object files
%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up build files
clean:
	rm -f $(OBJECTS) $(TARGET) $(SLOW_TARGET) $(TESTME_TARGET) $(PRIME_TARGET)

# Phony targets
.PHONY: all clean

# Dependencies
myshell.o: myshell.cpp param.hpp
param.o: param.cpp param.hpp
parse.o: parse.cpp parse.hpp param.hpp