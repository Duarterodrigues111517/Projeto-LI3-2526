#include "aircrafts.h"
#include <stdlib.h>
#include <string.h>

struct Aircraft {
    char *id;
    char *model;
    char *manufacturer;
    int capacity;
    char *first_flight_date; // "YYYY/MM/DD"
};

static char *dupstr(const char *s){ if(!s) return NULL; size_t n=strlen(s)+1; char *r=malloc(n); if(r) memcpy(r,s,n); return r; }

Aircraft *aircraft_new(const char *id, const char *model, const char *manufacturer,
                       int capacity, const char *first_flight_date){
    if(!id) return NULL;
    if(capacity < 0) return NULL;
    Aircraft *a = calloc(1,sizeof(*a));
    if(!a) return NULL;
    a->id = dupstr(id);
    a->model = dupstr(model);
    a->manufacturer = dupstr(manufacturer);
    a->capacity = capacity;
    a->first_flight_date = dupstr(first_flight_date);
    return a;
}
void aircraft_free(Aircraft *a){
    if(!a) return;
    free(a->id); free(a->model); free(a->manufacturer); free(a->first_flight_date);
    free(a);
}

const char *aircraft_get_id(const Aircraft *a){ return a? a->id: NULL; }
const char *aircraft_get_model(const Aircraft *a){ return a? a->model: NULL; }
const char *aircraft_get_manufacturer(const Aircraft *a){ return a? a->manufacturer: NULL; }
int         aircraft_get_capacity(const Aircraft *a){ return a? a->capacity: 0; }
const char *aircraft_get_first_flight_date(const Aircraft *a){ return a? a->first_flight_date: NULL; }

bool aircraft_set_model(Aircraft *a, const char *model){ if(!a) return false; char *d=dupstr(model); if(!d&&model) return false; free(a->model); a->model=d; return true; }
bool aircraft_set_manufacturer(Aircraft *a, const char *manufacturer){ if(!a) return false; char *d=dupstr(manufacturer); if(!d&&manufacturer) return false; free(a->manufacturer); a->manufacturer=d; return true; }
bool aircraft_set_capacity(Aircraft *a, int capacity){ if(!a) return false; if(capacity<0) return false; a->capacity=capacity; return true; }
bool aircraft_set_first_flight_date(Aircraft *a, const char *date){ if(!a) return false; char *d=dupstr(date); if(!d&&date) return false; free(a->first_flight_date); a->first_flight_date=d; return true; }
