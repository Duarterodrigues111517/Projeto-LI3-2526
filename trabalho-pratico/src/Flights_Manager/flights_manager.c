#include "Flights_Manager/flights_manager.h"


struct FlightsManager {
    GHashTable *flights_table;
    pool_t *flights_pool;
};