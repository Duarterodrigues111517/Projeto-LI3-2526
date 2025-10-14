#ifndef RESERVATIONS_H
#define RESERVATIONS_H

typedef struct reservations *Reservations;

Reservations reservations_create(void);
void         reservations_destroy(Reservations r);

int          reservations_load_csv(Reservations r, const char *csv_path, const char *errors_dir);

#endif
