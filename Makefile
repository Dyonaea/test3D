CC := g++
CFLAGS = -std=c++17 -g -Wall -Wextra -Wpedantic -Wstrict-aliasing
CFLAGS += -I./lib/include
LDFLAGS = -lm -lglfw -lGL

SRC := $(wildcard src/*.cpp) $(wildcard src/**/*.cpp) $(wildcard src/**/**/*.cpp) src/util/glad.c
BIN := bin

.PHONY: all clean run dirs game

all: dirs game

game:
	$(CC) -o $(BIN)/game $(SRC) $(CFLAGS) $(LDFLAGS)

run: all
	$(BIN)/game

clean:
	rm -rf $(BIN) $(wildcard src/*.o)

dirs:
	mkdir -p $(BIN)