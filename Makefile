# Compiler settings
CXXFLAGS ?= --std=c++17 -Wall -Werror -pedantic -g -Wno-sign-compare -Wno-comment
CXXFLAGS += -fsanitize=address -fsanitize=undefined -D_GLIBCXX_DEBUG
CPPFLAGS = -Iinclude

# Source files
SRCS = src/compiler_driver.cpp src/codegen.cpp src/lexer.cpp src/parser.cpp src/token.cpp src/c_visitor.cpp src/asm_visitor.cpp

# Target executable
TARGET = compile

# Default rule
all:
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(SRCS) -o $(TARGET)

# Clean rule
clean:
	rm -f $(TARGET)