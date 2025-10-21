#ifndef RESERVATIONS_ENTITY_H
#define RESERVATIONS_ENTITY_H

#include <stdbool.h>

typedef struct Reservation Reservation;

// flights_list: string no formato "[ID1;ID2]" ou "[ID1]" conforme enunciado
Reservation *reservation_new(int *reservation_id, const char *flight_id,
                             int *document_number, const char *seat,
                             const char *price, bool *extra_luggage,
                             bool *priority_boarding, const char *qr_code);
void reservation_free(Reservation *r);

int        *reservation_get_reservation_id(const Reservation *r);
const char *reservation_get_passenger_id(const Reservation *r);


bool reservation_set_reservation_id(Reservation *r, const char *rid);
bool reservation_set_passenger_id(Reservation *r, const char *pid);






#endif
