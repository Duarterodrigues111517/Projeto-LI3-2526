#ifndef FLIGHTS_H
#define FLIGHTS_H

#include <stdbool.h>
#include <utils/validators.h>

typedef struct Flight Flight;

// Construção / destruição
Flight *flight_new(const char *id, const char *departure, 
                   const char *actual_departure,
                   const char *arrival,
                   const char *actual_arrival,
                   const char *gate,
                   const char *status,
                   const char *origin,
                   const char *destination,
                   const char *aircraft,
                   const char *airline);
void flight_free(Flight *f);

// Getters
const char *flight_get_id(const Flight *f);
const char *flight_get_departure(const Flight *f);
const char *flight_get_actual_departure(const Flight *f);
const char *flight_get_arrival(const Flight *f);
const char *flight_get_actual_arrival(const Flight *f);
const char *flight_get_gate(const Flight *f);
const char *flight_get_status(const Flight *f);
const char *flight_get_origin(const Flight *f);
const char *flight_get_destination(const Flight *f);
const char *flight_get_aircraft(const Flight *f);
const char *flight_get_airline(const Flight *f);

// Setters
bool flight_set_departure(Flight *f, const char *dt);
bool flight_set_actual_departure(Flight *f, const char *dt);
bool flight_set_arrival(Flight *f, const char *dt);
bool flight_set_actual_arrival(Flight *f, const char *dt);
bool flight_set_gate(Flight *f, const char *gate);
bool flight_set_status(Flight *f, const char *status);
bool flight_set_origin(Flight *f, const char *origin);
bool flight_set_destination(Flight *f, const char *destination);
bool flight_set_aircraft(Flight *f, const char *aircraft);
bool flight_set_airline(Flight *f, const char *airline);

#endif
