# Compiler settings
CXX = g++
CXXFLAGS ?= --std=c++17 -Wall -Werror -pedantic -g -Wno-sign-compare -Wno-comment
CXXFLAGS += -fsanitize=address -fsanitize=undefined
CPPFLAGS = -Iinclude

# Automatically include all source files in src/
SRCS := $(wildcard src/*.cpp)

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
