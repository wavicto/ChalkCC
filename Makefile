# Compiler settings
CXX = g++
CXXFLAGS ?= --std=c++17 -Wall -Werror -pedantic -g -Wno-sign-compare -Wno-comment
CXXFLAGS += -fsanitize=address -fsanitize=undefined
CPPFLAGS = -Iinclude

# Recursively include all .cpp source files under src/
SRCS := $(shell find src -name '*.cpp')

# Target executable
TARGET = compile

# Default rule
all: $(TARGET)

$(TARGET): $(SRCS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $^ -o $@

# Clean rule
clean:
	rm -f $(TARGET)

.PHONY: all clean
