#include "flights.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct Flight {
    char *id;            // AA1234 (2 letras + 3–4 dígitos)
    char *airline;
    char *aircraft_id;
    char *origin;        // IATA
    char *destination;   // IATA
    char *schedule_departure; // "YYYY/MM/DD HH:MM:SS"
    char *schedule_arrival;
    char *actual_departure;   // ou "N/A"
    char *actual_arrival;     // ou "N/A"
    FlightStatus status;
};

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

Flight *flight_new(const char *id, const char *airline, const char *aircraft_id,
                   const char *origin, const char *destination,
                   const char *schedule_departure, const char *schedule_arrival,
                   const char *actual_departure, const char *actual_arrival,
                   FlightStatus status){
    if(!is_flight_id(id)) return NULL;
    if(!is_iata(origin) || !is_iata(destination) || strcmp(origin,destination)==0) return NULL;
    Flight *f = calloc(1,sizeof(*f));
    if(!f) return NULL;
    f->id = dupstr(id);
    f->airline = dupstr(airline);
    f->aircraft_id = dupstr(aircraft_id);
    f->origin = dupstr(origin);
    f->destination = dupstr(destination);
    f->schedule_departure = dupstr(schedule_departure);
    f->schedule_arrival = dupstr(schedule_arrival);
    f->actual_departure = dupstr(actual_departure);
    f->actual_arrival = dupstr(actual_arrival);
    f->status = status;
    return f;
}

void flight_free(Flight *f){
    if(!f) return;
    free(f->id); free(f->airline); free(f->aircraft_id);
    free(f->origin); free(f->destination);
    free(f->schedule_departure); free(f->schedule_arrival);
    free(f->actual_departure); free(f->actual_arrival);
    free(f);
}

const char *flight_get_id(const Flight *f){ return f? f->id: NULL; }
const char *flight_get_airline(const Flight *f){ return f? f->airline: NULL; }
const char *flight_get_aircraft_id(const Flight *f){ return f? f->aircraft_id: NULL; }
const char *flight_get_origin(const Flight *f){ return f? f->origin: NULL; }
const char *flight_get_destination(const Flight *f){ return f? f->destination: NULL; }
const char *flight_get_schedule_departure(const Flight *f){ return f? f->schedule_departure: NULL; }
const char *flight_get_schedule_arrival(const Flight *f){ return f? f->schedule_arrival: NULL; }
const char *flight_get_actual_departure(const Flight *f){ return f? f->actual_departure: NULL; }
const char *flight_get_actual_arrival(const Flight *f){ return f? f->actual_arrival: NULL; }
FlightStatus flight_get_status(const Flight *f){ return f? f->status: FLIGHT_UNKNOWN; }

bool flight_set_actual_departure(Flight *f, const char *dt){
    if(!f) return false;
    char *d = dupstr(dt);
    if(!d && dt) return false;
    free(f->actual_departure); f->actual_departure = d;
    return true;
}
bool flight_set_actual_arrival(Flight *f, const char *dt){
    if(!f) return false;
    char *d = dupstr(dt);
    if(!d && dt) return false;
    free(f->actual_arrival); f->actual_arrival = d;
    return true;
}
bool flight_set_status(Flight *f, FlightStatus st){
    if(!f) return false;
    f->status = st; return true;
}
