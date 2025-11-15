#include "Queries/querie3.h"

#include <glib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Estrutura de contexto para o foreach dos voos */
typedef struct {
    const char *start_date;  // "YYYY-MM-DD"
    const char *end_date;    // "YYYY-MM-DD"
    GHashTable *counts;      // key: airport code (char*) ; value: int*
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

/**
 * Callback usado em flights_manager_foreach
 * Conta partidas NÃO canceladas por aeroporto de origem, num intervalo de datas.
 */
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
        if (!cnt) return; // sem memória
        *cnt = 0;
        g_hash_table_insert(counts, g_strdup(origin), cnt);
    }

}

void querie3(const char *start_date,
             const char *end_date,
             AirportsManager_t *am,
             FlightsManager_t *fm,
             const char *output_path)
{
    // Segurança básica: se algo está marado, cria ficheiro vazio
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

    // Tabela: airport_code -> int* (contagem de partidas)
    GHashTable *counts = g_hash_table_new_full(
        g_str_hash,
        g_str_equal,
        g_free,   // free da key (g_strdup)
        g_free    // free do int*
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

    // 1) Contar partidas não canceladas, no intervalo de datas
    flights_manager_foreach(fm, count_departures_cb, &ctx);

    if (g_hash_table_size(counts) == 0) {
        // Não há voos válidos -> linha vazia
        fputc('\n', f);
        g_hash_table_destroy(counts);
        fclose(f);
        return;
    }

    // 2) Encontrar o aeroporto com mais partidas.
    //    Em empate, código menor em ordem lexicográfica.
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
        // Muito improvável aqui, mas por segurança
        fputc('\n', f);
        g_hash_table_destroy(counts);
        fclose(f);
        return;
    }

    // 3) Ir buscar info do aeroporto ao AirportsManager
    Airport *ap = airports_manager_get(am, best_code);
    const char *name    = ap ? airport_get_name(ap)    : "";
    const char *city    = ap ? airport_get_city(ap)    : "";
    const char *country = ap ? airport_get_country(ap) : "";

    if (!name)    name    = "";
    if (!city)    city    = "";
    if (!country) country = "";

    // 4) Escrever output:
    //    code,name,city,country,departure count
    //    (mesmo estilo de separador da querie1/2: vírgula, sem espaços)
    fprintf(f, "%s,%s,%s,%s,%d\n",
            best_code,
            name,
            city,
            country,
            best_count);

    // 5) Limpeza
    g_hash_table_destroy(counts);
    fclose(f);
}
