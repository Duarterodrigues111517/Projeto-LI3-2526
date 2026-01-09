#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include <glib.h>

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

#define BUF 512


/* helpers básicos                                       */


static void trim_newline(char *s) {
    if (!s) return;
    s[strcspn(s, "\r\n")] = '\0';
}

static void read_line_or_exit(const char *prompt, char *buf, size_t sz) {
    while (1) {
        printf("%s", prompt);
        fflush(stdout);

        if (!fgets(buf, (int)sz, stdin)) {
            printf("\nEOF recebido. A sair.\n");
            exit(0);
        }

        trim_newline(buf);

        if (buf[0] != '\0') return;

        printf("Entrada inválida. Tente novamente.\n");
    }
}

static int read_positive_int(const char *prompt) {
    char line[BUF];

    while (1) {
        printf("%s", prompt);
        fflush(stdout);

        if (!fgets(line, sizeof(line), stdin)) {
            printf("\nEOF recebido. A sair.\n");
            exit(0);
        }

        trim_newline(line);

        char *end = NULL;
        long v = strtol(line, &end, 10);

        while (end && (*end == ' ' || *end == '\t')) end++;

        if (end != line && *end == '\0' && v > 0)
            return (int)v;

        printf("Valor inválido. Tente novamente.\n");
    }
}


/* parsing do número da query (1, 1S, etc)               */


static int parse_query(const char *s, int *qid, char *sep) {
    if (!s || !qid || !sep) return 0;

    while (*s == ' ' || *s == '\t') s++;

    char *end = NULL;
    long v = strtol(s, &end, 10);

    if (end == s || v <= 0) return 0;

    *qid = (int)v;
    *sep = ';';

    if (*end == 'S') {
        *sep = '=';
        end++;
    }

    while (*end == ' ' || *end == '\t') end++;

    return (*end == '\0');
}


/* main                                                  */


int main(void) {
    char dataset[BUF];

    read_line_or_exit(
        "Introduza o caminho do dataset: ",
        dataset, sizeof(dataset)
    );

    /* construir caminhos */
    char airports_p[BUF], aircrafts_p[BUF], flights_p[BUF];
    char passengers_p[BUF], reservations_p[BUF];

    snprintf(airports_p,     sizeof(airports_p),     "%s/airports.csv",     dataset);
    snprintf(aircrafts_p,    sizeof(aircrafts_p),    "%s/aircrafts.csv",    dataset);
    snprintf(flights_p,      sizeof(flights_p),      "%s/flights.csv",      dataset);
    snprintf(passengers_p,   sizeof(passengers_p),   "%s/passengers.csv",   dataset);
    snprintf(reservations_p, sizeof(reservations_p), "%s/reservations.csv", dataset);

    /* carregar dados */
    AirportsManager_t     *am = parse_airports_file(airports_p);
    AircraftsManager_t    *acm = parse_aircrafts_file(aircrafts_p);
    FlightsManager_t      *fm = parse_flights_file(flights_p, acm);
    PassengersManager_t   *pm = parse_passengers_file(passengers_p);
    ReservationsManager_t *rm = parse_reservations_file(reservations_p, fm, pm);

    airports_manager_compute_passenger_counts(am, fm, rm);

    GHashTable *q6_table =
        g_hash_table_new_full(g_str_hash, g_str_equal, free,
                              (GDestroyNotify) g_hash_table_destroy);

    compute_q6(q6_table, rm, fm, pm);

    printf("\nDataset carregado com sucesso.\n");

    while (1) {
        char qline[BUF];
        int qid = 0;
        char sep = ';';

        printf("\nNúmero da query (1, 1S, 2, 2S, ... ou 0 para sair): ");
        fflush(stdout);

        if (!fgets(qline, sizeof(qline), stdin)) {
            printf("\nEOF recebido. A sair.\n");
            break;
        }

        trim_newline(qline);

        if (strcmp(qline, "0") == 0) {
            printf("A sair...\n");
            break;
        }

        if (!parse_query(qline, &qid, &sep)) {
            printf("Query inválida. Tente novamente.\n");
            continue;
        }

        
        /* QUERY 1                 */
        
        if (qid == 1) {
            char code[BUF];
            read_line_or_exit("Código do aeroporto: ", code, sizeof(code));
            querie1(code, sep, am, "/dev/stdout");
        }

        
        /* QUERY 2                 */
        
        else if (qid == 2) {
            int N = read_positive_int("Top N: ");

            char manufacturer[BUF];
            printf("Manufacturer (vazio para nenhum): ");
            fflush(stdout);
            fgets(manufacturer, sizeof(manufacturer), stdin);
            trim_newline(manufacturer);

            const char *man = (manufacturer[0] == '\0') ? NULL : manufacturer;

            querie2(N, man, sep, acm, fm, "/dev/stdout");
        }

        
        /* QUERY 3                 */
        
        else if (qid == 3) {
            char d1[BUF], d2[BUF];
            read_line_or_exit("Data inicial (YYYY-MM-DD): ", d1, sizeof(d1));
            read_line_or_exit("Data final   (YYYY-MM-DD): ", d2, sizeof(d2));

            querie3(d1, d2, sep, am, fm, "/dev/stdout");
        }

        
        /* QUERY 4 (não feita)     */
        
        else if (qid == 4) {
            printf("Query 4 não está implementada.\n");
        }

        
        /* QUERY 5                 */
        
        else if (qid == 5) {
            int N = read_positive_int("Top N companhias: ");

            char nbuf[32];
            snprintf(nbuf, sizeof(nbuf), "%d", N);

            querie5(nbuf, sep, fm, "/dev/stdout");
        }

        
        /* QUERY 6                 */
        
        else if (qid == 6) {
            char nat[BUF];
            read_line_or_exit("Nacionalidade: ", nat, sizeof(nat));
            querie6(nat, sep, q6_table, "/dev/stdout");
        }

        else {
            printf("Query desconhecida.\n");
        }
    }

    airports_manager_free(am);
    aircrafts_manager_free(acm);
    flights_manager_free(fm);
    passengers_manager_free(pm);
    reservations_manager_free(rm);
    g_hash_table_destroy(q6_table);

    return 0;
}
