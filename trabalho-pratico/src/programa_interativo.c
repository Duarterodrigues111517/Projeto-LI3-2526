#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Parser/airports_parser.h"
#include "Parser/aircrafts_parser.h"
#include "Parser/flights_parser.h"
#include "Parser/passengers_parser.h"
#include "Parser/reservations_parser.h"

#include "Queries/query1.h"
#include "Queries/query2.h"
#include "Queries/query3.h"
#include "Queries/query5.h"
#include "Queries/query6.h"

int main(void) {
    char dataset_path[512];

    printf("Introduza o caminho dos ficheiros de dados: ");
    fflush(stdout);

    if (!fgets(dataset_path, sizeof(dataset_path), stdin)) {
        fprintf(stderr, "Erro a ler caminho.\n");
        return 1;
    }
    dataset_path[strcspn(dataset_path, "\n")] = '\0';

    /* construir paths */
    char airports_file[600], aircrafts_file[600], flights_file[600];
    char passengers_file[600], reservations_file[600];

    snprintf(airports_file, sizeof(airports_file), "%s/airports.csv", dataset_path);
    snprintf(aircrafts_file, sizeof(aircrafts_file), "%s/aircrafts.csv", dataset_path);
    snprintf(flights_file, sizeof(flights_file), "%s/flights.csv", dataset_path);
    snprintf(passengers_file, sizeof(passengers_file), "%s/passengers.csv", dataset_path);
    snprintf(reservations_file, sizeof(reservations_file), "%s/reservations.csv", dataset_path);

    /* carregar dataset */
    AirportsManager_t *am = parse_airports_file(airports_file);
    AircraftsManager_t *acm = parse_aircrafts_file(aircrafts_file);
    FlightsManager_t *fm = parse_flights_file(flights_file, acm);
    PassengersManager_t *pm = parse_passengers_file(passengers_file);
    ReservationsManager_t *rm = parse_reservations_file(reservations_file, fm, pm);

    airports_manager_compute_passenger_counts(am, fm, rm);

    GHashTable *q6_table =
        g_hash_table_new_full(g_str_hash, g_str_equal, free,
                              (GDestroyNotify) g_hash_table_destroy);

    compute_q6(q6_table, rm, fm, pm);

    printf("Dataset carregado...\n");

    int q;
    printf("Que query deseja executar? ");
    fflush(stdout);

    if (scanf("%d", &q) != 1) {
        printf("Query inválida.\n");
        goto cleanup;
    }

    /* ---------------- QUERIES ---------------- */

    if (q == 1) {
        char code[16];
        printf("Código do aeroporto: ");
        scanf("%15s", code);

        querie1(code, ';', am, "/dev/stdout");

    } else if (q == 2) {
        int N;
        char manufacturer[128];

        printf("Top N: ");
        scanf("%d", &N);

        printf("Manufacturer (ou - para nenhum): ");
        scanf("%127s", manufacturer);

        const char *man = NULL;
        if (strcmp(manufacturer, "-") != 0)
            man = manufacturer;

        querie2(N, man, ';', acm, fm, "/dev/stdout");

    } else if (q == 3) {
        char start_date[32], end_date[32];

        printf("Data inicial (YYYY-MM-DD): ");
        scanf("%31s", start_date);

        printf("Data final (YYYY-MM-DD): ");
        scanf("%31s", end_date);

        querie3(start_date, end_date, ';', am, fm, "/dev/stdout");

    } else if (q == 4) {
        printf("Query 4 nao esta disponivel neste projeto.\n");

    } else if (q == 5) {
        int N;
        printf("Top N companhias: ");
        scanf("%d", &N);

        char buf[32];
        snprintf(buf, sizeof(buf), "%d", N);

        querie5(buf, ';', fm, "/dev/stdout");

    } else if (q == 6) {
        char nationality[64];
        printf("Nacionalidade: ");
        scanf("%63s", nationality);

        querie6(nationality, ';', q6_table, "/dev/stdout");

    } else {
        printf("Query invalida.\n");
    }

cleanup:
    airports_manager_free(am);
    aircrafts_manager_free(acm);
    flights_manager_free(fm);
    passengers_manager_free(pm);
    reservations_manager_free(rm);
    g_hash_table_destroy(q6_table);

    return 0;
}
