#ifndef FLIGHTS_PARSER_H
#define FLIGHTS_PARSER_H

#include <glib.h>
#include <stdio.h>
#include "Flights_Manager/flights_manager.h"

int parse_flight_row(GArray *f, const char *raw, const char *header,
                     FlightsManager_t *mgr, FILE **errors_fp);

#endif


