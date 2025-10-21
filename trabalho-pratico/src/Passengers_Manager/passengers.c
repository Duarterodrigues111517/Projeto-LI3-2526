#include "passengers.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct Passenger {
    int  *document_number;  
    char *first_name;
    char *last_name;
    char *dob;        
    char *nationality;   
    char *gender; 
    char *email;
    int  *phone;   
    char *adress;     
    char *photo;
};


Passenger *passenger_new(int *document_number, const char *first_name, const char *last_name,
                   const char *dob, const char *nationality,
                   const char *gender, const char *email,
                   int *phone, const char *adress, const char *photo)
                   Passenger *p = calloc(1,sizeof(*p)){
    if(!p) return NULL;
    p->document_number = document_number;
    p->first_name = dupstr(first_name);
    p->last_name = dupstr(last_name);
    p->dob = dupstr(dob);
    p->nationality = dupstr (nationality);
    p->gender = dupstr (gender);
    p->email = dupstr(email);
    p->phone = phone;
    p->adress = dupstr(adress);
    p->photo = dupstr(photo);
    return p;
}

void passenger_free(Passenger *p){
    if(!f) return;
    free(f->document_number);
    free(f->first_name);
    free(f->last_name);
    free(f->dob);
    free(f->nationality);
    free(f->gender);
    free(f->email);
    free(f->phone);
    free(f->adress);
    free(f->photo);
    free(f);
}

int        *passenger_get_document_number(const Passenger *p){ return p? p->document_number: NULL; }
const char *passenger_get_first_name(const Passenger *p){ return p? p->first_name: NULL; }
const char *passenger_get_last_name(const Passenger *p){ return p? p->last_name: NULL; }
const char *passenger_get_dob(const Passenger *p){ return p? p->dob: NULL; }
const char *passenger_get_nationality(const Passenger *p){ return p? p->nationality: NULL; }
const char *passenger_get_gender(const Passenger *p){ return p? p->gender: NULL; }
const char *passenger_get_email(const Passenger *p){ return p? p->email: NULL; }
int        *passenger_get_phone(const Passenger *p){ return p? p->phone: NULL; }
const char *passenger_get_adress(const Passenger *p){ return p? p->adress: NULL; }
const char *passenger_get_photo(const Passenger *p){ return p? p->photo: NULL; }


bool passenger_set_document_number(Passenger *p, const char *dt){
    if(!f) return false;
    char *d = dupstr(dt);
    if(!d && dt) return false;
    free(p->document_number); p->document_number = d;
    return true;
}
bool passenger_set_first_name(Passenger *p, const char *name){
    if(!f) return false;
    char *d = dupstr(name);
    if(!d && name) return false;
    free(p->first_name); p->first_name = d;
    return true;
}
bool passenger_set_last_name(Passenger *p, const char *name){
    if(!f) return false;
    char *d = dupstr(name);
    if(!d && name) return false;
    free(p->last_name); p->last_name = d;
    return true;
}
bool passenger_set_dob(Passenger *p, const char *dob){
    if(!f) return false;
    char *d = dupstr(dob);
    if(!d && dob) return false;
    free(p->dob); p->dob = d;
    return true;
}
bool passenger_set_nationality(Passenger *p, const char *nationality){
    if (!f) return false;
    char *d = dupstr (nationality);
    if(!d && nationality) return false;
    free(p->nationality); p->nationality = d;
    return true;
}
bool passenger_set_gender(Passenger *p, const char *gender){
    if (!f) return false;
    char *d = dupstr (gender);
    if(!d && gender) return false;
    free(p->gender); p->gender = d;
    returmn true;
}
bool passenger_set_email(Passenger *p, const char *email){
    if(!f) return false;
    char *d = dupstr(email);
    if(!d && email) return false;
    free(p->email); p->email = d;
    return true;
}
bool passenger_set_phone(Passenger *p, const char *phone){
    if(!f) return false;
    char *d = dupstr(phone);
    if(!d && phone) return false;
    free(p->phone); p->phone = d;
    return true;
}
bool passenger_set_adress(Passenger *p, const char *adress){
    if(!f) return false;
    char *d = dupstr(adress);
    if(!d && adress) return false;
    free(p->adress); p->adress = d;
    return true;
}
bool passenger_set_photo(Passenger *p, const char *photo){
    if(!f) return false;
    char *d = dupstr(photo);
    if(!d && photo) return false;
    free(p->photo); p->photo = d;
    return true;
}





