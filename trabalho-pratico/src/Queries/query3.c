#include "Queries/query3.h"

#include <glib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct {
    const char *start_date;  
    const char *end_date;    
    GHashTable *counts;      
} Q3Context;

static int datetime_in_range(const char *datetime,
                             const char *start_date,
                             const char *end_date)
{
    if (!datetime || strlen(datetime) < 10) return 0;
    if (!start_date || strlen(start_date) < 10) return 0;
    if (!end_date   || strlen(end_date)   < 10) return 0;

    int cmp_start = strncmp(datetime, start_date, 10);
    int cmp_end   = strncmp(datetime, end_date,   10);

    return (cmp_start >= 0 && cmp_end <= 0);
}

static void count_departures_cb(Flight *f, void *user_data) {
    if (!f || !user_data) return;

    Q3Context *ctx = (Q3Context *)user_data;
    GHashTable *counts = ctx->counts;

    const char *status = flight_get_status(f);
    if (status && strcmp(status, "Cancelled") == 0) {
        // Ignorar voos cancelados
        return;
    }

    const char *actual_dep = flight_get_actual_departure(f);
    if (!datetime_in_range(actual_dep, ctx->start_date, ctx->end_date)) {
        // Fora do intervalo de datas
        return;
    }

    const char *origin = flight_get_origin(f);
    if (!origin || origin[0] == '\0')
        return;

    int *cnt = g_hash_table_lookup(counts, origin);
    if (!cnt) {
        cnt = g_new(int, 1);
        if (!cnt) return; 
        *cnt = 0;
        g_hash_table_insert(counts, g_strdup(origin), cnt);
    }
    (*cnt)++; 
}

void querie3(const char *start_date,
             const char *end_date, char sep,
             AirportsManager_t *am,
             FlightsManager_t *fm,
             const char *output_path)
{
    if (!output_path) return;

    FILE *f = fopen(output_path, "w");
    if (!f) {
        perror("querie3: fopen");
        return;
    }

    if (!start_date || !end_date || !am || !fm) {
        // Query sem sentido -> ficheiro com linha vazia
        fputc('\n', f);
        fclose(f);
        return;
    }

    GHashTable *counts = g_hash_table_new_full(
        g_str_hash,
        g_str_equal,
        g_free,   
        g_free    
    );

    if (!counts) {
        fputc('\n', f);
        fclose(f);
        return;
    }

    Q3Context ctx = {
        .start_date = start_date,
        .end_date   = end_date,
        .counts     = counts
    };

    // Contar partidas não canceladas, no intervalo de datas
    flights_manager_foreach(fm, count_departures_cb, &ctx);

    if (g_hash_table_size(counts) == 0) {
        // Não há voos válidos -> linha vazia
        fputc('\n', f);
        g_hash_table_destroy(counts);
        fclose(f);
        return;
    }

    // Encontrar o aeroporto com mais partidas
    GHashTableIter iter;
    gpointer key, value;

    char *best_code = NULL;
    int   best_count = 0;

    g_hash_table_iter_init(&iter, counts);
    while (g_hash_table_iter_next(&iter, &key, &value)) {
        char *code = (char *)key;
        int  *cnt  = (int *)value;
        int   val  = cnt ? *cnt : 0;

        if (!best_code ||
            val > best_count ||
            (val == best_count && strcmp(code, best_code) < 0)) {

            best_code  = code;
            best_count = val;
        }
    }

    if (!best_code) {
        fputc('\n', f);
        g_hash_table_destroy(counts);
        fclose(f);
        return;
    }

    // Ir buscar info do aeroporto ao AirportsManager
    Airport *ap = airports_manager_get(am, best_code);
    const char *name    = ap ? airport_get_name(ap)    : "";
    const char *city    = ap ? airport_get_city(ap)    : "";
    const char *country = ap ? airport_get_country(ap) : "";

    if (!name)    name    = "";
    if (!city)    city    = "";
    if (!country) country = "";

    fprintf(f, "%s%c%s%c%s%c%s%c%d\n",
            best_code, sep,
            name, sep,
            city, sep,
            country, sep,
            best_count);

    // Limpeza
    g_hash_table_destroy(counts);
    fclose(f);
}
