// src/programa_interativo.c
#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>
#include <sys/stat.h>
#include <errno.h>

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

typedef struct AppData {
    AirportsManager_t *airports;
    AircraftsManager_t *aircrafts;
    FlightsManager_t *flights;
    PassengersManager_t *passengers;
    ReservationsManager_t *reservations;
    GHashTable *q6_table;

    char *dataset_dir;
} AppData;

/* ---------- helpers ---------- */

static void trim_newline(char *s) {
    if (!s) return;
    size_t n = strlen(s);
    while (n > 0 && (s[n - 1] == '\n' || s[n - 1] == '\r')) {
        s[n - 1] = '\0';
        n--;
    }
}

static char *read_line_prompt(const char *prompt) {
    if (prompt) {
        printf("%s", prompt);
        fflush(stdout);
    }

    char *line = NULL;
    size_t cap = 0;
    ssize_t n = getline(&line, &cap, stdin);
    if (n == -1) {
        free(line);
        return NULL;
    }
    trim_newline(line);
    return line;
}

static int ensure_results_dir(void) {
    struct stat st;
    if (stat(OUTPUT_DIR, &st) == 0) {
        if (S_ISDIR(st.st_mode)) return 1;
        fprintf(stderr, "Erro: '%s' existe mas não é diretoria.\n", OUTPUT_DIR);
        return 0;
    }

    if (mkdir(OUTPUT_DIR, 0777) != 0) {
        if (errno == EEXIST) return 1;
        perror("mkdir resultados");
        return 0;
    }
    return 1;
}

static char *path_join(const char *a, const char *b) {
    size_t la = strlen(a), lb = strlen(b);
    char *p = malloc(la + lb + 2);
    if (!p) return NULL;
    strcpy(p, a);
    if (la > 0 && a[la - 1] != '/') strcat(p, "/");
    strcat(p, b);
    return p;
}

/* ---------- load / free dataset ---------- */

static AppData *appdata_load(const char *dataset_dir) {
    if (!dataset_dir || dataset_dir[0] == '\0') return NULL;

    AppData *app = calloc(1, sizeof(*app));
    if (!app) return NULL;

    app->dataset_dir = strdup(dataset_dir);
    if (!app->dataset_dir) { free(app); return NULL; }

    char *airports_file     = path_join(dataset_dir, "airports.csv");
    char *aircrafts_file    = path_join(dataset_dir, "aircrafts.csv");
    char *flights_file      = path_join(dataset_dir, "flights.csv");
    char *passengers_file   = path_join(dataset_dir, "passengers.csv");
    char *reservations_file = path_join(dataset_dir, "reservations.csv");

    if (!airports_file || !aircrafts_file || !flights_file || !passengers_file || !reservations_file) {
        fprintf(stderr, "Erro: memória insuficiente ao criar paths.\n");
        free(airports_file); free(aircrafts_file); free(flights_file);
        free(passengers_file); free(reservations_file);
        free(app->dataset_dir);
        free(app);
        return NULL;
    }

    app->airports     = parse_airports_file(airports_file);
    app->aircrafts    = parse_aircrafts_file(aircrafts_file);
    app->flights      = parse_flights_file(flights_file, app->aircrafts);
    app->passengers   = parse_passengers_file(passengers_file);
    app->reservations = parse_reservations_file(reservations_file, app->flights, app->passengers);

    airports_manager_compute_passenger_counts(app->airports, app->flights, app->reservations);

    app->q6_table = g_hash_table_new_full(g_str_hash, g_str_equal, free, (GDestroyNotify)g_hash_table_destroy);
    compute_q6(app->q6_table, app->reservations, app->flights, app->passengers);

    free(airports_file);
    free(aircrafts_file);
    free(flights_file);
    free(passengers_file);
    free(reservations_file);

    return app;
}

static void appdata_free(AppData *app) {
    if (!app) return;

    if (app->airports)     airports_manager_free(app->airports);
    if (app->aircrafts)    aircrafts_manager_free(app->aircrafts);
    if (app->flights)      flights_manager_free(app->flights);
    if (app->reservations) reservations_manager_free(app->reservations);
    if (app->passengers)   passengers_manager_free(app->passengers);

    if (app->q6_table) g_hash_table_destroy(app->q6_table);

    free(app->dataset_dir);
    free(app);
}

/* ---------- interactive execution ---------- */

