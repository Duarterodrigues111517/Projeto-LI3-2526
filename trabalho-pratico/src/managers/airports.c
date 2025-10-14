#include <stdlib.h>
#include <stdio.h>
#include "managers/airports.h"

struct airports {
    /* por enquanto vazio */
    size_t dummy;
};

Airports airports_create(void) {
    Airports a = malloc(sizeof(*a));
    if (a) a->dummy = 0;
    return a;
}

void airports_destroy(Airports a) {
    if (!a) return;
    free(a);
}

int airports_load_csv(Airports a, const char *csv_path, const char *errors_dir) {
    (void)a; (void)csv_path; (void)errors_dir;
    /* TODO: implementar parse/validação */
    return 0;
}
