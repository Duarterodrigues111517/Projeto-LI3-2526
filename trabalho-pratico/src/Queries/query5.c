#include "Queries/query5.h"
#include <glib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const char *airline; /* apontador para key da hash (válido enquanto a hash existir) */
    long delayed_count;
    double avg_delay;
} Q5Row;

static int cmp_q5_rows(gconstpointer a, gconstpointer b) {
    const Q5Row *ra = a;
    const Q5Row *rb = b;

    /* Sort by avg_delay descending - check with epsilon for floating point */
    double diff = rb->avg_delay - ra->avg_delay;
    if (diff > 0.0001) return 1;   /* rb > ra, so rb comes first */
    if (diff < -0.0001) return -1; /* ra > rb, so ra comes first */

    /* Tie-breaker: airline ascending */
    return strcmp(ra->airline, rb->airline);
}

void querie5(const char *args, char sep, FlightsManager_t *fm, const char *output_path)
{
    if (!output_path) return;

    FILE *out = fopen(output_path, "w");
    if (!out) {
        perror("querie5: fopen");
        return;
    }

    if (!fm) {
        fputc('\n', out);
        fclose(out);
        return;
    }

    /* N */
    int N = 0;
    if (args && *args) {
        char *end = NULL;
        long v = strtol(args, &end, 10);
        if (end != args && v > 0) N = (int)v;
    }
    if (N <= 0) {
        fputc('\n', out);
        fclose(out);
        return;
    }

    GHashTable *tab = flights_manager_get_q5_table(fm);
    if (!tab || g_hash_table_size(tab) == 0) {
        fputc('\n', out);
        fclose(out);
        return;
    }

    /* construir array */
    GPtrArray *arr = g_ptr_array_new_full(g_hash_table_size(tab), free);

    GHashTableIter it;
    gpointer key, val;
    g_hash_table_iter_init(&it, tab);

    while (g_hash_table_iter_next(&it, &key, &val)) {
        const char *airline = (const char *)key;
        const Q5AirlineStat *st = (const Q5AirlineStat *)val;
        if (!st || st->delayed_count <= 0) continue;

        Q5Row *row = malloc(sizeof(*row));
        if (!row) continue;

        row->airline = airline;
        row->delayed_count = st->delayed_count;
        row->avg_delay = (double)st->total_delay_minutes / (double)st->delayed_count;

        g_ptr_array_add(arr, row);
    }

    if (arr->len == 0) {
        fputc('\n', out);
        g_ptr_array_free(arr, TRUE);
        fclose(out);
        return;
    }

    g_ptr_array_sort(arr, cmp_q5_rows);

    /* output top N */
    guint limit = (N < (int)arr->len) ? (guint)N : arr->len;
    for (guint i = 0; i < limit; i++) {
        Q5Row *r = g_ptr_array_index(arr, i);
        fprintf(out, "%s%c%ld%c%.3f\n", r->airline, sep, r->delayed_count, sep, r->avg_delay);
    }

    g_ptr_array_free(arr, TRUE);
    fclose(out);
}
