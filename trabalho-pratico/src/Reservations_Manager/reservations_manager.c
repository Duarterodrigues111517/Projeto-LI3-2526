#include "Reservations_Manager/reservations_manager.h"


struct ReservationsManager {
    GHashTable *reservations_table;
    pool_t *reservations_pool;
};