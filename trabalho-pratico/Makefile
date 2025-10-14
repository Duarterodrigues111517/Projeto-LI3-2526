# Makefile simples — começar pequeno e ir crescendo

CC     := gcc
CFLAGS := -std=c17 -Wall -Wextra -O2 -Iinclude

# Todos os .c em src/ e src/managers/
SRCS := $(wildcard src/*.c) $(wildcard src/managers/*.c)


# (Opcional) define os "mains" para evitar conflito de duas mains
MAIN_SRC      := src/main.c
TESTS_MAIN    := src/tests_main.c

# Fontes de cada executável (exclui o main do outro)
SRCS_PRINC  := $(filter-out $(TESTS_MAIN),$(SRCS))
SRCS_TESTES := $(filter-out $(MAIN_SRC),$(SRCS))

# Objetos
OBJS_PRINC  := $(SRCS_PRINC:.c=.o)
OBJS_TESTES := $(SRCS_TESTES:.c=.o)

# Alvo por omissão
all: programa-principal

programa-principal: $(OBJS_PRINC)
	$(CC) $^ -o $@

programa-testes: $(OBJS_TESTES)
	$(CC) $^ -o $@

# Regra genérica de compilação .c -> .o
src/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -f src/*.o programa-principal programa-testes
