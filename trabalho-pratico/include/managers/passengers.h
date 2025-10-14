#ifndef PASSENGERS_H
#define PASSENGERS_H

typedef struct passengers *Passengers;

Passengers passengers_create(void);
void       passengers_destroy(Passengers p);

int        passengers_load_csv(Passengers p, const char *csv_path, const char *errors_dir);

#endif
