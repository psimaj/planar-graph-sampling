FLAGS   := -pedantic-errors -Wall -Wextra -Werror -std=c++14
BUILD   := ./build
OBJ_DIR := $(BUILD)/objects
BIN_DIR := $(BUILD)/bin
TEST_DIR:= $(BUILD)/test
MAIN_TARGET  := program
TREE_TARGET := generateTree
DISSECTION_TARGET := generateDissection
INCLUDE := -Iinclude/
SRC     := $(wildcard src/structures/*.cpp)  \
			$(wildcard src/generators/*.cpp) \
			$(wildcard src/bijections/*.cpp) \
			$(wildcard src/utils/*.cpp) 	 \

TEST	:= $(wildcard test/visual/*.cpp) 	   \
			$(wildcard test/statistical/*.cpp) \

COMMON_OBJECTS := $(SRC:%.cpp=$(OBJ_DIR)/%.o)   \

MAIN_TARGET_OBJECT := $(OBJ_DIR)/src/main.o
TREE_TARGET_OBJECT := $(OBJ_DIR)/test/visual/generateTree.o
DISSECTION_TARGET_OBJECT := $(OBJ_DIR)/test/visual/generateDissection.o

all: build $(BIN_DIR)/$(MAIN_TARGET)
all: build $(BIN_DIR)/$(TREE_TARGET)
all: build $(BIN_DIR)/$(DISSECTION_TARGET)

$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(@D)
	g++ $(FLAGS) $(INCLUDE) -o $@ -c $<

$(BIN_DIR)/$(MAIN_TARGET): $(COMMON_OBJECTS) $(MAIN_TARGET_OBJECT)
	@mkdir -p $(@D)
	g++ $(FLAGS) $(INCLUDE) $(LDFLAGS) -o $(BIN_DIR)/$(MAIN_TARGET) $(COMMON_OBJECTS) $(MAIN_TARGET_OBJECT)

$(BIN_DIR)/$(TREE_TARGET): $(COMMON_OBJECTS) $(TREE_TARGET_OBJECT)
	@mkdir -p $(@D)
	g++ $(FLAGS) $(INCLUDE) $(LDFLAGS) -o $(BIN_DIR)/$(TREE_TARGET) $(COMMON_OBJECTS) $(TREE_TARGET_OBJECT)

$(BIN_DIR)/$(DISSECTION_TARGET): $(COMMON_OBJECTS) $(DISSECTION_TARGET_OBJECT)
	@mkdir -p $(@D)
	g++ $(FLAGS) $(INCLUDE) $(LDFLAGS) -o $(BIN_DIR)/$(DISSECTION_TARGET) $(COMMON_OBJECTS) $(DISSECTION_TARGET_OBJECT)

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