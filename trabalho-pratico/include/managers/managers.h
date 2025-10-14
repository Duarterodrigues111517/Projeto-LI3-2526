#ifndef MANAGERS_H
#define MANAGERS_H

#include "managers/airports.h"
#include "managers/flights.h"
#include "managers/passengers.h"
#include "managers/aircrafts.h"
#include "managers/reservations.h"

typedef struct managers *Managers;

/* ciclo de vida */
Managers    managers_create(void);
void        managers_destroy(Managers m);

/* getters (não transferem ownership) */
Airports     managers_airports(Managers m);
Flights      managers_flights(Managers m);
Passengers   managers_passengers(Managers m);
Aircrafts    managers_aircrafts(Managers m);
Reservations managers_reservations(Managers m);

#endif
