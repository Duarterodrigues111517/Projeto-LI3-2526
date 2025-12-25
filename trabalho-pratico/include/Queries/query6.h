#ifndef QUERY6_H
#define QUERY6_H

#include "../Flights_Manager/flights_manager.h"
#include "../Passengers_Manager/passengers_manager.h"
#include "../Reservations_Manager/reservations_manager.h"
#include <glib.h>
#include <stdio.h>


void compute_q6(GHashTable *q6_table,
                ReservationsManager_t *rm,
                FlightsManager_t *fm,
                PassengersManager_t *pm);

void querie6(const char *args,
             char sep,
             GHashTable *q6_table,
             const char *output_path);

#endif