#ifndef FLIGHT_MANAGER_H
#define FLIGHT_MANAGER_H


#include "flights.h"
#include "../utils/pool.h"
#include <glib.h>

typedef struct FlightsManager FlightsManager_t;

void destroy_flight(void *f);
FlightsManager_t *flights_manager_new(void);
void flights_manager_free(FlightsManager_t *fm);
void flights_manager_add(FlightsManager_t *fm, Flight *f);
Flight *flights_manager_get(const FlightsManager_t *fm, const char *id);
void flights_manager_foreach(FlightsManager_t *fm,
                             void (*fn)(Flight *f, void *user_data),
                             void *user_data);

#endif