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


void parse_queries(const char *path_input, AirportsManager_t *am, AircraftsManager_t *aircrafts, FlightsManager_t *flights, GHashTable *q6_table);

#endif
