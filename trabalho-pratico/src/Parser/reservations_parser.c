#include "Parser/reservations_parser.h"
#include "utils/validators.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <ctype.h>
#include <stdbool.h>

#define RESERVATIONS_ERR_PATH "resultados/reservations_errors.csv"

// cria ficheiro de erros só quando necessário (igual aos outros parsers)
static void ensure_errors_file(FILE **fp, const char *path, const char *header) {
    if (*fp) return;
    *fp = fopen(path, "w");
    if (*fp) fputs(header, *fp);
}

// conversões estritas (sem lixo no fim)
static int parse_int_strict(const char *s, int *out) {
    if (!s || !*s) return 0;
    char *end = NULL; errno = 0;
    long v = strtol(s, &end, 10);
    if (errno || end == s || *end != '\0') return 0;
    if (v < INT_MIN || v > INT_MAX) return 0;
    *out = (int)v; return 1;
}
static int parse_double_strict(const char *s, double *out) {
    if (!s || !*s) return 0;
    char *end = NULL; errno = 0;
    double v = strtod(s, &end);
    if (errno || end == s || *end != '\0') return 0;
    *out = v; return 1;
}
static int parse_bool_flex(const char *s, bool *out) {
    if (!s) return 0;
    if (!strcasecmp(s,"true") || !strcmp(s,"1") || !strcasecmp(s,"yes")  || !strcasecmp(s,"sim"))  { *out = true;  return 1; }
    if (!strcasecmp(s,"false")|| !strcmp(s,"0") || !strcasecmp(s,"no")   || !strcasecmp(s,"nao")   || !strcasecmp(s,"não")) { *out = false; return 1; }
    return 0;
}


int parse_reservation_row(GArray *f, const char *raw, const char *header,
                          ReservationsManager_t *mgr, FILE **errors_fp)
{
    if (f->len != 8) {
        ensure_errors_file(errors_fp, RESERVATIONS_ERR_PATH, header);
        if (*errors_fp) fputs(raw, *errors_fp);
        return 0;
    }

    const char *reservation_id    = g_array_index(f, char*, 0);
    const char *flight_id         = g_array_index(f, char*, 1);
    const char *document_s        = g_array_index(f, char*, 2);
    const char *seat              = g_array_index(f, char*, 3);
    const char *price_s           = g_array_index(f, char*, 4);
    const char *extra_luggage_s   = g_array_index(f, char*, 5);
    const char *priority_board_s  = g_array_index(f, char*, 6);
    const char *qr_code           = g_array_index(f, char*, 7);

    // validações sintáticas
    int ok = 1;
    ok &= is_valid_reservation_id(reservation_id); // R + 9 dígitos
    ok &= is_valid_flight_id(flight_id);           // ccdddddd
    ok &= is_valid_document_number(document_s);    // 9 dígitos
    ok &= is_nonempty_str(seat);                   // não vazio
    ok &= is_nonempty_str(qr_code);                // não vazio (ajusta se quiseres aceitar vazio)

    int document_number = 0;
    double price = 0.0;
    bool extra_luggage = false;
    bool priority_boarding = false;

    if (ok) ok &= parse_int_strict(document_s, &document_number);
    if (ok) ok &= parse_double_strict(price_s, &price);
    if (ok) ok &= parse_bool_flex(extra_luggage_s, &extra_luggage);
    if (ok) ok &= parse_bool_flex(priority_board_s, &priority_boarding);

    if (!ok) {
        ensure_errors_file(errors_fp, RESERVATIONS_ERR_PATH, header);
        if (*errors_fp) fputs(raw, *errors_fp);
        return 0;
    }

    // assinatura real (8 args):
    // Reservation *reservation_new(const char *reservation_id,
    //                              const char *flight_id,
    //                              int document_number,
    //                              const char *seat,
    //                              double price,
    //                              bool *extra_luggage,
    //                              bool *priority_boarding,
    //                              const char *qr_code);
    Reservation *r = reservation_new(reservation_id,
                                     flight_id,
                                     document_number,
                                     seat,
                                     price,
                                     &extra_luggage,
                                     &priority_boarding,
                                     qr_code);

    reservations_manager_add(mgr, r);
    return 1;
}


ReservationsManager_t *parse_reservations_file(const char *path) {
   ReservationsManager_t *mgr = reservations_manager_new();
    FILE *fp = fopen(path, "r");
    if (!fp) { perror("reservations.csv"); return mgr; }

    GArray *fields = g_array_new(FALSE, FALSE, sizeof(char *));
    char *raw = NULL;
    char *header = NULL;
    FILE *errors_fp = NULL;

    if (!process_line(fp, fields, &raw)) goto cleanup;
    header = g_strdup(raw);
    free(raw); raw = NULL;

    while (process_line(fp, fields, &raw)) {
        parse_reservation_row(fields, raw, header, mgr, &errors_fp);
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

