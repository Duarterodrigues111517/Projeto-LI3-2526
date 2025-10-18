#ifndef RESERVATIONS_ENTITY_H
#define RESERVATIONS_ENTITY_H

#include <stdbool.h>

typedef struct Reservation Reservation;

// flights_list: string no formato "[ID1;ID2]" ou "[ID1]" conforme enunciado
Reservation *reservation_new(const char *id, const char *passenger_id,
                             const char *flights_list, double total_price,
                             const char *date);
void reservation_free(Reservation *r);

const char *reservation_get_id(const Reservation *r);
const char *reservation_get_passenger_id(const Reservation *r);
const char *reservation_get_flights_list(const Reservation *r);
double       reservation_get_total_price(const Reservation *r);
const char *reservation_get_date(const Reservation *r);

bool reservation_set_passenger_id(Reservation *r, const char *pid);
bool reservation_set_flights_list(Reservation *r, const char *list);
bool reservation_set_total_price(Reservation *r, double price);
bool reservation_set_date(Reservation *r, const char *date);

#endif
