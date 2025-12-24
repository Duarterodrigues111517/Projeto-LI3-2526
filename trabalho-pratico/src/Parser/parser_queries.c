#include "Parser/parser_queries.h"

#ifndef OUTPUT_DIR
#define OUTPUT_DIR "resultados/"
#endif

void parse_queries(const char *path_input,
                   AirportsManager_t *am,
                   AircraftsManager_t *aircrafts,
                   FlightsManager_t *flights) {
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
        while (n > 0 && (line[n - 1] == '\n' || line[n - 1] == '\r'))
            line[--n] = '\0';

        // Ignorar linhas vazias
        char *ptr = line;
        while (*ptr == ' ' || *ptr == '\t') ptr++;
        if (*ptr == '\0') continue;

        // Construir nome do ficheiro de output
        char output_path[256];
        snprintf(output_path, sizeof(output_path),
                 OUTPUT_DIR "command%lu_output.txt", line_no);

        // Extrair número da query
        char *args = NULL;
        int qid = (int)strtol(ptr, &args, 10);

        // NOVO: separador por omissão e formato S
        char sep = ';';

        // Se a seguir ao número vier 'S', muda separador e avança 1 char
        if (*args == 'S') {
            sep = '=';
            args++; // salta o 'S'
        }

        // Saltar espaços antes dos argumentos
        while (*args == ' ' || *args == '\t') args++;

        switch (qid) {
            case 1:
                querie1(args,sep, am, output_path);
                break;

            case 2: {
                char *endptr = NULL;
                long n_long = strtol(args, &endptr, 10);

                if (endptr == args || n_long <= 0) {
                    // não foi possível ler N -> ficheiro vazio
                    FILE *f = fopen(output_path, "w");
                    if (f) {
                        fputc('\n', f);
                        fclose(f);
                    }
                    break;
                }

                int N = (int)n_long;

                // saltar espaços depois de N
                while (*endptr == ' ' || *endptr == '\t') endptr++;

                // se ainda houver texto, é o manufacturer; senão, não há filtro
                const char *manufacturer = (*endptr != '\0') ? endptr : NULL;

                querie2(N, manufacturer, sep, aircrafts, flights, output_path);
                break;
            }

            case 3: {
                char *start_date = strtok(args, " \t");
                char *end_date   = strtok(NULL, " \t");

                if (!start_date || !end_date) {
                    // argumentos insuficientes -> ficheiro vazio
                    FILE *f = fopen(output_path, "w");
                    if (f) {
                        fputc('\n', f);
                        fclose(f);
                    }
                    break;
                }

                querie3(start_date, end_date, sep, am, flights, output_path);
                break;
            }

            default: {
                // query desconhecida -> ficheiro vazio
                FILE *f = fopen(output_path, "w");
                if (f) {
                    fputc('\n', f);
                    fclose(f);
                }
                break;
            }
        }
    }

    free(line);
    fclose(fp);
}
