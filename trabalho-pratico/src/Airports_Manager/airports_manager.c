#include "Airports_Manager/airports_manager.h"


struct AirportsManager {
    GHashTable *airports_table;
    pool_t *airports_pool;
};