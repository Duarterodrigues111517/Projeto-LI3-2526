#ifndef AIRCRAFTS_H
#define AIRCRAFTS_H

typedef struct aircrafts *Aircrafts;

Aircrafts aircrafts_create(void);
void      aircrafts_destroy(Aircrafts a);

int       aircrafts_load_csv(Aircrafts a, const char *csv_path, const char *errors_dir);

#endif
