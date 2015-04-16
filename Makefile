TEST_SOURCES := ${shell find ./test/ -name *.cc}
TEST_HEADERS := ${shell find ./test/ -name *.hpp}
LIBRARY_INCLUDE := ./include
FLAGS = -std=gnu++11 -Wall
BINARY = test

all: test

clean:
	rm ./test/test

test:
	$(CXX) $(FLAGS) $(TEST_SOURCES) -I$(LIBRARY_INCLUDE) $(TEST_HEADERS) -o ./test/test

.PHONY: clean test
