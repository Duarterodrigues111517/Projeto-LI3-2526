#include "reservations.h"
#include <stdlib.h>
#include <string.h>

struct Reservation {
    int  *reservation_id;
    char *flight_id;
    int  *document_number;
    char *seat;
    int  *price;   
    bool *extra_luggage;
    bool *priority_boarding;
    char *qr_code;     
};

Reservation *reservation_new(int *reservation_id, const char *flight_id,
                             int *document_number, const char *seat,
                             int *price, bool *extra_luggage,
                             bool *priority_boarding, const char *qr_code){
    if(!id) return NULL;
    if(total_price < 0.0) return NULL;
    Reservation *r = calloc(1,sizeof(*r));
    if(!r) return NULL;
    r->reservation_id = reservation_id;
    r->flight_id = dupstr(flight_id);
    r->document_number = document_number;
    r->seat = dupstr(seat);
    r->price= price;
    r->extra_luggage = extra_luggage;
    r->priority_boarding = priority_boarding;
    r->qr_code = dupstr(qr_code);
    return r;
}

void reservation_free(Reservation *r){
    if(!r) return;
    free(r->reservation_id); free(r->flight_id); free(r->document_number); free(r->seat); free(r->price); free(r->extra_luggage); free(r->priority_boarding); free(r->qr_code);
    free(r);
}

int        *reservation_get_reservation_id(const Reservation *r){ return r? r->reservation_id: NULL; }
const char *reservation_get_flight_id(const Reservation *r){ return r? r->flight_id: NULL; }
int        *reservation_get_document_number(const Reservation *r){ return r? r->document_number: NULL; }
const char *reservation_get_seat(const Reservation *r){ return r? r->seat: NULL; }
int        *reservation_get_price(const Reservation *r){ return r? r->price: NULL; }
bool       *reservation_get_extra_luggage(const Reservation *r){ return r? r->extra_luggage: NULL; }
bool       *reservation_get_priority_boarding(const Reservation *r){ return r? r->priority_boarding: NULL; }
const char *reservation_get_qr_code(const Reservation *r){ return r? r->qr_code: NULL; }


bool reservation_set_reservation_id(Reservation *r, int *reservation_id){
    if(!r) return false;
    r->reservation_id = reservation_id;
    return true;
}
bool reservation_set_flight_id(Reservation *r, const char *flight_id){
    if(!r) return false;
    char *d=dupstr(flight_id);
    if(!d && flight_id) return false;
    free(r->flight_id); r->flight_id=d;
    return true;
}
bool reservation_set_document_number(Reservation *r, int *document_number){
    if(!r) return false;
    r->document_number = document_number;
    return true;
}
bool reservation_set_seat(Reservation *r, const char *seat){
    if(!r) return false;
    char *d=dupstr(seat);
    if(!d && seat) return false;
    free(r->seat); r->seat=d;
    return true;
}
bool reservation_set_price(Reservation *r, int *price){
    if(!r) return false;
    r->price = price;
    return true;
}
bool reservation_set_extra_luggage(Reservation *r, bool *extra_luggage){
    if(!r) return false;
    r->extra_luggage = extra_luggage;
    return true;
}
bool reservation_set_priority_boarding(Reservation *r, bool *priority_boarding){
    if(!r) return false;
    r->priority_boarding = priority_boarding;
    return true;
}
bool reservation_set_qr_code(Reservation *r, const char *qr_code){
    if(!r) return false;
    char *d=dupstr(qr_code);
    if(!d && qr_code) return false;
    free(r->qr_code); r->qr_code=d;
    return true;
}
