#include "Aircrafts_Manager/aircrafts.h"
#include <stdlib.h>
#include <string.h>

struct Aircraft {
    char *id;
    char *model;
    char *manufacturer;
    int  range;
    int  year; 
    int  capacity;
};

Aircraft *aircraft_new(const char *id, const char *model, const char *manufacturer,
                       int capacity, int range, int year){
    if(!id) return NULL;
    if(capacity < 0) return NULL;
    Aircraft *a = calloc(1,sizeof(*a));
    if(!a) return NULL;
    a->id = strdup(id);
    a->model = strdup(model);
    a->manufacturer = strdup(manufacturer);
    a->capacity = capacity;
    a->range = range;
    a->year = year;
    return a;
}
void aircraft_free(Aircraft *a){
    if(!a) return;
    free(a->id); free(a->model); free(a->manufacturer); free(a->range);
    free(a);
}

const char *aircraft_get_id(const Aircraft *a){ return a? a->id: NULL; }
const char *aircraft_get_model(const Aircraft *a){ return a? a->model: NULL; }
const char *aircraft_get_manufacturer(const Aircraft *a){ return a? a->manufacturer: NULL; }
int         aircraft_get_capacity(const Aircraft *a){ return a? a->capacity: 0; }
int        aircraft_get_range(const Aircraft *a){ return a? a->range: 0; }
int        aircraft_get_year(const Aircraft *a){ return a? a->year: 0; }

bool aircraft_set_id(Aircraft *a, const char *id){ if(!a) return false; char *d=strdup(id); if(!d&&id) return false; free(a->id); a->id=d; return true; }
bool aircraft_set_model(Aircraft *a, const char *model){ if(!a) return false; char *d=strdup(model); if(!d&&model) return false; free(a->model); a->model=d; return true; }
bool aircraft_set_manufacturer(Aircraft *a, const char *manufacturer){ if(!a) return false; char *d=strdup(manufacturer); if(!d&&manufacturer) return false; free(a->manufacturer); a->manufacturer=d; return true; }
bool aircraft_set_capacity(Aircraft *a, int capacity){ if(!a) return false; if(capacity<0) return false; a->capacity=capacity; return true; }
bool aircraft_set_range(Aircraft *a, int range){ if(!a) return false; a->range=range; return true; }
bool aircraft_set_year(Aircraft *a, int year){ if(!a) return false; a->year=year; return true; }