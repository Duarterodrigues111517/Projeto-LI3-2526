#ifndef RESERVATIONS_ENTITY_H
#define RESERVATIONS_ENTITY_H

#include <stdbool.h>

typedef struct Reservation Reservation;

// Construção / destruição
Reservation *reservation_new ( const char *reservation_id, const char *flight_id,
                             int document_number, const char *seat,
                             double price, bool *extra_luggage,
                             bool *priority_boarding, const char *qr_code);
void reservation_free(Reservation *r);
// Getters
const char *reservation_get_reservation_id(const Reservation *r);
const char *reservation_get_flight_id(const Reservation *r);
int        reservation_get_document_number(const Reservation *r);
const char *reservation_get_seat(const Reservation *r);
double     reservation_get_price(const Reservation *r);
bool       *reservation_get_extra_luggage(const Reservation *r);
bool       *reservation_get_priority_boarding(const Reservation *r);
const char *reservation_get_qr_code(const Reservation *r);
// Setters (retornam false se input inválido)
bool reservation_set_reservation_id(Reservation *r, const char *reservation_id);
bool reservation_set_flight_id(Reservation *r, const char *flight_id);
bool reservation_set_document_number(Reservation *r, int document_number);
bool reservation_set_seat(Reservation *r, const char *seat);
bool reservation_set_price(Reservation *r, double price);
bool reservation_set_extra_luggage(Reservation *r, bool *extra_luggage);
bool reservation_set_priority_boarding(Reservation *r, bool *priority_boarding);
bool reservation_set_qr_code(Reservation *r, const char *qr_code);



#endif
