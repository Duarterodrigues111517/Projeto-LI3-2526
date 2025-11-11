
CC = gcc
CFLAGS = -Wall -Wextra -Iinclude `pkg-config --cflags glib-2.0`
LDFLAGS = `pkg-config --libs glib-2.0`


SRC_DIR = src
INC_DIR = include
OBJ_DIR = obj
BIN_DIR = bin

MAIN_EXEC   = $(BIN_DIR)/programa-principal
TEST_EXEC   = $(BIN_DIR)/programa-testes
PARSER_EXEC = $(BIN_DIR)/test_parser

SRC_FILES := $(shell find $(SRC_DIR) -name "*.c")
OBJ_FILES := $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC_FILES))


all: dirs $(MAIN_EXEC)

dirs:
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(BIN_DIR)


$(MAIN_EXEC): $(OBJ_FILES)
	$(CC) $(OBJ_FILES) $(LDFLAGS) -o $@


$(TEST_EXEC): $(OBJ_FILES)
	$(CC) $(OBJ_FILES) $(LDFLAGS) -o $@
	


$(PARSER_EXEC): $(OBJ_FILES)
	$(CC) $(OBJ_FILES) $(LDFLAGS) -o $@



$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@


clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)
	rm -f $(RESULTS_DIR)/command*_output.txt
	rm -f resultados/*_errors.csv
	

clean_obj:
	rm -rf $(OBJ_DIR)


.PHONY: all clean clean_obj dirs
