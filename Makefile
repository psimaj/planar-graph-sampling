FLAGS    := -pedantic-errors -Wall -Wextra -Werror -std=c++14
BUILD    := ./build
OBJ_DIR  := $(BUILD)/objects
BIN_DIR  := $(BUILD)/bin
TARGET   := program
INCLUDE  := -Iinclude/
SRC      := $(wildcard src/structures/*.cpp) \
            $(wildcard src/utils/*.cpp)      \
			$(wildcard src/generators/*.cpp) \
			$(wildcard src/bijections/*.cpp) \
			$(wildcard src/utils/*.cpp) \
            $(wildcard src/*.cpp)            \

OBJECTS := $(SRC:%.cpp=$(OBJ_DIR)/%.o)

all: build $(BIN_DIR)/$(TARGET)

$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(@D)
	g++ $(FLAGS) $(INCLUDE) -o $@ -c $<

$(BIN_DIR)/$(TARGET): $(OBJECTS)
	@mkdir -p $(@D)
	g++ $(FLAGS) $(INCLUDE) $(LDFLAGS) -o $(BIN_DIR)/$(TARGET) $(OBJECTS)

.PHONY: all build clean debug release

build:
	@mkdir -p $(BIN_DIR)
	@mkdir -p $(OBJ_DIR)

debug: FLAGS += -DDEBUG -g
debug: all

release: FLAGS += -O2
release: all

clean:
	-@rm -rvf $(OBJ_DIR)/*
	-@rm -rvf $(BIN_DIR)/*