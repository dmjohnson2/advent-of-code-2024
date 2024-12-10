CC = gcc
CFLAGS = -Wall -Wextra -MMD -MP 

SRC_DIRS = src src/day1 src/day2 src/day3 src/day4 src/day5 src/day6 src/day8
OBJ_DIR = obj

SOURCES = $(foreach dir,$(SRC_DIRS),$(wildcard $(dir)/*.c))
OBJECTS = $(patsubst %.c,$(OBJ_DIR)/%.o,$(SOURCES))
DEPS = $(OBJECTS:.o=.d)
BINARY = advent

all: $(BINARY)

debug: CFLAGS += -g -DDEBUG
debug: $(BINARY)

$(BINARY): $(OBJECTS) 	
	$(CC) -o $@ $^

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

-include $(DEPS)

clean:
	rm -rf $(OBJ_DIR) advent
