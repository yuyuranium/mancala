CC ?= gcc
CFLAGS := -O -g -Wall -Wextra

include mk/common.mk

SRC_DIR := src
BUILD_DIR ?= build

__dir := $(shell mkdir -p $(BUILD_DIR))

SOURCES := $(wildcard $(SRC_DIR)/*.c)
OBJECTS := $(SOURCES:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)
deps := $(OBJECTS:%.o=%.o.d)

TARGET := $(BUILD_DIR)/mancala

.PHONY: all match clean

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(VECHO) "  LD\t$@\n"
	$(Q)$(CC) -o $@ $(CFLAGS) $^

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(VECHO) "  CC\t$@\n"
	$(Q)$(CC) -o $@ $(CFLAGS) -c -MMD -MF $@.d $<

P1 ?= chaotic
P2 ?= minimal_first
ROUNDS ?= 100

match: $(TARGET)
	$(Q) P1=0; P2=0; DRAW=0; \
	for i in $$(seq 1 $(ROUNDS)); do \
		RESULT=$$($(TARGET) -q $$( (($$i % 2)) && echo $(P2) $(P1) || echo $(P1) $(P2) )); \
		if echo $$RESULT | grep -q "The winner is $(P1)"; then \
			P1=$$((P1 + 1)); \
		elif echo $$RESULT | grep -q "The winner is $(P2)"; then \
			P2=$$((P2 + 1)); \
		else \
			DRAW=$$((DRAW + 1)); \
		fi; \
	done; \
	echo "$(P1):\t$$P1\n$(P2):\t$$P2\nDraw:\t$$DRAW"

clean:
	-$(RM) -rf $(BUILD_DIR)

-include $(deps)
