# Compiler settings
CXX = g++
CXXFLAGS = -Wall -Wextra -Wno-unused-parameter -std=c++17

# Source files
SRCS = compiler_driver.cpp codegen.cpp lexer.cpp parser.cpp token.cpp visitor.cpp

# Target executable
TARGET = compile

# Default rule
all:
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(TARGET)

# Clean rule
clean:
	rm -f $(TARGET)
