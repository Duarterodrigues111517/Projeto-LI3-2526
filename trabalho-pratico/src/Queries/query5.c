#include "Queries/query5.h"
#include <glib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *airline;        /* duplicado para ser seguro fora da hash */
    long delayed_count;
    double avg_delay;
} Q5Row;

static int cmp_q5_rows_qsort(const void *a, const void *b) {
    const Q5Row *ra = (const Q5Row *)a;
    const Q5Row *rb = (const Q5Row *)b;

    /* avg_delay desc */
    if (ra->avg_delay < rb->avg_delay) return 1;
    if (ra->avg_delay > rb->avg_delay) return -1;

    /* tie: airline asc */
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

    /* 1) contar quantas linhas válidas vamos ter */
    size_t cap = g_hash_table_size(tab);
    Q5Row *rows = malloc(sizeof(Q5Row) * cap);
    if (!rows) {
        fputc('\n', out);
        fclose(out);
        return;
    }

    size_t n_rows = 0;

    /* 2) preencher array */
    GHashTableIter it;
    gpointer key, val;
    g_hash_table_iter_init(&it, tab);

    while (g_hash_table_iter_next(&it, &key, &val)) {
        const char *airline = (const char *)key;
        const Q5AirlineStat *st = (const Q5AirlineStat *)val;
        if (!st || st->delayed_count <= 0) continue;

        rows[n_rows].airline = strdup(airline); /* segurança */
        if (!rows[n_rows].airline) continue;

        rows[n_rows].delayed_count = st->delayed_count;
        rows[n_rows].avg_delay =
            (double)st->total_delay_minutes / (double)st->delayed_count;

        n_rows++;
    }

    if (n_rows == 0) {
        fputc('\n', out);
        free(rows);
        fclose(out);
        return;
    }

    /* 3) sort com qsort */
    qsort(rows, n_rows, sizeof(Q5Row), cmp_q5_rows_qsort);

    /* 4) output top N */
    size_t limit = (N < (int)n_rows) ? (size_t)N : n_rows;
    for (size_t i = 0; i < limit; i++) {
        fprintf(out, "%s%c%ld%c%.3f\n",
                rows[i].airline, sep,
                rows[i].delayed_count, sep,
                rows[i].avg_delay);
    }

    /* 5) free */
    for (size_t i = 0; i < n_rows; i++) {
        free(rows[i].airline);
    }
    free(rows);
    fclose(out);
}
