#include <stdio.h>
#include <stdlib.h>
#include <glib.h>

#include "Parser/parser.h"

static void print_fields(GArray *arr, long line_no) {
    printf("Linha %ld -> %u campos\n", line_no, arr->len);
    for (guint i = 0; i < arr->len; i++) {
        char *field = g_array_index(arr, char*, i);
        printf("  [%u] %s\n", i, field ? field : "(null)");
    }
}

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Uso: %s <ficheiro.csv>\n", argv[0]);
        return 1;
    }

    const char *csv = argv[1];
    FILE *fp = fopen(csv, "r");
    if (!fp) { perror("fopen"); return 2; }

    // Array de char* (NÃO zero-terminated).
    GArray *fields = g_array_new(FALSE, FALSE, sizeof(char*));
    char *lineCopy = NULL;

    long line_no = 0;
    // Se o CSV tiver header e não o quiseres imprimir, lê 1x e ignora:
    // process_line(fp, fields, &lineCopy); free(lineCopy); free_garray_parsed_elements(fields);

    while (process_line(fp, fields, &lineCopy)) {
        line_no++;
        // tira o '\n' da cópia só para debug mais limpo
        lineCopy[strcspn(lineCopy, "\n")] = '\0';

        // Mostra os campos parseados
        print_fields(fields, line_no);

        // limpa para a próxima
        free(lineCopy);
        lineCopy = NULL;
        free_garray_parsed_elements(fields);
    }

    free(lineCopy); // seguro, pode ser NULL
    free_garray_parsed(fields);
    fclose(fp);
    return 0;
}
