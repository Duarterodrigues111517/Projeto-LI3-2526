#include "flights.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct flight {
    char *id;
    char *departure;
    char *actual_departure;
    char *arrival;
    char *actual_arrival;
    char *gate;
    char *status;
    char *origin;
    char *destination;
    char *aircraft;
    char *airline;
    char *tracking_url;
} Flight;

static char *dupstr(const char *s){ if(!s) return NULL; size_t n=strlen(s)+1; char *r=malloc(n); if(r) memcpy(r,s,n); return r; }
static bool is_iata(const char *s){ return s && strlen(s)==3 && isupper((unsigned char)s[0]) && isupper((unsigned char)s[1]) && isupper((unsigned char)s[2]); }
static bool is_flight_id(const char *s){
    if(!s) return false;
    size_t n=strlen(s);
    if(n<5||n>7) return false;
    if(!isupper((unsigned char)s[0])||!isupper((unsigned char)s[1])) return false;
    for(size_t i=2;i<n;i++) if(!isdigit((unsigned char)s[i])) return false;
    return true;
}

FlightStatus flight_status_from_string(const char *s){
    if(!s) return FLIGHT_UNKNOWN;
    if(strcasecmp(s,"scheduled")==0) return FLIGHT_SCHEDULED;
    if(strcasecmp(s,"cancelled")==0) return FLIGHT_CANCELLED;
    if(strcasecmp(s,"delayed")==0)   return FLIGHT_DELAYED;
    if(strcasecmp(s,"done")==0)      return FLIGHT_DONE;
    return FLIGHT_UNKNOWN;
}

Flight *flight_new(const char *id,
    const char *departure,
    const char *actual_departure,
    const char *arrival,
    const char *actual_arrival,
    const char *gate,
    const char *status,
    const char *origin,
    const char *destination,
    const char *aircraft,
    const char *airline,
    const char *tracking_url){
    if(!is_flight_id(id)) return NULL;
    if(!is_iata(origin)) return NULL;
    if(!is_iata(destination)) return NULL;
    Flight *f = calloc(1,sizeof(*f));
    if(!f) return NULL;
    f->id = dupstr(id);
    f->departure = dupstr(departure);
    f->actual_departure = dupstr(actual_departure);
    f->arrival = dupstr(arrival);
    f->actual_arrival = dupstr(actual_arrival);
    f->gate = dupstr(gate);
    f->status = dupstr(status);
    f->origin = dupstr(origin);
    f->destination = dupstr(destination);
    f->aircraft = dupstr(aircraft);
    f->airline = dupstr(airline);
    f->tracking_url = dupstr(tracking_url);

    return f;
}

void flight_free(Flight *f){
    if(!f) return;
    free(f->id);
    free(f->departure);
    free(f->actual_departure);
    free(f->arrival);
    free(f->actual_arrival);
    free(f->gate);
    free(f->status);
    free(f->origin);
    free(f->destination);
    free(f->aircraft);
    free(f->airline);
    free(f->tracking_url);
    free(f);
}
