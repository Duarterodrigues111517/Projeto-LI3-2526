#include "Parser/aircrafts_parser.h"
#include "utils/validators.h"
#include <ctype.h>
#include <string.h>
#include <stdio.h>

#define AIRCRAFTS_ERR_PATH "resultados/aircrafts_errors.csv"

// Mesmo helper do airports_parser
static void ensure_errors_file(FILE **fp, const char *path, const char *header) {
    if (*fp) return;
    *fp = fopen(path, "w");
    if (*fp) fputs(header, *fp); // header já inclui '\n'
}

// Inteiro estrito (sem lixo após o número)
static int parse_int_strict(const char *s, int *out) {
    if (!s || !*s) return 0;
    char *end = NULL;
    errno = 0;
    long v = strtol(s, &end, 10);
    if (errno != 0 || end == s || *end != '\0') return 0;
    if (v < INT_MIN || v > INT_MAX) return 0;
    *out = (int)v;
    return 1;
}

static int is_all_digits(const char *s) {
    if (!s || !*s) return 0;
    for (const unsigned char *p = (const unsigned char*)s; *p; p++)
        if (!isdigit(*p)) return 0;
    return 1;
}

static int is_nonempty(const char *s) {
    if (!s) return 0;
    while (*s && isspace((unsigned char)*s)) s++;
    return *s != '\0';
}

// yyyy e não no futuro (ajusta CURRENT_YEAR se necessário)
#define CURRENT_YEAR 2025
static int is_valid_year_yyyy(const char *s, int *out) {
    if (!s || strlen(s) != 4 || !is_all_digits(s)) return 0;
    int y = (int)strtol(s, NULL, 10);
    if (y < 0 || y > CURRENT_YEAR) return 0;
    if (out) *out = y;
    return 1;
}

int parse_aircraft_row(GArray *f, const char *raw, const char *header,
                       AircraftsManager_t *mgr, FILE **errors_fp)
{
    if (f->len != 6) {
        ensure_errors_file(errors_fp, "resultados/aircrafts_errors.csv", header);
        if (*errors_fp) fputs(raw, *errors_fp);
        return 0;
    }

    const char *identifier   = g_array_index(f, char*, 0);
    const char *manufacturer = g_array_index(f, char*, 1);
    const char *model        = g_array_index(f, char*, 2);
    const char *year_s       = g_array_index(f, char*, 3);
    const char *capacity_s   = g_array_index(f, char*, 4);
    const char *range_s      = g_array_index(f, char*, 5);

    int ok = 1;
    ok &= is_nonempty(identifier);
    ok &= is_nonempty(manufacturer);
    ok &= is_nonempty(model);

    int year = 0, capacity = 0, range = 0;
    ok &= is_valid_year_yyyy(year_s, &year);

    // capacity e range: inteiros positivos (validação sintática/lógica básica)
    if (ok) ok &= parse_int_strict(capacity_s, &capacity) && capacity > 0;
    if (ok) ok &= parse_int_strict(range_s, &range) && range > 0;

    if (!ok) {
        ensure_errors_file(errors_fp, "resultados/aircrafts_errors.csv", header);
        if (*errors_fp) fputs(raw, *errors_fp);
        return 0;
    }

    // Ajusta a assinatura de criação se o teu Aircraft for diferente
    Aircraft *a = aircraft_new(identifier, manufacturer, model, year, capacity, range);
    aircrafts_manager_add(mgr, a);
    return 1;
}


AircraftsManager_t *parse_aircrafts_file(const char *path) {
    AircraftsManager_t *mgr = aircrafts_manager_new();
    FILE *fp = fopen(path, "r");
    if (!fp) { perror("aircrafts.csv"); return mgr; }

    GArray *fields = g_array_new(FALSE, FALSE, sizeof(char *));
    char *raw = NULL;
    char *header = NULL;
    FILE *errors_fp = NULL;

    if (!process_line(fp, fields, &raw)) goto cleanup;
    header = g_strdup(raw);
    free(raw); raw = NULL;

    while (process_line(fp, fields, &raw)) {
        parse_aircraft_row(fields, raw, header, mgr, &errors_fp);
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
