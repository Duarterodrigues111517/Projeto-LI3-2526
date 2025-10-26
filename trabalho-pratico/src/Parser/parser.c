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

    if (getline(&line, &bufsize, file) != -1) {
        free_garray_parsed_elements(array);
        *lineCopy = strdup(line);
        line[strcspn(line, "\n")] = '\0';

        char *aux = line;
        char *token;

        while ((token = strsep(&aux, ",")) != NULL) {
            // remove \r at end
            size_t tlen = strlen(token);
            if (tlen > 0 && token[tlen - 1] == '\r')
                token[--tlen] = '\0';

            // strip any leading/trailing quotes (simple cleanup)
            while (*token == '"') token++;
            tlen = strlen(token);
            while (tlen > 0 && token[tlen - 1] == '"') token[--tlen] = '\0';

            // unescape double quotes inside ("" → ")
            char *clean = malloc(strlen(token) + 1);
            char *src = token, *dst = clean;
            while (*src) {
                if (src[0] == '"' && src[1] == '"') {
                    *dst++ = '"';
                    src += 2;
                } else {
                    *dst++ = *src++;
                }
            }
            *dst = '\0';

            g_array_append_val(array, clean);
        }

        free(line);
        return 1;
    }

    free(line);
    return 0;
}


void free_garray_parsed(GArray *array) {
    for (guint i = 0; i < array->len; i++) {
        g_free(g_array_index(array, char *, i));
    }
    g_array_free(array, TRUE);
}
