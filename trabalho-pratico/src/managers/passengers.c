#include <stdlib.h>
#include "managers/passengers.h"

struct passengers { size_t dummy; };

Passengers passengers_create(void) {
    Passengers p = malloc(sizeof(*p));
    if (p) p->dummy = 0;
    return p;
}

void passengers_destroy(Passengers p) {
    if (!p) return;
    free(p);
}

int passengers_load_csv(Passengers p, const char *csv_path, const char *errors_dir) {
    (void)p; (void)csv_path; (void)errors_dir;
    return 0;
}
