#include <stdlib.h>
#include "managers/managers.h"

struct managers {
    Airports     airports;
    Flights      flights;
    Passengers   passengers;
    Aircrafts    aircrafts;
    Reservations reservations;
};

Managers managers_create(void) {
    Managers m = malloc(sizeof(*m));
    if (!m) return NULL;

    m->airports     = airports_create();
    m->flights      = flights_create();
    m->passengers   = passengers_create();
    m->aircrafts    = aircrafts_create();
    m->reservations = reservations_create();

    if (!m->airports || !m->flights || !m->passengers || !m->aircrafts || !m->reservations) {
        managers_destroy(m);
        return NULL;
    }
    return m;
}

void managers_destroy(Managers m) {
    if (!m) return;
    reservations_destroy(m->reservations);
    aircrafts_destroy(m->aircrafts);
    passengers_destroy(m->passengers);
    flights_destroy(m->flights);
    airports_destroy(m->airports);
    free(m);
}

Airports     managers_airports(Managers m)   { return m ? m->airports     : NULL; }
Flights      managers_flights(Managers m)    { return m ? m->flights      : NULL; }
Passengers   managers_passengers(Managers m) { return m ? m->passengers   : NULL; }
Aircrafts    managers_aircrafts(Managers m)  { return m ? m->aircrafts    : NULL; }
Reservations managers_reservations(Managers m){return m ? m->reservations : NULL; }
