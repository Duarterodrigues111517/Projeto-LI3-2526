#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Parser/airports_parser.h"
#include "Parser/aircrafts_parser.h"
#include "Parser/flights_parser.h"
#include "Parser/passengers_parser.h"
#include "Parser/reservations_parser.h"

#include "Queries/query1.h"



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