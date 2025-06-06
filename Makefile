# Compiler settings
CXXFLAGS ?= --std=c++17 -Wall -Werror -pedantic -g -Wno-sign-compare -Wno-comment
CXXFLAGS += -fsanitize=address -fsanitize=undefined -D_GLIBCXX_DEBUG

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
