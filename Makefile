CC := g++
CFLAGS = -std=c++17 -O2 -Wall -Wextra -Wpedantic -Wstrict-aliasing -MMD
CFLAGS += -I./lib/include -I./lib/glfw/include -I./lib/glm
LDFLAGS = -L./lib/glfw/build/src -L./lib/glm/build/glm -lglfw3 -lm -lGL

SRC := $(wildcard src/*.cpp) $(wildcard src/**/*.cpp) $(wildcard src/**/**/*.cpp) src/util/glad.c
OBJ := $(patsubst src/%.cpp, obj/%.o, $(SRC:.c=.o))
BIN := bin

OBJ_DIRS := $(sort $(dir $(OBJ)))

# Add a variable for dependency files
DEP := $(OBJ:.o=.d)

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

# Include the dependency files
-include $(DEP)

clean:
	rm -rf $(BIN) obj