#ifndef AIRCRAFT_MANAGER_H
#define AIRCRAFT_MANAGER_H


#include "aircrafts.h"
#include "../utils/pool.h"
#include <glib.h>

typedef struct AircraftManager AircraftManager_t;

void destroy_aircraft(void *a);
AircraftsManager_t *aircrafts_manager_new(void);
void aircrafts_manager_free(AircraftsManager_t *acm);
void aircrafts_manager_add(AircraftsManager_t *acm, Aircraft *a);
Aircraft *aircrafts_manager_get(const AircraftsManager_t *acm, const char *id);

#endif