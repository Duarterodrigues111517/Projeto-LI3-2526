#include <stdlib.h>
#include "managers/aircrafts.h"

struct aircrafts { size_t dummy; };

Aircrafts aircrafts_create(void) {
    Aircrafts a = malloc(sizeof(*a));
    if (a) a->dummy = 0;
    return a;
}

void aircrafts_destroy(Aircrafts a) {
    if (!a) return;
    free(a);
}

int aircrafts_load_csv(Aircrafts a, const char *csv_path, const char *errors_dir) {
    (void)a; (void)csv_path; (void)errors_dir;
    return 0;
}
