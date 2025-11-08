#ifndef PASSENGER_MANAGER_H
#define PASSENGER_MANAGER_H

#include "passengers.h"
#include "../utils/pool.h"
#include <glib.h>

typedef struct PassengersManager PassengersManager_t;

void destroy_passenger(void *p);
PassengersManager_t *passengers_manager_new(void);
void passengers_manager_free(PassengersManager_t *pm);
void passengers_manager_add(PassengersManager_t *pm, Passenger *p);
Passenger *passengers_manager_get(const PassengersManager_t *pm, const char *id);

#endif
