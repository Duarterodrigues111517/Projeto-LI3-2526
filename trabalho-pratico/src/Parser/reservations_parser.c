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


static int parse_flight_ids_list_fast(const char *s, char *id1, size_t id1_sz, char *id2, size_t id2_sz, int *n_ids) {
    if (!s || !id1 || !id2 || !n_ids) return 0;

    size_t len = strlen(s);
    if (len < 2 || s[0] != '[' || s[len-1] != ']') return 0;

    const char *p = s + 1;              // after '['
    const char *end = s + len - 1;      // at ']'

    *n_ids = 0;
    id1[0] = '\0';
    id2[0] = '\0';

    while (p < end) {
        while (p < end && isspace((unsigned char)*p)) p++;
        if (p >= end) break;

        // Expect optional quote '
        if (*p == '\'') p++;

        // Read token until quote or comma or end
        const char *start = p;
        while (p < end && *p != '\'' && *p != ',' ) p++;
        const char *stop = p;

        // Skip closing quote if present
        if (p < end && *p == '\'') p++;

        // Trim trailing spaces inside token
        while (stop > start && isspace((unsigned char)stop[-1])) stop--;

        size_t tlen = (size_t)(stop - start);
        if (tlen > 0) {
            if (*n_ids == 0) {
                if (tlen >= id1_sz) return 0;
                memcpy(id1, start, tlen);
                id1[tlen] = '\0';
            } else if (*n_ids == 1) {
                if (tlen >= id2_sz) return 0;
                memcpy(id2, start, tlen);
                id2[tlen] = '\0';
            } else {
                return 0; // >2 ids invalid
            }
            (*n_ids)++;
        }

        // Move to next (skip spaces and optional comma)
        while (p < end && isspace((unsigned char)*p)) p++;
        if (p < end && *p == ',') p++;
    }

    return (*n_ids >= 1 && *n_ids <= 2);
}


int parse_reservation_row(GArray *f, const char *raw, const char *header,
                          ReservationsManager_t *mgr,
                          FlightsManager_t *fl_mgr,
                          PassengersManager_t *p_mgr,
                          FILE **errors_fp)
{
    if (f->len != 8) {
        ensure_errors_file(errors_fp, RESERVATIONS_ERR_PATH, header);
        if (*errors_fp) fputs(raw, *errors_fp);
        return 0;
    }

    const char *reservation_id    = g_array_index(f, char*, 0);
    const char *flight_ids_field  = g_array_index(f, char*, 1); 
    const char *document_s        = g_array_index(f, char*, 2);
    const char *seat              = g_array_index(f, char*, 3);
    const char *price_s           = g_array_index(f, char*, 4);


    int ok = 1;

    // validações básicas de strings
    ok &= is_valid_reservation_id(reservation_id); // R + 9 dígitos
    ok &= is_valid_document_number(document_s);    // 9 dígitos
    ok &= is_nonempty_str(seat);                   // não vazio
               // não vazio

    int document_number = 0;
    double price = 0.0;


    if (ok) ok &= parse_int_strict(document_s, &document_number);
    if (ok) ok &= parse_double_strict(price_s, &price);

    // parse e validar lista de flight ids
    char flight_id1[32], flight_id2[32];
    int n_ids = 0;

    if (ok) ok &= parse_flight_ids_list_fast(flight_ids_field, flight_id1, sizeof(flight_id1), flight_id2, sizeof(flight_id2), &n_ids);
    if (ok) {
        ok &= is_valid_flight_id(flight_id1);
        if (n_ids == 2) ok &= is_valid_flight_id(flight_id2);
    }


    // -------- validações LÓGICAS com os managers --------
    if (ok) {
        // flight ids têm de existir em flights_manager
        Flight *f1 = flights_manager_get(fl_mgr, flight_id1);
        Flight *f2 = NULL;

        if (!f1) {
            ok = 0;
        }

        if (ok && n_ids == 2) {
            f2 = flights_manager_get(fl_mgr, flight_id2);
            if (!f2) ok = 0;
        }

        // document number tem de existir em passengers_manager
        if (ok) {
            Passenger *p = passengers_manager_get(p_mgr, document_s);
            if (!p) ok = 0;
        }

        // se houver 2 voos, destino do 1º = origem do 2º
        if (ok && n_ids==2 && f1 && f2) {
            const char *dest1 = flight_get_destination(f1);
            const char *orig2 = flight_get_origin(f2);
            if (!dest1 || !orig2 || strcmp(dest1, orig2) != 0) {
                ok = 0;
            }
        }
    }

    if (!ok) {
        ensure_errors_file(errors_fp, RESERVATIONS_ERR_PATH, header);
        if (*errors_fp) fputs(raw, *errors_fp);
        return 0;
    }

    // criar reserva com 1 ou 2 voos
    Reservation *r = reservation_new(reservation_id,
                                     flight_id1,
                                     flight_id2,           
                                     document_number,
                                     seat,
                                     price);



    if (!r) {
        ensure_errors_file(errors_fp, RESERVATIONS_ERR_PATH, header);
        if (*errors_fp) fputs(raw, *errors_fp);
        return 0;
    }

    reservations_manager_add(mgr, r);
    return 1;
}

ReservationsManager_t *parse_reservations_file(const char *path,
                                               FlightsManager_t *fl_mgr,
                                               PassengersManager_t *p_mgr)
{
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
        parse_reservation_row(fields, raw, header, mgr, fl_mgr, p_mgr, &errors_fp);
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
