#include "Parser/parser_queries.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef OUTPUT_DIR
#define OUTPUT_DIR "resultados/"
#endif

void parse_queries(const char *path_input, AirportsManager_t *am, AircraftsManager_t *aircrafts, FlightsManager_t *flights) {
    FILE *fp = fopen(path_input, "r");
    if (!fp) {
        perror("Erro ao abrir input.txt");
        return;
    }

    char *line = NULL;
    size_t cap = 0;
    ssize_t n;
    unsigned long line_no = 0;

    while ((n = getline(&line, &cap, fp)) != -1) {
        line_no++;

        // Remover \n / \r do fim
        while (n > 0 && (line[n - 1] == '\n' || line[n - 1] == '\r')) line[--n] = '\0';

        // Ignorar linhas vazias
        char *ptr = line;
        while (*ptr == ' ' || *ptr == '\t') ptr++;
        if (*ptr == '\0') continue;

        // Construir nome do ficheiro de output
        char output_path[256];
        snprintf(output_path, sizeof(output_path), OUTPUT_DIR "command%lu_output.txt", line_no);

        // Extrair número da query
        char *args = NULL;
        int qid = (int)strtol(ptr, &args, 10);

        // Saltar espaços antes dos argumentos
        while (*args == ' ' || *args == '\t') args++;

        switch (qid) {
            case 1:
                querie1(args, am, output_path);
                break;
        case 2: {
                    char *saveptr = NULL;

                    // primeira chamada: usa 'args'
                    char *n_str = strtok_r(args, " ", &saveptr);
                    if (!n_str) {
                        FILE *f = fopen(output_path, "w");
                        if (f) { fputc('\n', f); fclose(f); }
                        break;
                    }

                    int N = atoi(n_str);

                    // resto da linha (pode ser o manufacturer ou nada)
                    char *manufacturer = strtok_r(NULL, "", &saveptr);
                    if (manufacturer) {
                        while (*manufacturer == ' ') manufacturer++;
                    }

                    querie2(N,
                            manufacturer && *manufacturer ? manufacturer : NULL,
                            aircrafts,
                            flights,
                            output_path);
                    break;
                }

        }
    }

    free(line);
    fclose(fp);
}
