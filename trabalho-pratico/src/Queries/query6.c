#include "Queries/query6.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <glib.h>

/*
  q6_table:
    key   = nationality (char*)
    value = GHashTable* dest_counts

  dest_counts:
    key   = destination airport code (char*)
    value = int* (count)
*/

static void free_int_ptr(gpointer p) {
    free(p);
}

static void q6_add_arrival_with_count(GHashTable *q6_table, const char *nat, 
                                       const char *dest) {
    if (!q6_table || !nat || !dest) return;

    GHashTable *dest_counts = g_hash_table_lookup(q6_table, nat);

    if (!dest_counts) {
        dest_counts = g_hash_table_new_full(g_str_hash, g_str_equal, free, free_int_ptr);
        g_hash_table_insert(q6_table, strdup(nat), dest_counts);
    }

    int *cnt = g_hash_table_lookup(dest_counts, dest);
    if (!cnt) {
        cnt = malloc(sizeof(int));
        if (!cnt) return;
        *cnt = 0;
        g_hash_table_insert(dest_counts, strdup(dest), cnt);
    }
    (*cnt) ++;  // Add the number of passengers, not just 1
}

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
    if (!nat || *nat == '\0') return;



    int n = reservation_get_flights_count(r);
    for (int i = 0; i < n; i++) {
        const char *fid = reservation_get_flight_id_at(r, i);
        if (!fid) continue;

        Flight *f = flights_manager_get(ctx->fm, fid);
        if (!f) continue;

        const char *status = flight_get_status(f);
        if (status && strcmp(status, "Cancelled") == 0) continue;

        const char *dest = flight_get_destination(f);
        if (!dest) continue;

        // Count ALL passengers in this reservation as arriving at this destination
        q6_add_arrival_with_count(ctx->q6, nat, dest);
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

static char *dup_and_trim(const char *s) {
    if (!s) return NULL;
    char *cpy = strdup(s);
    if (!cpy) return NULL;

    // trim simples (início)
    char *start = cpy;
    while (*start == ' ' || *start == '\t') start++;

    // trim fim
    size_t len = strlen(start);
    while (len > 0 && (start[len-1] == ' ' || start[len-1] == '\t' ||
                       start[len-1] == '\n' || start[len-1] == '\r')) {
        start[--len] = '\0';
    }

    // se houve avanço no início, compactar
    if (start != cpy) memmove(cpy, start, len + 1);

    return cpy;
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
        fputc('\n', f);
        fclose(f);
        return;
    }

    char *nat = dup_and_trim(args);
    if (!nat || *nat == '\0') {
        free(nat);
        fputc('\n', f);
        fclose(f);
        return;
    }

    GHashTable *dest_counts = g_hash_table_lookup(q6_table, nat);
    if (!dest_counts) {
        free(nat);
        fputc('\n', f);
        fclose(f);
        return;
    }

    const char *best_code = NULL;
    int best_count = -1;

    GHashTableIter it;
    gpointer k, v;
    g_hash_table_iter_init(&it, dest_counts);

    while (g_hash_table_iter_next(&it, &k, &v)) {
        const char *code = (const char *)k;
        int cnt = *(int *)v;

        if (cnt > best_count) {
            best_count = cnt;
            best_code = code;
        } else if (cnt == best_count && best_code && strcmp(code, best_code) < 0) {
            best_code = code; // desempate lexicográfico
        } else if (cnt == best_count && !best_code) {
            best_code = code;
        }
    }

    if (!best_code) {
        fputc('\n', f);
    } else {
        fprintf(f, "%s%c%d\n", best_code, sep, best_count);
    }

    free(nat);
    fclose(f);
}
