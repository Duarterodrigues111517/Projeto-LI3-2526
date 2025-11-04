#include "Flights_Manager/flights_manager.h"


struct FlightsManager {
    GHashTable *flights_table;
};

// Destroy
void destroy_flight(void *f) {
    flight_free((Flight *)f);
}


// Create 

FlightsManager_t *flights_manager_new(void) {
    FlightsManager_t *fm = malloc(sizeof(FlightsManager_t));
    if (!fm) return NULL;

    fm->flights_table = g_hash_table_new_full(
        g_str_hash,          
        g_str_equal,          
        free,                 
        destroy_flight    
    );

    if (!fm->flights_table) {
        free(fm);
        return NULL;
    }

    return fm;
}


// Free memory 

void flights_manager_free(FlightsManager_t *fm) {
    if (!fm) return;
    g_hash_table_destroy(fm->flights_table);
    free(fm);
}


//Add flight 

void flights_manager_add(FlightsManager_t *fm, Flight *f) {
    if (!fm || !f) return;

    g_hash_table_insert(fm->flights_table, g_strdup(f->id), f);
} 

// Get flight

Flight *flights_manager_get(const FlightsManager_t *fm, const char *id) {
    if (!fm || !id) return NULL;
    return (Flight *)g_hash_table_lookup(fm->flights_table, id);
}