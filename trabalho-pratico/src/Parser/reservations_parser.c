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
static int parse_bool_flex(const char *s, bool *out) {
    if (!s) return 0;
    if (!strcasecmp(s,"true") || !strcmp(s,"1") || !strcasecmp(s,"yes")  || !strcasecmp(s,"sim"))  { *out = true;  return 1; }
    if (!strcasecmp(s,"false")|| !strcmp(s,"0") || !strcasecmp(s,"no")   || !strcasecmp(s,"nao")   || !strcasecmp(s,"não")) { *out = false; return 1; }
    return 0;
}

static int parse_flight_ids_list(const char *s, char **out1, char **out2) {
    *out1 = NULL;
    *out2 = NULL;
    if (!s) return 0;

    size_t len = strlen(s);
    if (len < 2 || s[0] != '[' || s[len-1] != ']') {
        return 0;
    }

    // copiar conteúdo entre [ e ]
    char *inner = strndup(s + 1, len - 2);
    if (!inner) return 0;

    // remover aspas simples
    char *p = inner, *q = inner;
    while (*p) {
        if (*p != '\'') *q++ = *p;
        p++;
    }
    *q = '\0';

    // separar por vírgulas
    int count = 0;
    char *tok = strtok(inner, ",");
    while (tok) {
        while (isspace((unsigned char)*tok)) tok++;
        char *end = tok + strlen(tok);
        while (end > tok && isspace((unsigned char)end[-1])) {
            end--;
        }
        *end = '\0';

        if (*tok != '\0') {
            if (count == 0) {
                *out1 = strdup(tok);
                if (!*out1) { free(inner); return 0; }
            } else if (count == 1) {
                *out2 = strdup(tok);
                if (!*out2) { free(inner); free(*out1); *out1 = NULL; return 0; }
            } else {
                free(inner);
                free(*out1); free(*out2);
                *out1 = *out2 = NULL;
                return 0;
            }
            count++;
        }

        tok = strtok(NULL, ",");
    }

    free(inner);

    if (count == 0) {
        // lista vazia → inválido
        free(*out1); free(*out2);
        *out1 = *out2 = NULL;
        return 0;
    }

    // count == 1 ou 2 é aceite
    return 1;
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
    const char *extra_luggage_s   = g_array_index(f, char*, 5);
    const char *priority_board_s  = g_array_index(f, char*, 6);
    const char *qr_code           = g_array_index(f, char*, 7);

    int ok = 1;

    // validações básicas de strings
    ok &= is_valid_reservation_id(reservation_id); // R + 9 dígitos
    ok &= is_valid_document_number(document_s);    // 9 dígitos
    ok &= is_nonempty_str(seat);                   // não vazio
    ok &= is_nonempty_str(qr_code);                // não vazio

    int document_number = 0;
    double price = 0.0;
    bool extra_luggage = false;
    bool priority_boarding = false;

    if (ok) ok &= parse_int_strict(document_s, &document_number);
    if (ok) ok &= parse_double_strict(price_s, &price);
    if (ok) ok &= parse_bool_flex(extra_luggage_s, &extra_luggage);
    if (ok) ok &= parse_bool_flex(priority_board_s, &priority_boarding);

    // parse e validar lista de flight ids
    char *flight_id1 = NULL;
    char *flight_id2 = NULL;

    if (ok) {
        ok &= parse_flight_ids_list(flight_ids_field, &flight_id1, &flight_id2);
    }

    if (ok) {
        // validação sintática de cada flight id individual
        ok &= is_valid_flight_id(flight_id1);
        if (flight_id2) ok &= is_valid_flight_id(flight_id2);
    }

    // -------- validações LÓGICAS com os managers --------
    if (ok) {
        // flight ids têm de existir em flights_manager
        Flight *f1 = flights_manager_get(fl_mgr, flight_id1);
        Flight *f2 = NULL;

        if (!f1) {
            ok = 0;
        }

        if (ok && flight_id2) {
            f2 = flights_manager_get(fl_mgr, flight_id2);
            if (!f2) ok = 0;
        }

        // document number tem de existir em passengers_manager
        if (ok) {
            Passenger *p = passengers_manager_get(p_mgr, document_s);
            if (!p) ok = 0;
        }

        // se houver 2 voos, destino do 1º = origem do 2º
        if (ok && flight_id2 && f1 && f2) {
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
        free(flight_id1);
        free(flight_id2);
        return 0;
    }

    // criar reserva com 1 ou 2 voos
    Reservation *r = reservation_new(reservation_id,
                                     flight_id1,
                                     flight_id2,           
                                     document_number,
                                     seat,
                                     price,
                                     extra_luggage,
                                     priority_boarding,
                                     qr_code);

    free(flight_id1);
    free(flight_id2);

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
