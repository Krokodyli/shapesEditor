CXX = g++
CXXFLAGS = -std=c++17 -Wall -Werror -O2

SRC_DIR = src
BUILD_DIR = build
BIN_DIR = bin
DATA_DIR = data
RESOURCE_DIR = bin/resources

BIN_NAME = sfmlapp

SOURCES = $(shell find $(SRC_DIR) -name "*.cpp")

OBJECTS = $(SOURCES:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)
DEPS = $(OBJECTS:.o=.d)

LIBS = -lsfml-graphics -lsfml-window -lsfml-system

.PHONY: default_target debug directories all clean

default_target: compile

run: compile
run:
	./bin/sfmlapp

compile: directories
	@$(MAKE) all

directories:
	@echo "Creating directories"
	@mkdir -p $(dir $(OBJECTS))
	@mkdir -p $(BIN_DIR)
	@cp -R $(DATA_DIR)/. $(RESOURCE_DIR)

all: $(BIN_DIR)/$(BIN_NAME)

$(BIN_DIR)/$(BIN_NAME): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $@ $(LIBS)
-include $(DEPS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@echo "Compiling: $< -> $@"
	$(CXX) $(CXXFLAGS) $(INCLUDES) -MP -MMD -c $< -o $@ $(LIBS)

clean:
	@rm -rf $(BUILD_DIR)/*
	@rm -rf $(BIN_DIR)/$(BIN_NAME)
