#ifndef AIRCRAFTS_ENTITY_H
#define AIRCRAFTS_ENTITY_H

#include <stdbool.h>

typedef struct Aircraft Aircraft;

Aircraft *aircraft_new(const char *id, const char *model, const char *manufacturer,
                       int capacity, int range, int year); 
void aircraft_free(Aircraft *a);

const char *aircraft_get_id(const Aircraft *a);
const char *aircraft_get_model(const Aircraft *a);
const char *aircraft_get_manufacturer(const Aircraft *a);
int        aircraft_get_capacity(const Aircraft *a);
int        aircraft_get_range(const Aircraft *a);
int        aircraft_get_year(const Aircraft *a);

bool aircraft_set_id(Aircraft *a, const char *id);
bool aircraft_set_model(Aircraft *a, const char *model);
bool aircraft_set_manufacturer(Aircraft *a, const char *manufacturer);
bool aircraft_set_capacity(Aircraft *a, int capacity);
bool aircraft_set_range(Aircraft *a, int range);
bool aircraft_set_year(Aircraft *a, int year);
#endif
