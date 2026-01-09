#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Parser/airports_parser.h"
#include "Parser/aircrafts_parser.h"
#include "Parser/flights_parser.h"
#include "Parser/passengers_parser.h"
#include "Parser/reservations_parser.h"

#include "Queries/query1.h"
// se quiseres mais queries, incluis aqui

int main(void) {
    char dataset_path[256];
    char airport_code[16];

    printf("Introduza o caminho dos ficheiros de dados: ");
    fflush(stdout);
    if (!fgets(dataset_path, sizeof(dataset_path), stdin)) {
        return 1;
    }
    dataset_path[strcspn(dataset_path, "\n")] = '\0';

    // construir paths
    char airports_file[300], aircrafts_file[300], flights_file[300];
    char passengers_file[300], reservations_file[300];

    snprintf(airports_file, sizeof(airports_file), "%s/airports.csv", dataset_path);
    snprintf(aircrafts_file, sizeof(aircrafts_file), "%s/aircrafts.csv", dataset_path);
    snprintf(flights_file, sizeof(flights_file), "%s/flights.csv", dataset_path);
    snprintf(passengers_file, sizeof(passengers_file), "%s/passengers.csv", dataset_path);
    snprintf(reservations_file, sizeof(reservations_file), "%s/reservations.csv", dataset_path);

    printf("Dataset carregado...\n");

    AirportsManager_t   *am = parse_airports_file(airports_file);
    AircraftsManager_t  *ac = parse_aircrafts_file(aircrafts_file);
    FlightsManager_t    *fm = parse_flights_file(flights_file, ac);
    PassengersManager_t *pm = parse_passengers_file(passengers_file);
    ReservationsManager_t *rm = parse_reservations_file(reservations_file, fm, pm);

    int q;
    printf("Que query deseja executar? ");
    fflush(stdout);
    if (scanf("%d", &q) != 1) {
        printf("Query inválida\n");
        return 1;
    }

    if (q == 1) {
        printf("Código do aeroporto: ");
        scanf("%15s", airport_code);

        // imprimir no terminal → usa stdout
        querie1(airport_code, ';', am, "/dev/stdout");
    } else {
        printf("Query não suportada no modo interativo.\n");
    }

    // libertar memória
    airports_manager_free(am);
    aircrafts_manager_free(ac);
    flights_manager_free(fm);
    passengers_manager_free(pm);
    reservations_manager_free(rm);

    return 0;
}
