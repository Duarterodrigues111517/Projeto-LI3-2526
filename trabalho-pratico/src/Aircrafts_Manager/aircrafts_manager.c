#include "Aircrafts_Manager/aircrafts_manager.h"


struct AircraftManager {
    GHashTable *aircrafts_table;
    pool_t *aircrafts_pool;
};