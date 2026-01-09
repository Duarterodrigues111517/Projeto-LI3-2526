#include "Aircrafts_Manager/aircrafts.h"
#include <stdlib.h>
#include <string.h>

// estrutura interna da aeronave
struct Aircraft {
    char *id;
    char *manufacturer;
    char *model;
    int   year;
    int   capacity;
    int   range;
};

Aircraft *aircraft_new(const char *id,
                       const char *manufacturer,
                       const char *model,
                       int year,
                       int capacity,
                       int range)
{
    if (!id) return NULL;
    if (capacity < 0) return NULL;

    Aircraft *a = calloc(1, sizeof(*a));
    if (!a) return NULL;

    a->id = strdup(id);
    a->manufacturer = strdup(manufacturer);
    a->model = strdup(model);
    a->year = year;
    a->capacity = capacity;
    a->range = range;

    return a;
}

void aircraft_free(Aircraft *a){
    if (!a) return;
    free(a->id);
    free(a->manufacturer);
    free(a->model);
    free(a);
}

// getters
const char *aircraft_get_id(const Aircraft *a){ return a? a->id: NULL; }
const char *aircraft_get_model(const Aircraft *a){ return a? a->model: NULL; }
const char *aircraft_get_manufacturer(const Aircraft *a){ return a? a->manufacturer: NULL; }
int         aircraft_get_capacity(const Aircraft *a){ return a? a->capacity: 0; }
int        aircraft_get_range(const Aircraft *a){ return a? a->range: 0; }
int        aircraft_get_year(const Aircraft *a){ return a? a->year: 0; }

// setters
bool aircraft_set_id(Aircraft *a, const char *id){ 
    if(!a || !id) return false;
    if (strlen(id) == 0) return false;
    if (a->id) free(a->id);
    a->id = strdup(id);
    return true;
    }
bool aircraft_set_model(Aircraft *a, const char *model){ 
     if(!a || !model) return false;
     if (strlen(model) == 0) return false;  
     if (a->model) free(a->model);
     a->model = strdup(model); 
     return true; }
bool aircraft_set_manufacturer(Aircraft *a, const char *manufacturer){ 
    if(!a || !manufacturer) return false; 
    if(strlen(manufacturer) == 0) return false;
    char *d = strdup(manufacturer);
    if(!d) return false;
    if(a->manufacturer) free(a->manufacturer);
    a->manufacturer = d;
    return true;
}
bool aircraft_set_capacity(Aircraft *a, int capacity){ if(!a) return false; if(capacity<0) return false; a->capacity=capacity; return true; }
bool aircraft_set_range(Aircraft *a, int range){ if(!a) return false; a->range=range; return true; }
bool aircraft_set_year(Aircraft *a, int year){ if(!a) return false; a->year=year; return true; }