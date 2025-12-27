#ifndef FLIGHT_MANAGER_H
#define FLIGHT_MANAGER_H


#include "flights.h"
#include <glib.h>

typedef struct FlightsManager FlightsManager_t;

/* ===== Q5 stats ===== */
typedef struct {
    long delayed_count;
    long long total_delay_minutes;
} Q5AirlineStat;

/* getters/update */
GHashTable *flights_manager_get_q5_table(const FlightsManager_t *fm);
void flights_manager_update_q5(FlightsManager_t *fm, const Flight *f);


void destroy_flight(void *f);
FlightsManager_t *flights_manager_new(void);
void flights_manager_free(FlightsManager_t *fm);
void flights_manager_add(FlightsManager_t *fm, Flight *f);
Flight *flights_manager_get(const FlightsManager_t *fm, const char *id);
void flights_manager_foreach(FlightsManager_t *fm,
                             void (*fn)(Flight *f, void *user_data),
                             void *user_data);

#endif