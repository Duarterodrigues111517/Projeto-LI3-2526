#include "Queries/query1.h"
#include <stdio.h>
#include <string.h>

void querie1(const char *args, AirportsManager_t *am, const char *output_path) {
    if (!args || !am || !output_path) return;

    // Extrair o código IATA 
    char code[16] = {0};
    sscanf(args, "%15s", code);

    Airport *a = airports_manager_get(am, code);

    FILE *f = fopen(output_path, "w");
    if (!f) { perror("querie1: fopen"); return; }

    if (a) {
        fprintf(f, "%s,%s,%s,%s,%s\n",
                airport_get_code(a),
                airport_get_name(a),
                airport_get_city(a),
                airport_get_country(a),
                airport_get_type(a));
    } else {
        // Código não encontrado
        fputc('\n', f);
    }

    fclose(f);
}
