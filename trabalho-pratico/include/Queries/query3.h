#ifndef QUERY3_H
#define QUERY3_H

#include "Airports_Manager/airports_manager.h"
#include "Flights_Manager/flights_manager.h"

void querie3(const char *start_date,
             const char *end_date, char sep,
             AirportsManager_t *am,
             FlightsManager_t *fm,
             const char *output_path);

#endif
