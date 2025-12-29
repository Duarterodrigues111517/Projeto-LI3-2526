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
        fputs(prompt, stdout);
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
    // cria "resultados/" se não existir
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

    // Reutiliza exatamente o mesmo fluxo do teu main.c
    app->airports     = parse_airports_file(airports_file);
    app->aircrafts    = parse_aircrafts_file(aircrafts_file);
    app->flights      = parse_flights_file(flights_file, app->aircrafts);
    app->passengers   = parse_passengers_file(passengers_file);
    app->reservations = parse_reservations_file(reservations_file, app->flights, app->passengers);

    // pré-cálculos
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

    // segue o padrão do teu main.c
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

static void print_menu(void) {
    puts("\n=== Programa Interativo (Fase 2) ===");
    puts("1) Executar query (escrever uma linha no formato do input.txt)");
    puts("2) Recarregar dataset");
    puts("0) Sair");
}

static void print_query_help(void) {
    puts("\nFormato da linha (igual ao input.txt):");
    puts("  <QID>[S] <args>");
    puts("Exemplos:");
    puts("  1 ABC");
    puts("  1S ABC");
    puts("  2 10 Boeing");
    puts("  3 2025-01-01 2025-12-31");
    puts("  5 20");
    puts("  6 PT");
    puts("Nota: o 'S' (ex: 1S, 2S, ...) ativa o formato alternativo.");
}

static int run_single_query_line(AppData *app, const char *query_line) {
    if (!app || !query_line) return 0;
    if (!ensure_results_dir()) return 0;

    // 1) escrever temp input com 1 linha
    const char *tmp_input = OUTPUT_DIR "input_interativo_tmp.txt";
    FILE *fi = fopen(tmp_input, "w");
    if (!fi) {
        perror("fopen tmp input");
        return 0;
    }
    fprintf(fi, "%s\n", query_line);
    fclose(fi);

    // 2) executar parser de queries (vai gerar resultados/command1_output.txt)
    parse_queries(tmp_input, app->airports, app->aircrafts, app->flights, app->q6_table);

    // 3) ler e imprimir o output
    const char *out_path = OUTPUT_DIR "command1_output.txt";
    FILE *fo = fopen(out_path, "r");
    if (!fo) {
        perror("fopen command1_output");
        return 0;
    }

    puts("\n--- OUTPUT ---");
    int c;
    while ((c = fgetc(fo)) != EOF) putchar(c);
    if (ferror(fo)) perror("ler output");
    fclose(fo);
    puts("--- FIM ---");

    // 4) limpar ficheiros temporários (opcional)
    remove(tmp_input);
    remove(out_path);

    return 1;
}

int main(void) {
    AppData *app = NULL;

    puts("Programa Interativo (Fase 2)");
    puts("Introduz o caminho para a pasta do dataset (onde estão airports.csv, flights.csv, ...).");
    puts("Exemplo: datasets/D1");

    while (!app) {
        char *dir = read_line_prompt("Dataset path: ");
        if (!dir) {
            puts("\nEOF recebido. A sair.");
            return 0;
        }
        if (dir[0] == '\0') {
            free(dir);
            puts("Caminho vazio. Tenta novamente.");
            continue;
        }

        app = appdata_load(dir);
        if (!app) {
            puts("Falha a carregar dataset. Confirma o caminho e tenta novamente.");
        } else {
            puts("Dataset carregado com sucesso.");
        }
        free(dir);
    }

    for (;;) {
        print_menu();
        char *opt = read_line_prompt("Opção: ");
        if (!opt) break;

        if (strcmp(opt, "0") == 0) {
            free(opt);
            break;
        } else if (strcmp(opt, "1") == 0) {
            free(opt);
            print_query_help();
            char *line = read_line_prompt("Query line: ");
            if (!line) break;

            if (line[0] == '\0') {
                puts("Linha vazia -> ignorado.");
                free(line);
                continue;
            }

            (void)run_single_query_line(app, line);
            free(line);
        } else if (strcmp(opt, "2") == 0) {
            free(opt);
            char *dir = read_line_prompt("Novo dataset path: ");
            if (!dir) break;

            if (dir[0] == '\0') {
                puts("Caminho vazio -> não recarreguei.");
                free(dir);
                continue;
            }

            AppData *new_app = appdata_load(dir);
            if (!new_app) {
                puts("Falha a carregar novo dataset. Mantive o anterior.");
            } else {
                appdata_free(app);
                app = new_app;
                puts("Dataset recarregado com sucesso.");
            }
            free(dir);
        } else {
            puts("Opção inválida.");
            free(opt);
        }
    }

    appdata_free(app);
    puts("Até já!");
    return 0;
}
