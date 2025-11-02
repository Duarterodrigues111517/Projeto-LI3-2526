#include "Passengers_Manager/passengers_manager.h"


struct PassengersManager {
    GHashTable *passengers_table;
    pool_t *passengers_pool;
};