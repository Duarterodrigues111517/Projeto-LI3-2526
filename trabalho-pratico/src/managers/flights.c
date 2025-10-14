#include <stdlib.h>
#include "managers/flights.h"

struct flights { size_t dummy; };

Flights flights_create(void) {
    Flights f = malloc(sizeof(*f));
    if (f) f->dummy = 0;
    return f;
}

void flights_destroy(Flights f) {
    if (!f) return;
    free(f);
}

int flights_load_csv(Flights f, const char *csv_path, const char *errors_dir) {
    (void)f; (void)csv_path; (void)errors_dir;
    return 0;
}
