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

// Liberta a memoria
void airports_manager_free(AirportsManager_t *am) {
    if (!am) return;
    g_hash_table_destroy(am->airports_table);
    free(am);
}

void airports_manager_add(AirportsManager_t *am, Airport *a) {
    if (!am || !a) return;

    g_hash_table_insert(am->airports_table,
                        g_strdup(airport_get_code(a)), a);
}


//Procura aeroporto
Airport *airports_manager_get(const AirportsManager_t *am, const char *code) {
    if (!am || !code) return NULL;
    return (Airport *)g_hash_table_lookup(am->airports_table, code);
}

typedef struct {
    AirportsManager_t *am;
    FlightsManager_t  *fm;
} CountsCtx;

static void process_reservation_counts(Reservation *r, void *user_data) {
    CountsCtx *ctx = (CountsCtx *)user_data;
    if (!r || !ctx || !ctx->am || !ctx->fm) return;

    int n = reservation_get_flights_count(r); // 1 ou 2
    for (int i = 0; i < n; i++) {
        const char *fid = reservation_get_flight_id_at(r, i);
        if (!fid) continue;

        Flight *f = flights_manager_get(ctx->fm, fid);
        if (!f) continue;

        const char *status = flight_get_status(f);
        if (status && strcmp(status, "Cancelled") == 0) continue;

        const char *orig = flight_get_origin(f);
        const char *dest = flight_get_destination(f);

        Airport *a_orig = airports_manager_get(ctx->am, orig);
        Airport *a_dest = airports_manager_get(ctx->am, dest);

        if (a_orig) airport_inc_departures(a_orig, 1);
        if (a_dest) airport_inc_arrivals(a_dest, 1);
    }
}

void airports_manager_compute_passenger_counts(AirportsManager_t *am,
                                               FlightsManager_t *fm,
                                               ReservationsManager_t *rm) {
    if (!am || !fm || !rm) return;

    CountsCtx ctx = { .am = am, .fm = fm };
    reservations_manager_foreach(rm, process_reservation_counts, &ctx);
}
