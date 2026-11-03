# Makefile

TARGET_EXEC := app

BUILD_DIR := ./build
SRC_DIRS := ./src

CC := gcc
CFLAGS := -Wall -Werror -O2
SOURCES := $(shell find $(SRC_DIRS) -name '*.c')
OBJECTS := $(SOURCES:.c=.o)

INC_DIRS := $(shell find $(SRC_DIRS) -type d)

app: $(OBJECTS) | build_dir
	@mkdir -p $(BUILD_DIR)
	mv $(OBJECTS) $(BUILD_DIR)/
	$(CC) $(CFLAGS) -o $(BUILD_DIR)/$(TARGET_EXEC) $(BUILD_DIR)/*.o

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

build_dir:
	@mkdir -p $(BUILD_DIR)

clean:
	rm -rf $(BUILD_DIR)

run: app
	./$(BUILD_DIR)/$(TARGET_EXEC)

.PHONY: all clean run

