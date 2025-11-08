#include "Passengers_Manager/passengers_manager.h"
#include <stdlib.h>
#include <string.h>

struct PassengersManager {
    GHashTable *passengers_table;
};

void destroy_passenger(void *p) {
    passenger_free((Passenger *)p);
}

PassengersManager_t *passengers_manager_new(void) {
    PassengersManager_t *pm = malloc(sizeof(PassengersManager_t));
    if (!pm) return NULL;

    pm->passengers_table = g_hash_table_new_full(
        g_str_hash,
        g_str_equal,
        free,
        destroy_passenger
    );

    if (!pm->passengers_table) {
        free(pm);
        return NULL;
    }

    return pm;
}

void passengers_manager_free(PassengersManager_t *pm) {
    if (!pm) return;
    g_hash_table_destroy(pm->passengers_table);
    free(pm);
}

void passengers_manager_add(PassengersManager_t *pm, Passenger *p) {
    if (!pm || !p) return;

    const char *id = passenger_get_document_number(p);
    if (!id) return;

    g_hash_table_insert(pm->passengers_table, g_strdup(id), p);
}

Passenger *passengers_manager_get(const PassengersManager_t *pm, const char *id) {
    if (!pm || !id) return NULL;
    return (Passenger *)g_hash_table_lookup(pm->passengers_table, id);
}



