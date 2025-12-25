#include "Parser/flights_parser.h"
#include "utils/validators.h"  
#include <string.h>
#include <stdio.h>

#define FLIGHTS_ERR_PATH "resultados/flights_errors.csv"

// igual ao airports_parser
static void ensure_errors_file(FILE **fp, const char *path, const char *header) {
    if (*fp) return;
    *fp = fopen(path, "w");
    if (*fp) fputs(header, *fp); 
}

static int is_aircraft_valid(const AircraftsManager_t *acm, const char *aircraft_id) {
    if (!acm || !aircraft_id) return 0;
    Aircraft *a = aircrafts_manager_get(acm, aircraft_id);
    return (a != NULL);
}

int parse_flight_row(GArray *f, const char *raw, const char *header,
                     FlightsManager_t *mgr, AircraftsManager_t *a_mgr,FILE **errors_fp)
{
    const int n = (int)f->len;
    if (n != 12) {
        ensure_errors_file(errors_fp, FLIGHTS_ERR_PATH, header);
        if (*errors_fp) fputs(raw, *errors_fp);
        return 0;
    }

    const char *id               = NULL;
    const char *departure        = NULL;
    const char *actual_departure = "N/A";
    const char *arrival          = NULL;
    const char *actual_arrival   = "N/A";
    const char *gate             = "";
    const char *status           = NULL;
    const char *origin           = NULL;
    const char *destination      = NULL;
    const char *aircraft         = NULL;
    const char *airline          = "";
    const char *tracking_url     = "";

        id               = g_array_index(f, char*, 0);
        departure        = g_array_index(f, char*, 1);
        actual_departure = g_array_index(f, char*, 2);
        arrival          = g_array_index(f, char*, 3);
        actual_arrival   = g_array_index(f, char*, 4);
        gate             = g_array_index(f, char*, 5);
        status           = g_array_index(f, char*, 6);
        origin           = g_array_index(f, char*, 7);
        destination      = g_array_index(f, char*, 8);
        aircraft         = g_array_index(f, char*, 9);
        airline          = g_array_index(f, char*, 10);
        tracking_url     = g_array_index(f, char*, 11);
    

    // -------- Validações sintáticas -----------
    int ok = 1;
    ok &= is_valid_flight_id(id);          
    ok &= is_valid_iata3(origin);
    ok &= is_valid_iata3(destination);
    ok &= (strcmp(origin, destination) != 0);

    ok &= is_valid_datetime(departure);
    ok &= is_valid_datetime(arrival);
    
    if (actual_departure && strcmp(actual_departure, "N/A") != 0)
        ok &= is_valid_datetime(actual_departure);
    if (actual_arrival && strcmp(actual_arrival, "N/A") != 0)
        ok &= is_valid_datetime(actual_arrival);

    ok &= is_valid_status(status);
    ok &= (compare_datetimes(departure, arrival) < 0); 
    ok &= is_aircraft_valid(a_mgr,aircraft);

    if (strcmp(status, "Cancelled") == 0) {
        ok &= (actual_departure != NULL && strcmp(actual_departure, "N/A") == 0);
        ok &= (actual_arrival   != NULL && strcmp(actual_arrival,   "N/A") == 0);
    }
    else {
        // Para voos não cancelados, os actual_* têm de existir e não podem ser "N/A"
        ok &= (actual_departure != NULL && strcmp(actual_departure, "N/A") != 0);
        ok &= (actual_arrival   != NULL && strcmp(actual_arrival,   "N/A") != 0);

        // E têm de ser datetime válidos
        ok &= is_valid_datetime(actual_departure);
        ok &= is_valid_datetime(actual_arrival);

        // Só depois faz sentido comparar
        ok &= (compare_datetimes(actual_departure, actual_arrival) < 0);

        if (strcmp(status, "Delayed") == 0) {
            ok &= (compare_datetimes(actual_departure, departure) > 0);
            ok &= (compare_datetimes(actual_arrival,   arrival)   > 0);
        }
    }

     // Se alguma validação falhar, escreve linha de erro
    if (!ok) {
        ensure_errors_file(errors_fp, FLIGHTS_ERR_PATH, header);
        if (*errors_fp) {
        fputs(raw, *errors_fp);

        size_t len = strlen(raw);
        if (len > 0 && raw[len - 1] != '\n') {
            fputc('\n', *errors_fp);
        }
    }
        return 0;
    }

    // -------- Criação e inserção -----------
    Flight *fl = flight_new(id,
                            departure,
                            actual_departure,
                            arrival,
                            actual_arrival,
                            gate,
                            status,
                            origin,
                            destination,
                            aircraft,
                            airline,
                            tracking_url);

    flights_manager_add(mgr, fl);
    return 1;
}


FlightsManager_t *parse_flights_file(const char *csvPath, AircraftsManager_t *a_mgr) {
    FILE *fp = fopen(csvPath, "r");
    if (!fp) { perror("flights.csv"); return flights_manager_new(); }

    FlightsManager_t *mgr = flights_manager_new();

    GArray *fields = g_array_new(FALSE, FALSE, sizeof(char *));
    char *raw = NULL;
    char *header = NULL;
    FILE *errors_fp = NULL;

    if (!process_line(fp, fields, &raw)) goto cleanup;
    header = g_strdup(raw);
    free(raw); raw = NULL;

    while (process_line(fp, fields, &raw)) {
        parse_flight_row(fields, raw, header, mgr,a_mgr, &errors_fp);
        free(raw); raw = NULL;
    }

cleanup:
    if (errors_fp) fclose(errors_fp);
    if (header) g_free(header);
    if (raw) free(raw);
    if (fields) free_garray_parsed(fields);
    fclose(fp);
    return mgr;
}


