#ifndef FLIGHTS_H
#define FLIGHTS_H

typedef struct flights *Flights;

Flights flights_create(void);
void    flights_destroy(Flights f);

int     flights_load_csv(Flights f, const char *csv_path, const char *errors_dir);

#endif
