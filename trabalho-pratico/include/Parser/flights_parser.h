#ifndef FLIGHTS_PARSER_H
#define FLIGHTS_PARSER_H

#include <glib.h>
#include <stdio.h>
#include "Flights_Manager/flights_manager.h"
#include "Parser/parser.h"

int parse_flight_row(GArray *f, const char *raw, const char *header,
                     FlightsManager_t *mgr, FILE **errors_fp);


FlightsManager_t *parse_flights_file(const char *csvPath);
#endif


