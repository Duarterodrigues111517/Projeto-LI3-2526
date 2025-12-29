CC = gcc
CFLAGS = -Wall -Wextra -Iinclude `pkg-config --cflags glib-2.0`
LDFLAGS = `pkg-config --libs glib-2.0`

SRC_DIR = src
INC_DIR = include
OBJ_DIR = obj

RESULTS_DIR = resultados

MAIN_EXEC   = programa-principal
TEST_EXEC   = programa-testes
PARSER_EXEC = test_parser
INTER_EXEC  = programa-interativo

# todos os .c
SRC_FILES := $(shell find $(SRC_DIR) -name "*.c")

# separa mains
MAIN_SRC   = $(SRC_DIR)/main.c
INTER_SRC  = $(SRC_DIR)/programa_interativo.c

# tudo o resto é "comum"
COMMON_SRC := $(filter-out $(MAIN_SRC) $(INTER_SRC), $(SRC_FILES))

# objetos
COMMON_OBJS := $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(COMMON_SRC))
MAIN_OBJ    := $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(MAIN_SRC))
INTER_OBJ   := $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(INTER_SRC))

all: dirs $(MAIN_EXEC) $(INTER_EXEC) $(TEST_EXEC) $(PARSER_EXEC)

dirs:
	@mkdir -p $(OBJ_DIR)

# executáveis
$(MAIN_EXEC): $(COMMON_OBJS) $(MAIN_OBJ)
	$(CC) $^ $(LDFLAGS) -o $@

$(INTER_EXEC): $(COMMON_OBJS) $(INTER_OBJ)
	$(CC) $^ $(LDFLAGS) -o $@

# se os teus "testes" e "parser" são só executáveis iguais ao principal, deixa assim:
$(TEST_EXEC): $(COMMON_OBJS) $(MAIN_OBJ)
	$(CC) $^ $(LDFLAGS) -o $@

$(PARSER_EXEC): $(COMMON_OBJS) $(MAIN_OBJ)
	$(CC) $^ $(LDFLAGS) -o $@

# compilação genérica
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)
	rm -f programa-principal programa-interativo programa-testes test_parser
	rm -f $(RESULTS_DIR)/command*_output.txt
	rm -f resultados/*_errors.csv

clean_obj:
	rm -rf $(OBJ_DIR)

.PHONY: all clean clean_obj dirs
