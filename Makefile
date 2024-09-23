# Structure-related variables
BUILD_DIR ?= bin
SOURCE_DIR ?= src
SOURCES = $(wildcard $(SOURCE_DIR)/*.c)
OBJECTS = $(patsubst $(SOURCE_DIR)/%.c, $(BUILD_DIR)/%.o, $(SOURCES))

# Project-related variables
PROJECT = main

# Compiler-related variables
CC = gcc
CFLAGS ?=
CFLAGS += -g -Wall -Werror -I src
CFLAGS += $(shell sdl2-config --cflags)
LDFLAGS ?=
LDFLAGS += $(shell sdl2-config --libs) -lm

# Alias definitions
def: default
cdef: clean default
default: $(PROJECT)
clean:
	@rm -vrf $(BUILD_DIR)

# Default linking rules
$(PROJECT) : $(SOURCES)
	@mkdir -p bin
	$(CC) $(CFLAGS) $^ $(LDFLAGS) -o $(BUILD_DIR)/$@
