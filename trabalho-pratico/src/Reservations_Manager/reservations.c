#include "reservations.h"
#include <stdlib.h>
#include <string.h>

struct Reservation {
    char *id;
    char *passenger_id;
    char *flights_list; // "[AA123;BB456]" ou "[AA123]"
    double total_price;
    char *date;         // "YYYY/MM/DD"
};

static char *dupstr(const char *s){ if(!s) return NULL; size_t n=strlen(s)+1; char *r=malloc(n); if(r) memcpy(r,s,n); return r; }

Reservation *reservation_new(const char *id, const char *passenger_id,
                             const char *flights_list, double total_price,
                             const char *date){
    if(!id) return NULL;
    if(total_price < 0.0) return NULL;
    Reservation *r = calloc(1,sizeof(*r));
    if(!r) return NULL;
    r->id = dupstr(id);
    r->passenger_id = dupstr(passenger_id);
    r->flights_list = dupstr(flights_list);
    r->total_price = total_price;
    r->date = dupstr(date);
    return r;
}

void reservation_free(Reservation *r){
    if(!r) return;
    free(r->id); free(r->passenger_id); free(r->flights_list); free(r->date);
    free(r);
}

const char *reservation_get_id(const Reservation *r){ return r? r->id: NULL; }
const char *reservation_get_passenger_id(const Reservation *r){ return r? r->passenger_id: NULL; }
const char *reservation_get_flights_list(const Reservation *r){ return r? r->flights_list: NULL; }
double       reservation_get_total_price(const Reservation *r){ return r? r->total_price: 0.0; }
const char *reservation_get_date(const Reservation *r){ return r? r->date: NULL; }

bool reservation_set_passenger_id(Reservation *r, const char *pid){ if(!r) return false; char *d=dupstr(pid); if(!d&&pid) return false; free(r->passenger_id); r->passenger_id=d; return true; }
bool reservation_set_flights_list(Reservation *r, const char *list){ if(!r) return false; char *d=dupstr(list); if(!d&&list) return false; free(r->flights_list); r->flights_list=d; return true; }
bool reservation_set_total_price(Reservation *r, double price){ if(!r) return false; if(price<0.0) return false; r->total_price=price; return true; }
bool reservation_set_date(Reservation *r, const char *date){ if(!r) return false; char *d=dupstr(date); if(!d&&date) return false; free(r->date); r->date=d; return true; }
