#include "Queries/query6.h"


typedef struct {
    char *airport_code;
    int count;
} Q6Result;

GHashTable *q6_table; // key: nationality (char*), value: Q6Result*



static void q6_process_reservation(Reservation *r, void *user_data) {
    struct {
        GHashTable *q6;
        FlightsManager_t *fm;
        PassengersManager_t *pm;
    } *ctx = user_data;

    int doc = reservation_get_document_number(r);

    char doc_str[10];
    snprintf(doc_str, sizeof(doc_str), "%09d", doc);

    Passenger *p = passengers_manager_get(ctx->pm, doc_str);
    if (!p) return;

    const char *nat = passenger_get_nationality(p);
    if (!nat) return;

    int n = reservation_get_flights_count(r);
    for (int i = 0; i < n; i++) {
        const char *fid = reservation_get_flight_id_at(r, i);
        if (!fid) continue;

        Flight *f = flights_manager_get(ctx->fm, fid);
        if (!f) continue;

        const char *status = flight_get_status(f);
        if (strcmp(status, "Cancelled") == 0) continue;

        const char *dest = flight_get_destination(f);
        if (!dest) continue;

        Q6Result *res = g_hash_table_lookup(ctx->q6, nat);

        if (!res) {
            res = malloc(sizeof(Q6Result));
            res->airport_code = strdup(dest);
            res->count = 1;
            g_hash_table_insert(ctx->q6, strdup(nat), res);
        } else {
            if (strcmp(dest, res->airport_code) == 0) {
                res->count++;
            } else if (res->count == 1) {
                // novo candidato
                free(res->airport_code);
                res->airport_code = strdup(dest);
                res->count = 1;
            }
        }
    }
}

void compute_q6(GHashTable *q6_table,
                ReservationsManager_t *rm,
                FlightsManager_t *fm,
                PassengersManager_t *pm)
{
    struct {
        GHashTable *q6;
        FlightsManager_t *fm;
        PassengersManager_t *pm;
    } ctx = { q6_table, fm, pm };

    reservations_manager_foreach(rm, q6_process_reservation, &ctx);
}

void querie6(const char *args, char sep,
             GHashTable *q6_table,
             const char *output_path)
{
    if (!output_path) return;

    FILE *f = fopen(output_path, "w");
    if (!f) {
        perror("querie6: fopen");
        return;
    }

    if (!args || !q6_table) {
        // Query sem sentido -> ficheiro com linha vazia
        fputc('\n', f);
        fclose(f);
        return;
    }

    const char *nat = args;

    Q6Result *res = g_hash_table_lookup(q6_table, nat);
    if (res) {
        fprintf(f, "%s%c%d\n", res->airport_code, sep, res->count);
    } else {
        fputc('\n', f);
    }

    fclose(f);
}
