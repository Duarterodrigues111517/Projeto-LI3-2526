#include "Passengers_Manager/passengers.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// estrutura interna dos passageiros
struct Passenger {
    char *document_number;  
    char *first_name;
    char *last_name;
    char *dob;        
    char *nationality;   
    char *gender; 
    char *email;
};

Passenger *passenger_new(const char *document_number,
                         const char *first_name,
                         const char *last_name,
                         const char *dob,
                         const char *nationality,
                         const char *gender) {
    if (!document_number || strlen(document_number) == 0) return NULL;

    Passenger *p = calloc(1, sizeof(*p));
    if (!p) return NULL;

    p->document_number = strdup(document_number);
    p->first_name = strdup(first_name);
    p->last_name = strdup(last_name);
    p->dob = strdup(dob);
    p->nationality = strdup(nationality);
    p->gender = strdup(gender);

    return p;
}

void passenger_free(Passenger *p) {
    if (!p) return;
    free(p->document_number);
    free(p->first_name);
    free(p->last_name);
    free(p->dob);
    free(p->nationality);
    free(p->gender);
    free(p);
}

// Getters
const char *passenger_get_document_number(const Passenger *p) { return p ? p->document_number : NULL; }
const char *passenger_get_first_name(const Passenger *p) { return p ? p->first_name : NULL; }
const char *passenger_get_last_name(const Passenger *p) { return p ? p->last_name : NULL; }
const char *passenger_get_dob(const Passenger *p) { return p ? p->dob : NULL; }
const char *passenger_get_nationality(const Passenger *p) { return p ? p->nationality : NULL; }
const char *passenger_get_gender(const Passenger *p) { return p ? p->gender : NULL; }


// Setters
bool passenger_set_document_number(Passenger *p, const char *document_number) {
    if (!p) return false;
    char *d = strdup(document_number);
    if (!d && document_number) return false;
    free(p->document_number);
    p->document_number = d;
    return true;
}

bool passenger_set_first_name(Passenger *p, const char *name) { if (!p) return false; char *d = strdup(name); if (!d && name) return false; free(p->first_name); p->first_name = d; return true; }
bool passenger_set_last_name(Passenger *p, const char *name) { if (!p) return false; char *d = strdup(name); if (!d && name) return false; free(p->last_name); p->last_name = d; return true; }
bool passenger_set_dob(Passenger *p, const char *dob) { if (!p) return false; char *d = strdup(dob); if (!d && dob) return false; free(p->dob); p->dob = d; return true; }
bool passenger_set_nationality(Passenger *p, const char *n) { if (!p) return false; char *d = strdup(n); if (!d && n) return false; free(p->nationality); p->nationality = d; return true; }
bool passenger_set_gender(Passenger *p, const char *g) { if (!p) return false; char *d = strdup(g); if (!d && g) return false; free(p->gender); p->gender = d; return true; }





