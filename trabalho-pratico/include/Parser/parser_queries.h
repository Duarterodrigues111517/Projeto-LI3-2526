#ifndef QUERIES_PARSER_H
#define QUERIES_PARSER_H

#include "Airports_Manager/airports_manager.h"
#include "Queries/query1.h"
#include "Queries/query2.h"
#include "Queries/query3.h"  
#include "Queries/query5.h"
#include "Queries/query6.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Airports_Manager/airports_manager.h"
#include "Aircrafts_Manager/aircrafts_manager.h"
#include "Flights_Manager/flights_manager.h"

/**
 * @brief Lê e executa as queries a partir de um ficheiro de input.
 *
 * Abre o ficheiro em path_input, interpreta cada linha como uma query e chama as
 * rotinas correspondentes (Q1, Q2, Q3, Q5, Q6, ...), usando os gestores fornecidos
 * como fontes de dados.
 *
 * @param path_input Caminho para o ficheiro de queries (input).
 * @param am Gestor de aeroportos.
 * @param aircrafts Gestor de aeronaves.
 * @param flights Gestor de voos.
 * @param q6_table Estrutura auxiliar usada pela Query 6 (tabela/índice) já preparada.
 */
void parse_queries(const char *path_input, AirportsManager_t *am, AircraftsManager_t *aircrafts, FlightsManager_t *flights, GHashTable *q6_table);

#endif
