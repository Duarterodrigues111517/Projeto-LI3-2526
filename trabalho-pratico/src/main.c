#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Parser/parser.h"
#include "Parser/airports_parser.h"
#include "Parser/aircrafts_parser.h"
#include "Parser/flights_parser.h"
#include "Parser/reservations_parser.h"
#include "Parser/passengers_parser.h"
#include "Parser/parser_queries.h"
#include "Queries/query6.h"


#ifndef OUTPUT_DIR
#define OUTPUT_DIR "resultados/"
#endif

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <path dataset> <input>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *datasetDir = argv[1];
    const char *inputFile = argv[2]; // usa quando fores ler as queries
    const char *outputDir = OUTPUT_DIR;
    (void)outputDir; 
    char *airports_file = malloc(strlen(datasetDir) + strlen("/airports.csv") + 1);
    char *aircrafts_file = malloc(strlen(datasetDir) + strlen("/aircrafts.csv") + 1);
    char *flights_file = malloc(strlen(datasetDir) + strlen("/flights.csv") + 1);
    char *reservations_file = malloc(strlen(datasetDir) + strlen("/reservations.csv") + 1);
    char *passengers_file = malloc(strlen(datasetDir) + strlen("/passengers.csv") + 1);

    strcpy(airports_file, datasetDir);   strcat(airports_file, "/airports.csv");
    strcpy(aircrafts_file, datasetDir);  strcat(aircrafts_file, "/aircrafts.csv");
    strcpy(flights_file, datasetDir);    strcat(flights_file, "/flights.csv");
    strcpy(reservations_file, datasetDir); strcat(reservations_file, "/reservations.csv");
    strcpy(passengers_file, datasetDir); strcat(passengers_file, "/passengers.csv");

    AirportsManager_t *airports_table = parse_airports_file(airports_file);
    (void)airports_table; 
    AircraftsManager_t *aircrafts_mgr = parse_aircrafts_file(aircrafts_file);
    (void)aircrafts_mgr;
    FlightsManager_t *flights_mgr = parse_flights_file(flights_file, aircrafts_mgr);
    (void)flights_mgr;
    PassengersManager_t *passengers_mgr = parse_passengers_file(passengers_file);
    (void)passengers_mgr;
    ReservationsManager_t *reservations_mgr = parse_reservations_file(reservations_file, flights_mgr, passengers_mgr);
    (void)reservations_mgr;
    airports_manager_compute_passenger_counts(airports_table, flights_mgr, reservations_mgr);   
    GHashTable *q6_table =
    g_hash_table_new_full(g_str_hash, g_str_equal, free, (GDestroyNotify) g_hash_table_destroy);

    compute_q6(q6_table, reservations_mgr, flights_mgr, passengers_mgr);
   


    parse_queries(inputFile, airports_table, aircrafts_mgr, flights_mgr, q6_table);


    airports_manager_free(airports_table);
    aircrafts_manager_free(aircrafts_mgr);
    flights_manager_free(flights_mgr);
    reservations_manager_free(reservations_mgr);
    passengers_manager_free(passengers_mgr);


    g_hash_table_destroy(q6_table);
    free(airports_file);
    free(aircrafts_file);
    free(flights_file);
    free(reservations_file);
    free(passengers_file);

    return EXIT_SUCCESS;
}