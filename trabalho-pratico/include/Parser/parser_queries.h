#ifndef QUERIES_PARSER_H
#define QUERIES_PARSER_H

#include "Airports_Manager/airports_manager.h"
#include "Queries/query1.h"
#include "Queries/query2.h"
#include "Queries/query3.h"  
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Airports_Manager/airports_manager.h"
#include "Aircrafts_Manager/aircrafts_manager.h"
#include "Flights_Manager/flights_manager.h"


// Futuramente vais incluir outros managers aqui também
// (para as queries 2, 3, etc.)

/**
 * Lê o ficheiro de queries (input.txt), interpreta as linhas e chama as queries corretas.
 * 
 * @param path_input caminho do ficheiro input.txt
 * @param am gestor de aeroportos
 */
void parse_queries(const char *path_input, AirportsManager_t *am, AircraftsManager_t *aircrafts, FlightsManager_t *flights);

#endif
