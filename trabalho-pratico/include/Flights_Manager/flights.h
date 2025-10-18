#ifndef FLIGHTS_H
#define FLIGHTS_H

#include <stdbool.h>

typedef struct Flight Flight;

typedef enum {
    FLIGHT_SCHEDULED,
    FLIGHT_CANCELLED,
    FLIGHT_DELAYED,
    FLIGHT_DONE,
    FLIGHT_UNKNOWN
} FlightStatus;

// Construção / destruição
Flight *flight_new(const char *id, const char *airline, const char *aircraft_id,
                   const char *origin, const char *destination,
                   const char *schedule_departure, const char *schedule_arrival,
                   const char *actual_departure, const char *actual_arrival,
                   FlightStatus status);
void flight_free(Flight *f);

// Getters
const char *flight_get_id(const Flight *f);
const char *flight_get_airline(const Flight *f);
const char *flight_get_aircraft_id(const Flight *f);
const char *flight_get_origin(const Flight *f);
const char *flight_get_destination(const Flight *f);
const char *flight_get_schedule_departure(const Flight *f);
const char *flight_get_schedule_arrival(const Flight *f);
const char *flight_get_actual_departure(const Flight *f);
const char *flight_get_actual_arrival(const Flight *f);
FlightStatus flight_get_status(const Flight *f);

// Setters
bool flight_set_actual_departure(Flight *f, const char *dt);
bool flight_set_actual_arrival(Flight *f, const char *dt);
bool flight_set_status(Flight *f, FlightStatus st);

// Helpers
FlightStatus flight_status_from_string(const char *s);

#endif
