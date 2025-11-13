#include "Reservations_Manager/reservations.h"
#include <stdlib.h>
#include <string.h>

struct Reservation {
    char *reservation_id;
    char *flight_ids[2];   // até 2 voos
    int   flights_count;   // 1 ou 2
    int  document_number;
    char *seat;
    double price;
    bool extra_luggage;
    bool priority_boarding;
    char *qr_code;     
};


Reservation *reservation_new(const char *reservation_id,
                             const char *flight_id1,
                             const char *flight_id2,   // pode ser NULL
                             int document_number,
                             const char *seat,
                             double price,
                             bool extra_luggage,
                             bool priority_boarding,
                             const char *qr_code)
{
    if (!reservation_id) return NULL;
    if (price < 0.0) return NULL;

    Reservation *r = calloc(1, sizeof(*r));
    if (!r) return NULL;

    r->reservation_id = strdup(reservation_id);
    r->document_number = document_number;
    r->seat  = strdup(seat);
    r->price = price;
    r->extra_luggage      = extra_luggage;
    r->priority_boarding  = priority_boarding;
    r->qr_code            = strdup(qr_code);

    r->flights_count = 0;
    r->flight_ids[0] = NULL;
    r->flight_ids[1] = NULL;

    if (flight_id1) {
        r->flight_ids[0] = strdup(flight_id1);
        r->flights_count = 1;
    }

    if (flight_id2) {
        r->flight_ids[1] = strdup(flight_id2);
        r->flights_count = 2;
    }

    return r;
}

void reservation_free(Reservation *r){
    if (!r) return;

    free(r->reservation_id);

    for (int i = 0; i < r->flights_count; i++) {
        free(r->flight_ids[i]);
    }

    free(r->seat);
    free(r->qr_code);
    free(r);
}

const char *reservation_get_reservation_id(const Reservation *r){ return r? r->reservation_id: NULL; }
const char *reservation_get_flight_id(const Reservation *r){
    return (r && r->flights_count > 0) ? r->flight_ids[0] : NULL;
}
int reservation_get_flights_count(const Reservation *r){
    return r ? r->flights_count : 0;
}
const char *reservation_get_flight_id_at(const Reservation *r, int idx){
    if (!r) return NULL;
    if (idx < 0 || idx >= r->flights_count) return NULL;
    return r->flight_ids[idx];
}
int        reservation_get_document_number(const Reservation *r){ return r? r->document_number: 0; }
const char *reservation_get_seat(const Reservation *r){ return r? r->seat: NULL; }
double     reservation_get_price(const Reservation *r){ return r? r->price: 0.0; }
bool       reservation_get_extra_luggage(const Reservation *r){ return r? r->extra_luggage: false; }
bool       reservation_get_priority_boarding(const Reservation *r){ return r? r->priority_boarding: false; }
const char *reservation_get_qr_code(const Reservation *r){ return r? r->qr_code: NULL; }


bool reservation_set_reservation_id(Reservation *r, const char *reservation_id){
    if(!r) return false;
    free(r->reservation_id);
    r->reservation_id = strdup(reservation_id);
    return true;
}
bool reservation_set_flights(Reservation *r,
                             const char *flight_id1,
                             const char *flight_id2){
    if (!r) return false;

    for (int i = 0; i < r->flights_count; i++)
        free(r->flight_ids[i]);

    r->flights_count = 0;

    if (flight_id1) {
        r->flight_ids[0] = strdup(flight_id1);
        if (!r->flight_ids[0]) return false;
        r->flights_count = 1;
    }

    if (flight_id2) {
        r->flight_ids[1] = strdup(flight_id2);
        if (!r->flight_ids[1]) return false;
        r->flights_count = 2;
    }

    return true;
}


bool reservation_set_document_number(Reservation *r, int document_number){
    if(!r) return false;
    r->document_number = document_number;
    return true;
}
bool reservation_set_seat(Reservation *r, const char *seat){
    if(!r) return false;
    char *d=strdup(seat);
    if(!d && seat) return false;
    free(r->seat); r->seat=d;
    return true;
}
bool reservation_set_price(Reservation *r, double price){
    if(!r) return false;
    r->price = price;
    return true;
}
bool reservation_set_extra_luggage(Reservation *r, bool extra_luggage){
    if(!r) return false;
    r->extra_luggage = extra_luggage;
    return true;
}
bool reservation_set_priority_boarding(Reservation *r, bool priority_boarding){
    if(!r) return false;
    r->priority_boarding = priority_boarding;
    return true;
}
bool reservation_set_qr_code(Reservation *r, const char *qr_code){
    if(!r) return false;
    char *d=strdup(qr_code);
    if(!d && qr_code) return false;
    free(r->qr_code); r->qr_code=d;
    return true;
}
