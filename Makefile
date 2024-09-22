CC ?= gcc
CFLAGS := -O -g -Wall -Wextra

include mk/common.mk

SRC_DIR := src
BUILD_DIR ?= build

__dir := $(shell mkdir -p $(BUILD_DIR))

SOURCES := $(wildcard $(SRC_DIR)/*.c)
OBJECTS := $(SOURCES:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

TARGET := $(BUILD_DIR)/mancala

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(VECHO) "  LD\t$@\n"
	$(Q)$(CC) -o $@ $(CFLAGS) $^

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(VECHO) "  CC\t$@\n"
	$(Q)$(CC) -o $@ $(CFLAGS) -c $<

clean:
	-$(RM) -rf $(BUILD_DIR)
