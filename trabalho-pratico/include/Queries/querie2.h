#ifndef QUERIE2_H
#define QUERIE2_H

#include "Aircrafts_Manager/aircrafts_manager.h"
#include "Flights_Manager/flights_manager.h"

void querie2(int N,
             const char *manufacturer_filter,
             const AircraftsManager_t *aircrafts,
             const FlightsManager_t *flights,
             const char *output_path);

#endif
