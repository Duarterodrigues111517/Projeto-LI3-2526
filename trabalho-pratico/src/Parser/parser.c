#include "Parser/parser.h"

// Função para dar free aos elementos do GArray
void free_garray_parsed_elements(GArray *array) {
    for (guint i = 0; i < array->len; i++) {
        g_free(g_array_index(array, char *, i));
    }
    g_array_set_size(array, 0); 
}


 int process_line(FILE *file, GArray *array, char **lineCopy) {
    char *line = NULL;
    size_t bufsize = 0;
    ssize_t n = getline(&line, &bufsize, file);
    if (n == -1) { free(line); return 0; }

    *lineCopy = strdup(line);

    // remove \n e \r finais
    while (n > 0 && (line[n-1] == '\n' || line[n-1] == '\r')) line[--n] = '\0';

    // limpa o array de tokens anterior
    free_garray_parsed_elements(array);

    // parser de CSV com aspas 
    GString *field = g_string_new(NULL);
    int in_quotes = 0;
    for (ssize_t i = 0; i < n; i++) {
        char c = line[i];
        if (c == '"') {
            if (in_quotes && i + 1 < n && line[i+1] == '"') {
                g_string_append_c(field, '"');
                i++; 
            } else {
                in_quotes = !in_quotes; 
            }
        } else if (c == ',' && !in_quotes) {
            char *token = g_strdup(field->str);
            g_array_append_val(array, token);
            g_string_truncate(field, 0);
        } else {
            g_string_append_c(field, c);
        }
    }
    char *token = g_strdup(field->str);
    g_array_append_val(array, token);
    g_string_free(field, TRUE);

    free(line);
    return 1;
}


void free_garray_parsed(GArray *array) {
    for (guint i = 0; i < array->len; i++) {
        g_free(g_array_index(array, char *, i));
    }
    g_array_free(array, TRUE);
}
