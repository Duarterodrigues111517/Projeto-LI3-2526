#include <stdlib.h>
#include "managers/reservations.h"

struct reservations { size_t dummy; };

Reservations reservations_create(void) {
    Reservations r = malloc(sizeof(*r));
    if (r) r->dummy = 0;
    return r;
}

void reservations_destroy(Reservations r) {
    if (!r) return;
    free(r);
}

int reservations_load_csv(Reservations r, const char *csv_path, const char *errors_dir) {
    (void)r; (void)csv_path; (void)errors_dir;
    return 0;
}
