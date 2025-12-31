#include "Flights_Manager/flights.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct Flight {
    char *id;
    char *departure;
    char *actual_departure;
    char *arrival;
    char *actual_arrival;
    char *gate;
    char *status;
    char *origin;
    char *destination;
    char *aircraft;
    char *airline;
} Flight;




Flight *flight_new(const char *id,
    const char *departure,
    const char *actual_departure,
    const char *arrival,
    const char *actual_arrival,
    const char *gate,
    const char *status,
    const char *origin,
    const char *destination,
    const char *aircraft,
    const char *airline){
    if(!is_valid_flight_id(id)) return NULL;
    if(!is_valid_iata3(origin)) return NULL;
    if(!is_valid_iata3(destination)) return NULL;
    Flight *f = calloc(1,sizeof(*f));
    if(!f) return NULL;
    f->id = strdup(id);
    f->departure = strdup(departure);
    f->actual_departure = strdup(actual_departure);
    f->arrival = strdup(arrival);
    f->actual_arrival = strdup(actual_arrival);
    f->gate = strdup(gate);
    f->status = strdup(status);
    f->origin = strdup(origin);
    f->destination = strdup(destination);
    f->aircraft = strdup(aircraft);
    f->airline = strdup(airline);

    return f;
}

void flight_free(Flight *f){
    if(!f) return;
    free(f->id);
    free(f->departure);
    free(f->actual_departure);
    free(f->arrival);
    free(f->actual_arrival);
    free(f->gate);
    free(f->status);
    free(f->origin);
    free(f->destination);
    free(f->aircraft);
    free(f->airline);
    free(f);
}

const char *flight_get_id(const Flight *f){ return f? f->id: NULL; }
const char *flight_get_departure(const Flight *f){ return f? f->departure: NULL; }
const char *flight_get_actual_departure(const Flight *f){ return f? f->actual_departure: NULL; }
const char *flight_get_arrival(const Flight *f){ return f? f->arrival: NULL; }
const char *flight_get_actual_arrival(const Flight *f){ return f? f->actual_arrival: NULL; }
const char *flight_get_gate(const Flight *f){ return f? f->gate: NULL; }
const char *flight_get_status(const Flight *f){ return f? f->status: NULL; }
const char *flight_get_origin(const Flight *f){ return f? f->origin: NULL; }
const char *flight_get_destination(const Flight *f){ return f? f->destination: NULL; }
const char *flight_get_aircraft(const Flight *f){ return f? f->aircraft: NULL; }
const char *flight_get_airline(const Flight *f){ return f? f->airline: NULL; }


bool flight_set_id(Flight *f, const char *id){ if(!f) return false; if(!is_valid_flight_id(id)) return false; char *d=strdup(id); if(!d && id) return false; free(f->id); f->id=d; return true; }
bool flight_set_departure(Flight *f, const char *departure){ if(!f) return false; char *d=strdup(departure); if(!d && departure) return false; free(f->departure); f->departure=d; return true; }
bool flight_set_actual_departure(Flight *f, const char *actual_departure){ if(!f) return false; char *d=strdup(actual_departure); if(!d && actual_departure) return false; free(f->actual_departure); f->actual_departure=d; return true; }
bool flight_set_arrival(Flight *f, const char *arrival){ if(!f) return false; char *d=strdup(arrival); if(!d && arrival) return false; free(f->arrival); f->arrival=d; return true; }
bool flight_set_actual_arrival(Flight *f, const char *actual_arrival){ if(!f) return false; char *d=strdup(actual_arrival); if(!d && actual_arrival) return false; free(f->actual_arrival); f->actual_arrival=d; return true; }
bool flight_set_gate(Flight *f, const char *gate){ if(!f) return false; char *d=strdup(gate); if(!d && gate) return false; free(f->gate); f->gate=d; return true; }
bool flight_set_status(Flight *f, const char *status){ if(!f) return false; char *d=strdup(status); if(!d && status) return false; free(f->status); f->status=d; return true; }
bool flight_set_origin(Flight *f, const char *origin){ if(!f) return false; if(!is_valid_iata3(origin)) return false; char *d=strdup(origin); if(!d && origin) return false; free(f->origin); f->origin=d; return true; }
bool flight_set_destination(Flight *f, const char *destination){ if(!f) return false; if(!is_valid_iata3(destination)) return false; char *d=strdup(destination); if(!d && destination) return false; free(f->destination); f->destination=d; return true; }
bool flight_set_aircraft(Flight *f, const char *aircraft){ if(!f) return false; char *d=strdup(aircraft); if(!d && aircraft) return false; free(f->aircraft); f->aircraft=d; return true; }
bool flight_set_airline(Flight *f, const char *airline){ if(!f) return false; char *d=strdup(airline); if(!d && airline) return false; free(f->airline); f->airline=d; return true; }
