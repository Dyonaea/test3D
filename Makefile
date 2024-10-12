CC := g++
CFLAGS = -std=c++17 -g -Wall -Wextra -Wpedantic -Wstrict-aliasing
CFLAGS += -I./lib/include
LDFLAGS =  -lm -lglfw -lGL

SRC := $(wildcard src/*.cpp) $(wildcard src/**/*.cpp) $(wildcard src/**/**/*.cpp) src/util/glad.c
OBJ := $(patsubst src/%.cpp, obj/%.o, $(SRC:.c=.o))
BIN := bin


OBJ_DIRS := $(sort $(dir $(OBJ)))

.PHONY: all clean run dirs game lib

all: dirs game

game: $(OBJ)
	$(CC) -o $(BIN)/game $(OBJ) $(LDFLAGS)

obj/%.o: src/%.cpp | dirs
	$(CC) $(CFLAGS) -c $< -o $@

obj/%.o: src/util/%.c | dirs
	$(CC) $(CFLAGS) -c $< -o $@

dirs:
	mkdir -p $(BIN)
	mkdir -p $(OBJ_DIRS)

run: all
	$(BIN)/game

lib: 
	cd lib/glm && mkdir -p build && cd build && cmake .. && make 
	cd lib/glfw && mkdir -p build && cd build && cmake .. && make 

clean:
	rm -rf $(BIN) obj