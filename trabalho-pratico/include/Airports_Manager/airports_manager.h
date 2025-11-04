#ifndef AIRPORT_MANAGER_H
#define AIRPORT_MANAGER_H


#include "airports.h"
#include "../utils/pool.h"
#include <glib.h>

typedef struct AirportsManager AirportsManager_t;

void destroy_airport(void *a);
AirportsManager_t *airports_manager_new(void);
void airports_manager_free(AirportsManager_t *am);
void airports_manager_add(AirportsManager_t *am, Airport *a);
Airport *airports_manager_get(const AirportsManager_t *am, const char *id);

#endif