#ifndef QUERY2_H
#define QUERY2_H

#include "Aircrafts_Manager/aircrafts_manager.h"
#include "Flights_Manager/flights_manager.h"

/**
 * Query 2
 * Top N aeronaves com mais voos (não cancelados),
 * opcionalmente filtradas por fabricante.
 *
 * Output (por linha):
 *   aircraft_id,manufacturer,model,flight_count
 */
void querie2(int N,
             const char *manufacturer,        // pode ser NULL (sem filtro)
             AircraftsManager_t *acm,
             FlightsManager_t *fm,
             const char *output_path);

#endif
