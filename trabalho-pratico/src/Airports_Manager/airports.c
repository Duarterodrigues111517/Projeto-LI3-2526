#include "Airports_Manager/airports.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct Airport {
    char   *code;     
    char   *name;
    char   *city;
    char   *country;
    char   *icao;    
    char   *type;     
    double latitude;
    double longitude;
    int arrival_count;
    int departure_count;

};

static bool is_iata(const char *s){ return s && strlen(s)==3 && isupper((unsigned char)s[0]) && isupper((unsigned char)s[1]) && isupper((unsigned char)s[2]); }

Airport *airport_new(const char *code, const char *name, const char *city,
                     const char *country, const char *icao, const char *type,
                     double latitude, double longitude, int arrival_count, int departure_count){
    if(!is_iata(code)) return NULL;
    if(latitude < -90.0 || latitude > 90.0) return NULL;
    if(longitude < -180.0 || longitude > 180.0) return NULL;
    Airport *a = calloc(1,sizeof(*a));
    if(!a) return NULL;
    a->code = strdup(code);
    a->name = strdup(name);
    a->city = strdup(city);
    a->country = strdup(country);
    a->icao = strdup(icao);
    a->type = strdup(type);
    a->latitude = latitude;
    a->longitude = longitude;
    a->arrival_count = arrival_count;
    a->departure_count = departure_count;
    return a;
}

void airport_free(Airport *a){
    if(!a) return;
    free(a->code); free(a->name); free(a->city); free(a->country); free(a->icao); free(a->type);
    free(a);
}

const char *airport_get_code(const Airport *a){ return a? a->code: NULL; }
const char *airport_get_name(const Airport *a){ return a? a->name: NULL; }
const char *airport_get_city(const Airport *a){ return a? a->city: NULL; }
const char *airport_get_country(const Airport *a){ return a? a->country: NULL; }
const char *airport_get_icao(const Airport *a){ return a? a->icao: NULL; }
const char *airport_get_type(const Airport *a){ return a? a->type: NULL; }
double airport_get_latitude(const Airport *a){ return a? a->latitude: 0.0; }
double airport_get_longitude(const Airport *a){ return a? a->longitude: 0.0; }
int airport_get_arrival_count(const Airport *a){ return a? a->arrival_count: 0; }
int airport_get_departure_count(const Airport *a){ return a? a->departure_count: 0; }

bool airport_set_code(Airport *a, const char *code){ if(!a) return false; char *d=strdup(code); if(!d && code) return false; free(a->code); a->code=d; return true; }
bool airport_set_name(Airport *a, const char *name){ if(!a) return false; char *d=strdup(name); if(!d && name) return false; free(a->name); a->name=d; return true; }
bool airport_set_city(Airport *a, const char *city){ if(!a) return false; char *d=strdup(city); if(!d && city) return false; free(a->city); a->city=d; return true; }
bool airport_set_country(Airport *a, const char *country){ if(!a) return false; char *d=strdup(country); if(!d && country) return false; free(a->country); a->country=d; return true; }
bool airport_set_icao(Airport *a, const char *icao){ if(!a) return false; char *d=strdup(icao); if(!d && icao) return false; free(a->icao); a->icao=d; return true; }
bool airport_set_type(Airport *a, const char *type){ if(!a) return false; char *d=strdup(type); if(!d && type) return false; free(a->type); a->type=d; return true; }
bool airport_set_latitude(Airport *a, double lat){ if(!a) return false; if(lat<-90.0||lat>90.0) return false; a->latitude = lat; return true; }
bool airport_set_longitude(Airport *a, double lon){ if(!a) return false; if(lon<-180.0||lon>180.0) return false; a->longitude = lon; return true; }
void airport_inc_arrivals(Airport *a, int n){ if(!a) return; a->arrival_count += n; }
void airport_inc_departures(Airport *a, int n){ if(!a) return; a->departure_count += n; }