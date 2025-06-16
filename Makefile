CXX = g++
CXXFLAGS ?= --std=c++17 -Wall -Werror -pedantic -g -Wno-sign-compare -Wno-comment
CXXFLAGS += -fsanitize=address -fsanitize=undefined -pthread
CPPFLAGS = -Iinclude

# Compiler source files
SRCS := $(shell find src -name '*.cpp')
TARGET = compile

# === Default: build compiler ===
all: $(TARGET)

compiler: $(TARGET)

$(TARGET): $(SRCS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $^ -o $@

# === Google Test ===
TEST_BIN = test_runner

test: $(TEST_BIN)
	./$(TEST_BIN)

$(TEST_BIN): tests/*.cpp $(SRCS) \
             third_party/googletest/googletest/src/gtest-all.cc \
             third_party/googletest/googletest/src/gtest_main.cc
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) \
		-Ithird_party/googletest/googletest/include \
		-Ithird_party/googletest/googletest \
		$^ -o $@

# === Clean ===
clean:
	rm -f $(TARGET) $(TEST_BIN)
