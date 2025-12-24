#ifndef QUERY2_H
#define QUERY2_H

#include "Aircrafts_Manager/aircrafts_manager.h"
#include "Flights_Manager/flights_manager.h"

void querie2(int N,
             const char *manufacturer,  char sep,      
             AircraftsManager_t *acm,
             FlightsManager_t *fm,
             const char *output_path);

#endif
