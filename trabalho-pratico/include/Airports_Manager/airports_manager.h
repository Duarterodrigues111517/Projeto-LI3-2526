#ifndef AIRPORT_MANAGER_H
#define AIRPORT_MANAGER_H


#include "airports.h"
#include <glib.h>
#include "Flights_Manager/flights_manager.h"
#include "Reservations_Manager/reservations_manager.h"
#include <string.h>
#include "Flights_Manager/flights.h"
#include "Reservations_Manager/reservations.h"
#include "Airports_Manager/airports.h"


typedef struct AirportsManager AirportsManager_t;

void destroy_airport(void *a);
AirportsManager_t *airports_manager_new(void);
void airports_manager_free(AirportsManager_t *am);
void airports_manager_add(AirportsManager_t *am, Airport *a);
Airport *airports_manager_get(const AirportsManager_t *am, const char *id);
void airports_manager_compute_passenger_counts(AirportsManager_t *am,
                                               FlightsManager_t *fm,
                                               ReservationsManager_t *rm);


#endif