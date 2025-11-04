#include "Aircrafts_Manager/aircrafts_manager.h"


struct AircraftManager {
    GHashTable *aircrafts_table;

};

// Destroy
void destroy_aircraft(void *a) {
    aircraft_free((Aircraft *)a);
}

//Create

