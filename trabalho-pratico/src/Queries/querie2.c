#include "Queries/querie2.h"

#include <glib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura auxiliar para ordenar resultados
typedef struct {
    Aircraft *aircraft;
    int flight_count;
} Q2Entry;

/**
 * Callback usado em flights_manager_foreach
 * Conta voos NÃO cancelados por aeronave.
 */
static void count_flights_cb(Flight *f, void *user_data) {
    if (!f || !user_data) return;

    GHashTable *counts = (GHashTable *)user_data;

    const char *status = flight_get_status(f);
    if (status && strcmp(status, "Cancelled") == 0) {
        // Ignorar voos cancelados
        return;
    }

    const char *aircraft_id = flight_get_aircraft(f);
    if (!aircraft_id || aircraft_id[0] == '\0')
        return;

    int *cnt = g_hash_table_lookup(counts, aircraft_id);
    if (!cnt) {
        cnt = g_new(int, 1);
        if (!cnt) return; // sem memória; em contexto real podias tratar melhor
        *cnt = 0;
        g_hash_table_insert(counts, g_strdup(aircraft_id), cnt);
    }
    (*cnt)++;
}

// Comparador para qsort: 1º nº de voos (desc), depois id da aeronave (asc)
static int cmp_q2entry(const void *pa, const void *pb) {
    const Q2Entry *a = (const Q2Entry *)pa;
    const Q2Entry *b = (const Q2Entry *)pb;

    if (a->flight_count != b->flight_count) {
        // maior nº de voos primeiro
        return (b->flight_count - a->flight_count);
    }

    const char *id_a = aircraft_get_id(a->aircraft);
    const char *id_b = aircraft_get_id(b->aircraft);
    if (!id_a) id_a = "";
    if (!id_b) id_b = "";

    return strcmp(id_a, id_b);
}

void querie2(int N,
             const char *manufacturer_filter,
             AircraftsManager_t *acm,
             FlightsManager_t *fm,
             const char *output_path)
{
    // Segurança básica: se algo está marado, cria ficheiro vazio para
    // não falhar completamente a query.
    if (!output_path) return;

    FILE *f = fopen(output_path, "w");
    if (!f) {
        perror("querie2: fopen");
        return;
    }

    if (N <= 0 || !acm || !fm) {
        // Query sem sentido -> ficheiro com linha vazia
        fputc('\n', f);
        fclose(f);
        return;
    }

    // Tabela: aircraft_id -> int* (contagem de voos não cancelados)
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

    // 1) Contar voos não cancelados por aeronave
    flights_manager_foreach(fm, count_flights_cb, counts);

    if (g_hash_table_size(counts) == 0) {
        // Não há voos válidos -> linha vazia
        fputc('\n', f);
        g_hash_table_destroy(counts);
        fclose(f);
        return;
    }

    // 2) Transformar hash em array de entradas, aplicando filtro por manufacturer (se existir)
    int max_entries = g_hash_table_size(counts);
    Q2Entry *entries = malloc(sizeof(Q2Entry) * max_entries);
    if (!entries) {
        fputc('\n', f);
        g_hash_table_destroy(counts);
        fclose(f);
        return;
    }

    int used = 0;
    GHashTableIter iter;
    gpointer key, value;

    g_hash_table_iter_init(&iter, counts);
    while (g_hash_table_iter_next(&iter, &key, &value)) {
        char *aircraft_id = (char *)key;
        int  *cnt_ptr     = (int *)value;

        Aircraft *a = aircrafts_manager_get(acm, aircraft_id);
        if (!a) continue; // aeronave não encontrada (dados inconsistentes) -> ignora

        // Se houver filtro de manufacturer, aplica
        const char *man = aircraft_get_manufacturer(a);
        if (manufacturer_filter && manufacturer_filter[0] != '\0') {
            if (!man || strcmp(manufacturer_filter, man) != 0) {
                continue;
            }
        }

        entries[used].aircraft = a;
        entries[used].flight_count = *cnt_ptr;
        used++;
    }

    if (used == 0) {
        // Não sobrou nenhuma aeronave depois do filtro -> linha vazia
        fputc('\n', f);
        free(entries);
        g_hash_table_destroy(counts);
        fclose(f);
        return;
    }

    // 3) Ordenar resultados
    qsort(entries, used, sizeof(Q2Entry), cmp_q2entry);

    // 4) Escrever no ficheiro até N linhas
    if (N > used) N = used;

    for (int i = 0; i < N; i++) {
        Aircraft *a = entries[i].aircraft;
        const char *id    = aircraft_get_id(a);
        const char *man   = aircraft_get_manufacturer(a);
        const char *model = aircraft_get_model(a);

        if (!id)    id    = "";
        if (!man)   man   = "";
        if (!model) model = "";

        // Mesmo estilo de separador que usaste na querie1 (vírgula)
        fprintf(f, "%s,%s,%s,%d\n",
                id,
                man,
                model,
                entries[i].flight_count);
    }

    // 5) Limpeza
    free(entries);
    g_hash_table_destroy(counts);
    fclose(f);
}
