#include "Airports_Manager/airports_manager.h"


struct AirportsManager {
    GHashTable *airports_table;
};

// Destroy
void destroy_airport(void *a) {
    airport_free((Airport *)a);
}

//Create
AirportsManager_t *airports_manager_new(void) {
    AirportsManager_t *am = malloc(sizeof(AirportsManager_t));
    if (!am) return NULL;

    am->airports_table = g_hash_table_new_full(
        g_str_hash,          
        g_str_equal,          
        free,                 
        destroy_airport    
    );

    if (!am->airports_table) {
        free(am);
        return NULL;
    }

    return am;
}

// LIberta a memoria
void airports_manager_free(AirportsManager_t *am) {
    if (!am) return;
    g_hash_table_destroy(am->airports_table);
    free(am);
}

// Adiciona aeroporto
void airports_manager_add(AirportsManager_t *am, Airport *a) {
    if (!am || !a) return;

    g_hash_table_insert(am->airports_table, g_strdup(a->id), a);
}

//Procura aeroporto
Airport *airports_manager_get(const AirportsManager_t *am, const char *id) {
    if (!am || !id) return NULL;
    return (Airport *)g_hash_table_lookup(am->airports_table, id);
}
