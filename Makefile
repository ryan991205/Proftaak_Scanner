PRODUCT=scanner

CFLAGS=-Wall -Werror -Wextra -pedantic -g -ggdb -O0

OPENCV = `pkg-config opencv --cflags --libs`

SOURCES=$(wildcard product/*.cpp)\
		$(wildcard product/*/*.cpp)

HEADERS=$(wildcard product/*.h) \
		$(wildcard product/*/*.h) 


TEST=test_$(PRODUCT)
TEST_SOURCES=$(filter-out product/main.cpp, $(SOURCES)) \
			 $(wildcard test/*.cpp)
TEST_HEADERS=$(HEADERS) \
			 $(wildcard test/*.h)
TEST_LIBS=-lgtest -lgmock -lgmock_main -lpthread

CC=g++

.phony: all clean test

all: $(PRODUCT)

$(PRODUCT): $(SOURCES) $(HEADERS) Makefile
	@$(CC) $(CFLAGS) -o $@ $(SOURCES) $(OPENCV)

$(TEST): $(TEST_SOURCES) $(TEST_HEADERS) Makefile
	@$(CC) $(CFLAGS) -Itest $(TEST_SOURCES) -o $@ $(TEST_LIBS)

clean:
	@rm -rf $(PRODUCT) $(TEST)

test: $(TEST)
	@./$(TEST) 2> /dev/null