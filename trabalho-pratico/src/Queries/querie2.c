// Queries/querie2.c
#include "Queries/querie2.h"
#include <glib.h>
#include <stdio.h>
#include <string.h>

typedef struct {
    Aircraft *aircraft;
    int       flight_count;
} AircraftCount;

/* Comparator para ordenar:
 * 1) mais voos primeiro (desc)
 * 2) em empate, id da aeronave por ordem crescente (strcmp)
 */
static gint aircraft_count_cmp(gconstpointer pa, gconstpointer pb) {
    const AircraftCount *a = pa;
    const AircraftCount *b = pb;

    if (a->flight_count != b->flight_count) {
        /* desc: b - a */
        return (b->flight_count - a->flight_count);
    }

    const char *id_a = aircraft_get_id(a->aircraft);
    const char *id_b = aircraft_get_id(b->aircraft);

    return strcmp(id_a, id_b);  // lexicográfico ascendente
}

/* Callback para iterar sobre voos e preencher a hash de contagens.
 * Vais precisar de adaptar ao teu FlightsManager:
 *   - como iteras sobre os voos
 *   - como obténs status e aircraft_id
 */

typedef struct {
    GHashTable *counts;   // char* -> int*
} CountContext;

static void count_flight_callback(Flight *f, void *user_data) {
    CountContext *ctx = user_data;

    const char *status = flight_get_status(f);
    if (!status) return;

    /* Só contam voos com estado diferente de "Cancelled" */
    if (strcmp(status, "Cancelled") == 0) return;

    const char *aircraft_id = flight_get_aircraft_id(f);

    if (!aircraft_id) return;

    int *count = g_hash_table_lookup(ctx->counts, aircraft_id);
    if (!count) {
        count = g_new0(int, 1);
        *count = 0;
        g_hash_table_insert(ctx->counts, g_strdup(aircraft_id), count);
    }

    (*count)++;
}

void querie2(int N,
             const char *manufacturer_filter,
             const AircraftsManager_t *aircrafts,
             const FlightsManager_t *flights,
             const char *output_path)
{
    if (N <= 0 || !aircrafts || !flights || !output_path) {
        // Cria ficheiro vazio com \n, como nas outras queries
        FILE *f = fopen(output_path, "w");
        if (f) { fputc('\n', f); fclose(f); }
        return;
    }

    /* 1) Contar voos por aeronave */

    GHashTable *counts = g_hash_table_new_full(g_str_hash, g_str_equal,
                                               g_free, g_free);  // key, value

    CountContext ctx = { .counts = counts };

    /* Aqui tens de adaptar para a forma como percorres todos os voos.
     * Exemplos possíveis:
     *   flights_manager_foreach(flights, count_flight_callback, &ctx);
     *   ou obter um array de voos e fazer um ciclo for.
     */
    flights_manager_foreach((FlightsManager_t *)flights,
                        count_flight_callback,
                        &ctx);

    /* 2) Converter hash em array de AircraftCount, já filtrando por fabricante (se houver) */

    GPtrArray *array = g_ptr_array_new_with_free_func(g_free); // liberta AircraftCount

    GHashTableIter it;
    gpointer key, value;
    g_hash_table_iter_init(&it, counts);
    while (g_hash_table_iter_next(&it, &key, &value)) {
        char *aircraft_id = key;
        int  *count       = value;

        Aircraft *a = aircrafts_manager_get(aircrafts, aircraft_id);
        if (!a) continue;  // em princípio não acontece se validação estiver ok

        if (manufacturer_filter && *manufacturer_filter) {
            const char *m = aircraft_get_manufacturer(a);
            if (!m || strcmp(m, manufacturer_filter) != 0) {
                continue;
            }
        }

        AircraftCount *ac = g_new(AircraftCount, 1);
        ac->aircraft     = a;
        ac->flight_count = *count;

        g_ptr_array_add(array, ac);
    }

    /* Já não precisamos da hash de contagens */
    g_hash_table_destroy(counts);

    /* 3) Ordenar */

    g_ptr_array_sort(array, aircraft_count_cmp);

    /* 4) Escrever para o ficheiro */

    FILE *fout = fopen(output_path, "w");
    if (!fout) {
        perror("Erro ao abrir ficheiro de output da query 2");
        g_ptr_array_free(array, TRUE);
        return;
    }

    int limit = (N < (int)array->len) ? N : (int)array->len;

    for (int i = 0; i < limit; i++) {
        AircraftCount *ac = g_ptr_array_index(array, i);
        const char *id   = aircraft_get_id(ac->aircraft);
        const char *man  = aircraft_get_manufacturer(ac->aircraft);
        const char *model= aircraft_get_model(ac->aircraft);

        if (!id)    id    = "";
        if (!man)   man   = "";
        if (!model) model = "";

        /* Ajusta aqui o formato: ';' ou ',' conforme o esperado pelos testes */
        fprintf(fout, "%s;%s;%s;%d\n", id, man, model, ac->flight_count);
    }

    if (limit == 0) {
        /* Pelo enunciado, se não houver nada, normalmente põem só uma linha vazia */
        fputc('\n', fout);
    }

    fclose(fout);
    g_ptr_array_free(array, TRUE);
}

