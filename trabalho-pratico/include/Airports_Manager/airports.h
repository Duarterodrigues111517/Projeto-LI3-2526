#ifndef AIRPORTS_H
#define AIRPORTS_H

#include <stddef.h>
#include <stdbool.h>

typedef struct Airport Airport;

// Construção / destruição
Airport *airport_new(const char *code, const char *name, const char *city,
                     const char *country, const char *icao, const char *type,
                     double latitude, double longitude);
void airport_free(Airport *a);

// Getters
const char *airport_get_code(const Airport *a);
const char *airport_get_name(const Airport *a);
const char *airport_get_city(const Airport *a);
const char *airport_get_country(const Airport *a);
const char *airport_get_icao(const Airport *a);
const char *airport_get_type(const Airport *a);
double airport_get_latitude(const Airport *a);
double airport_get_longitude(const Airport *a);

// Setters (retornam false se input inválido)
bool airport_get_code(Airport *a, const char **code);
bool airport_set_name(Airport *a, const char *name);
bool airport_set_city(Airport *a, const char *city);
bool airport_set_country(Airport *a, const char *country);
bool airport_set_icao(Airport *a, const char *icao);
bool airport_set_type(Airport *a, const char *type);
bool airport_set_latitude(Airport *a, double lat);
bool airport_set_longitude(Airport *a, double lon);

#endif
