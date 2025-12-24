#include "Parser/airports_parser.h"
#include "utils/validators.h"
#include <string.h>
#include <stdio.h>

#define AIRPORTS_ERR_PATH "resultados/airports_errors.csv"

static void ensure_errors_file(FILE **fp, const char *path, const char *header) {
    if (*fp) return;
    *fp = fopen(path, "w");
    if (*fp) fputs(header, *fp); 
}

static int parse_double_strict(const char *s, double *out) {
    
    char *end = NULL;
    errno = 0;
    double v = strtod(s, &end);
    if (errno != 0 || end == s || *end != '\0') return 0;
    *out = v;
    return 1;
}

int parse_airport_row(GArray *f, const char *raw, const char *header,
                      AirportsManager_t *mgr, FILE **errors_fp)
{
    if (f->len != 8) {
        ensure_errors_file(errors_fp, "resultados/airports_errors.csv", header);
        if (*errors_fp) fputs(raw, *errors_fp);
        return 0;
    }

    const char *code     = g_array_index(f, char*, 0);
    const char *name     = g_array_index(f, char*, 1);
    const char *city     = g_array_index(f, char*, 2);
    const char *country  = g_array_index(f, char*, 3);
    const char *lat_s    = g_array_index(f, char*, 4);
    const char *lon_s    = g_array_index(f, char*, 5);
    const char *icao     = g_array_index(f, char*, 6);
    const char *type     = g_array_index(f, char*, 7);

    int ok = 1;
    ok &= is_valid_iata3(code);
    ok &= is_valid_lat(lat_s);
    ok &= is_valid_lon(lon_s);
    ok &= is_valid_airport_type(type);

    double lat = 0.0, lon = 0.0;
    if (ok) {
        
        ok &= parse_double_strict(lat_s, &lat);
        ok &= parse_double_strict(lon_s, &lon);
    }

    if (!ok) {
        ensure_errors_file(errors_fp, "resultados/airports_errors.csv", header);
        if (*errors_fp) fputs(raw, *errors_fp);
        return 0;
    }

   
    Airport *a = airport_new(code, name, city, country, icao, type, lat, lon, 0, 0);
    airports_manager_add(mgr, a);
    return 1;
}


AirportsManager_t *parse_airports_file(const char *path) {
    AirportsManager_t *mgr = airports_manager_new();
    FILE *fp = fopen(path, "r");
    if (!fp) { perror("airports.csv"); return mgr; }

    GArray *fields = g_array_new(FALSE, FALSE, sizeof(char *));
    char *raw = NULL;
    char *header = NULL;
    FILE *errors_fp = NULL;

    if (!process_line(fp, fields, &raw)) goto cleanup;
    header = g_strdup(raw);
    free(raw); raw = NULL;

    while (process_line(fp, fields, &raw)) {
        parse_airport_row(fields, raw, header, mgr, &errors_fp);
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
