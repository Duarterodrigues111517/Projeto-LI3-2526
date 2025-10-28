#include "Passengers_Manager/passengers.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct Passenger {
    int  document_number;  
    char *first_name;
    char *last_name;
    char *dob;        
    char *nationality;   
    char *gender; 
    char *email;
    char *phone;   
    char *adress;     
    char *photo;
};


Passenger *passenger_new (int document_number, const char *first_name,
                             const char *last_name, const char *dob,
                             const char *nationality, const char *gender,
                             const char *email, const char *phone,
                             const char *adress, const char *photo){
    if(document_number <= 0) return NULL;
    Passenger *p = calloc(1,sizeof(*p));
    if(!p) return NULL;
    p->document_number = document_number;
    p->first_name = strdup(first_name);
    p->last_name = strdup(last_name);
    p->dob = strdup(dob);
    p->nationality = strdup(nationality);
    p->gender = strdup(gender);
    p->email = strdup(email);
    p->phone = strdup(phone);
    p->adress = strdup(adress);
    p->photo = strdup(photo);
    return p;
}

void passenger_free(Passenger *p){
    if(!p) return;
    free(p->first_name);
    free(p->last_name);
    free(p->dob);
    free(p->nationality);
    free(p->gender);
    free(p->email);
    free(p->phone);
    free(p->adress);
    free(p->photo);
    free(p);
}

int         passenger_get_document_number(const Passenger *p){ return p? p->document_number: -1; }
const char *passenger_get_first_name(const Passenger *p){ return p? p->first_name: NULL; }
const char *passenger_get_last_name(const Passenger *p){ return p? p->last_name: NULL; }
const char *passenger_get_dob(const Passenger *p){ return p? p->dob: NULL; }
const char *passenger_get_nationality(const Passenger *p){ return p? p->nationality: NULL; }
const char *passenger_get_gender(const Passenger *p){ return p? p->gender: NULL; }
const char *passenger_get_email(const Passenger *p){ return p? p->email: NULL; }
const char *passenger_get_phone(const Passenger *p){ return p? p->phone: NULL; }
const char *passenger_get_adress(const Passenger *p){ return p? p->adress: NULL; }
const char *passenger_get_photo(const Passenger *p){ return p? p->photo: NULL; }


bool passenger_set_document_number(Passenger *p, int dt){
    if(!p) return false;
    p->document_number = dt;
    return true;
}
bool passenger_set_first_name(Passenger *p, const char *name){
    if(!p) return false;
    char *d = strdup(name);
    if(!d && name) return false;
    free(p->first_name); p->first_name = d;
    return true;
}
bool passenger_set_last_name(Passenger *p, const char *name){
    if(!p) return false;
    char *d = strdup(name);
    if(!d && name) return false;
    free(p->last_name); p->last_name = d;
    return true;
}
bool passenger_set_dob(Passenger *p, const char *dob){
    if(!p) return false;
    char *d = strdup(dob);
    if(!d && dob) return false;
    free(p->dob); p->dob = d;
    return true;
}
bool passenger_set_nationality(Passenger *p, const char *nationality){
    if (!p) return false;
    char *d = strdup(nationality);
    if(!d && nationality) return false;
    free(p->nationality); p->nationality = d;
    return true;
}
bool passenger_set_gender(Passenger *p, const char *gender){
    if (!p) return false;
    char *d = strdup(gender);
    if(!d && gender) return false;
    free(p->gender); p->gender = d;
    return true;
}
bool passenger_set_email(Passenger *p, const char *email){
    if(!p) return false;
    char *d = strdup(email);
    if(!d && email) return false;
    free(p->email); p->email = d;
    return true;
}
bool passenger_set_phone(Passenger *p, const char *phone){
    if(!p) return false;
    char *d = strdup(phone);
    if(!d && phone) return false;
    free(p->phone); p->phone = d;
    return true;
}
bool passenger_set_adress(Passenger *p, const char *adress){
    if(!p) return false;
    char *d = strdup(adress);
    if(!d && adress) return false;
    free(p->adress); p->adress = d;
    return true;
}
bool passenger_set_photo(Passenger *p, const char *photo){
    if(!p) return false;
    char *d = strdup(photo);
    if(!d && photo) return false;
    free(p->photo); p->photo = d;
    return true;
}





