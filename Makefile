CC := g++
CFLAGS = -std=c++17 -O2 -Wall -Wextra -Wpedantic -Wstrict-aliasing -MMD
CFLAGS += -I./lib/include -I./lib/glfw/include -I./lib/glm
ifeq ($(OS), Windows_NT)
    LDFLAGS = -L./lib/glfw/build/src -L./lib/glm/build/glm -lglfw3 -lm -lopengl32 -lgdi32 -luser32 
    MKDIR = if not exist 
    SLASH = \\
    GAME_BIN = $(BIN)$(SLASH)game.exe
else
    LDFLAGS = -L./lib/glfw/build/src -L./lib/glm/build/glm -lglfw3 -lm -lGL
    MKDIR = mkdir -p 
    SLASH = /
    GAME_BIN = $(BIN)$(SLASH)game
endif

SRC := $(wildcard src/*.cpp) $(wildcard src/**/*.cpp) $(wildcard src/**/**/*.cpp) src/util/glad.c
OBJ := $(patsubst src/%.cpp, obj/%.o, $(SRC:.c=.o))
BIN := bin

OBJ_DIRS := $(sort $(dir $(OBJ)))

DEP := $(OBJ:.o=.d)

.PHONY: all clean run dirs game lib

all: dirs game

game: $(OBJ)
	$(CC) -o $(GAME_BIN) $(OBJ) $(LDFLAGS)

obj/%.o: src/%.cpp | dirs
	$(CC) $(CFLAGS) -c $< -o $@

obj/%.o: src/util/%.c | dirs
	$(CC) $(CFLAGS) -c $< -o $@

dirs:
ifeq ($(OS), Windows_NT)
	$(MKDIR) $(BIN) $(SLASH)nul || mkdir $(BIN)
	@for %%d in ($(OBJ_DIRS)) do ($(MKDIR) "%%d" $(SLASH)nul || mkdir "%%d")
else
	$(MKDIR) $(BIN)
	$(MKDIR) $(OBJ_DIRS)
endif

run: all
	$(GAME_BIN)

lib:
	cd lib/glm && mkdir -p build && cd build && cmake .. && make 
	cd lib/glfw && mkdir -p build && cd build && cmake .. && make 

-include $(DEP)

clean:
ifeq ($(OS), Windows_NT)
	rd /s /q $(BIN)
	rd /s /q obj
else
	rm -rf $(BIN) obj
endif