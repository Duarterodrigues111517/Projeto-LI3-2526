#include "Aircrafts_Manager/aircrafts_manager.h"


struct AircraftsManager {
    GHashTable *aircrafts_table;

};

// Destroy
void destroy_aircraft(void *a) {
    aircraft_free((Aircraft *)a);
}

//Create 

AircraftsManager_t *aircrafts_manager_new(void) {
    AircraftsManager_t *acm = malloc(sizeof(AircraftsManager_t));
    if (!acm) return NULL;

    acm->aircrafts_table = g_hash_table_new_full(
        g_str_hash,          
        g_str_equal,          
        free,                 
        destroy_aircraft    
    );
    if (!acm->aircrafts_table) {
        free(acm);
        return NULL;
    }
    return acm;
}

//Free memory 

void aircrafts_manager_free(AircraftsManager_t *acm) {
    if (!acm) return;
    g_hash_table_destroy(acm->aircrafts_table);
    free(acm);
}

// Add aircraft
void aircrafts_manager_add(AircraftsManager_t *acm, Aircraft *a) {
    if (!acm || !a) return;
    g_hash_table_insert(acm->aircrafts_table,
                        g_strdup(aircraft_get_id(a)), a);  
}

// Get aircraft 

Aircraft *aircrafts_manager_get(const AircraftsManager_t *acm, const char *id) {
    if (!acm || !id) return NULL;
    return (Aircraft *)g_hash_table_lookup(acm->aircrafts_table, id);
}