static int run_single_query_line(AppData *app, const char *query_line) {
    if (!app || !query_line) return 0;
    if (!ensure_results_dir()) return 0;

    const char *tmp_input = OUTPUT_DIR "input_interativo_tmp.txt";
    FILE *fi = fopen(tmp_input, "w");
    if (!fi) {
        perror("fopen tmp input");
        return 0;
    }
    fprintf(fi, "%s\n", query_line);
    fclose(fi);

    parse_queries(tmp_input, app->airports, app->aircrafts, app->flights, app->q6_table);

    const char *out_path = OUTPUT_DIR "command1_output.txt";
    FILE *fo = fopen(out_path, "r");
    if (!fo) {
        perror("fopen command1_output");
        return 0;
    }

    printf("Output: ");
    int c;
    while ((c = fgetc(fo)) != EOF) putchar(c);
    if (ferror(fo)) perror("ler output");
    fclose(fo);

    remove(tmp_input);
    remove(out_path);

    return 1;
}

static void process_query(AppData *app, const char *query_input) {
    // Parse query number and optional 'S' flag
    char *input_copy = strdup(query_input);
    if (!input_copy) return;
    
    char *token = strtok(input_copy, " ");
    if (!token) {
        free(input_copy);
        return;
    }
    
    int query_num = 0;
    int format_flag = 0; // 0 for normal, 1 for 'S' format
    
    // Check if token ends with 'S'
    size_t len = strlen(token);
    if (len > 1 && token[len-1] == 'S') {
        format_flag = 1;
        token[len-1] = '\0'; // Remove the 'S'
    }
    
    query_num = atoi(token);
    free(input_copy);
    
    if (query_num < 1 || query_num > 6) {
        printf("Query inválida. Use queries de 1 a 6.\n");
        return;
    }
    
    // Build the query line based on query type
    char query_line[1024];
    char *args = NULL;
    
    switch (query_num) {
        case 1:
            args = read_line_prompt("Código do aeroporto: ");
            if (!args) return;
            snprintf(query_line, sizeof(query_line), "%d%s %s", 
                    query_num, format_flag ? "S" : "", args);
            break;
            
        case 2:
            args = read_line_prompt("Número e fabricante (ex: 10 Boeing): ");
            if (!args) return;
            snprintf(query_line, sizeof(query_line), "%d%s %s", 
                    query_num, format_flag ? "S" : "", args);
            break;
            
        case 3:
            args = read_line_prompt("Datas (YYYY-MM-DD YYYY-MM-DD): ");
            if (!args) return;
            snprintf(query_line, sizeof(query_line), "%d%s %s", 
                    query_num, format_flag ? "S" : "", args);
            break;
            
        case 4:
            args = read_line_prompt("Datas (YYYY-MM-DD YYYY-MM-DD) ou enter para todas: ");
            if (!args) return;
            if (strlen(args) == 0) {
                snprintf(query_line, sizeof(query_line), "%d%s", 
                        query_num, format_flag ? "S" : "");
            } else {
                snprintf(query_line, sizeof(query_line), "%d%s %s", 
                        query_num, format_flag ? "S" : "", args);
            }
            break;
            
        case 5:
            args = read_line_prompt("Número: ");
            if (!args) return;
            snprintf(query_line, sizeof(query_line), "%d%s %s", 
                    query_num, format_flag ? "S" : "", args);
            break;
            
        case 6:
            args = read_line_prompt("País: ");
            if (!args) return;
            snprintf(query_line, sizeof(query_line), "%d%s %s", 
                    query_num, format_flag ? "S" : "", args);
            break;
            
        default:
            printf("Query não implementada.\n");
            return;
    }
    
    run_single_query_line(app, query_line);
    free(args);
}

int main(void) {
    AppData *app = NULL;

    char *dir = read_line_prompt("Introduza o caminho dos ficheiros de dados: ");
    if (!dir) {
        printf("\nEOF recebido. A sair.\n");
        return 0;
    }
    
    if (dir[0] == '\0') {
        printf("Caminho vazio.\n");
        free(dir);
        return 1;
    }

    app = appdata_load(dir);
    if (!app) {
        printf("Falha a carregar dataset.\n");
        free(dir);
        return 1;
    }
    
    printf("Dataset carregado...\n");
    free(dir);

    // Main query loop
    while (1) {
        char *query = read_line_prompt("Que query deseja executar? ");
        if (!query) break;
        
        if (query[0] == '\0' || strcmp(query, "0") == 0) {
            free(query);
            break;
        }
        
        process_query(app, query);
        free(query);
    }

    appdata_free(app);
    return 0;
}