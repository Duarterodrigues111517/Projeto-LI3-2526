#ifndef RESERVATIONS_ENTITY_H
#define RESERVATIONS_ENTITY_H

#include <stdbool.h>

typedef struct Reservation Reservation;

// Construção / destruição
Reservation *reservation_new(const char *reservation_id,
                             const char *flight_id1,
                             const char *flight_id2,   
                             int document_number,
                             const char *seat,
                             double price);
void reservation_free(Reservation *r);
// Getters
const char *reservation_get_reservation_id(const Reservation *r);
const char *reservation_get_flight_id(const Reservation *r);
int reservation_get_flights_count(const Reservation *r);    
const char *reservation_get_flight_id_at(const Reservation *r, int index);
int        reservation_get_document_number(const Reservation *r);
const char *reservation_get_seat(const Reservation *r);
double     reservation_get_price(const Reservation *r);


// Setters 
bool reservation_set_reservation_id(Reservation *r, const char *reservation_id);
bool reservation_set_flights(Reservation *r, const char *flight_id1, const char *flight_id2);
bool reservation_set_document_number(Reservation *r, int document_number);
bool reservation_set_seat(Reservation *r, const char *seat);
bool reservation_set_price(Reservation *r, double price);




#endif
