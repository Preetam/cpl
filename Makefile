TEST_SOURCES := ${shell find ./test/ -name *.cc}
TEST_HEADERS := ${shell find ./test/ -name *.hpp}
LIBRARY_INCLUDE := ./include
FLAGS = -std=c++0x -Wall
TEST_BINARY = ./test/test

all: test_build test_run test_leaks

clean:
	rm ./test/test

test_build:
	$(CXX) $(FLAGS) $(TEST_SOURCES) -I$(LIBRARY_INCLUDE) $(TEST_HEADERS) -o $(TEST_BINARY)

test_run:
	$(TEST_BINARY)

test_leaks:
	valgrind --leak-check=full --show-leak-kinds=all $(TEST_BINARY)

.PHONY: clean test test_leaks
