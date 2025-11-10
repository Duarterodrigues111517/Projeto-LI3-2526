#ifndef QUERIES_PARSER_H
#define QUERIES_PARSER_H

#include "../Airports_Manager/airports_manager.h"

// Futuramente vais incluir outros managers aqui também
// (para as queries 2, 3, etc.)

/**
 * Lê o ficheiro de queries (input.txt), interpreta as linhas e chama as queries corretas.
 * 
 * @param path_input caminho do ficheiro input.txt
 * @param am gestor de aeroportos
 */
void parse_queries(const char *path_input, AirportsManager_t *am);

#endif
