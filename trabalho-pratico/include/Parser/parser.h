#ifndef PARSER_GEN_H
#define PARSER_GEN_H

#include <glib.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Liberta todos os elementos do GArray sem o destruir
void free_garray_parsed_elements(GArray *array);

// Processa uma linha de um ficheiro CSV, divide pelos ';' e guarda no GArray
int process_line(FILE *file, GArray *array, char **lineCopy);

// Liberta todo o GArray e destrói-o
void free_garray_parsed(GArray *array);

#endif
