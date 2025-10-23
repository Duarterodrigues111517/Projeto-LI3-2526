#ifndef PASSENGERS_ENTITY_H
#define PASSENGERS_ENTITY_H

#include <stdbool.h>

typedef struct Passenger Passenger;

Passenger *passenger_new(int *document_number, const char *first_name, const char *last_name,
                         const char *dob, const char *nationality,
                         const char *gender, const char *email,
                         int *phone, const char *adress, const char *photo);
void passenger_free(Passenger *p);

int        *passenger_get_document_number(const Passenger *p);
const char *passenger_get_first_name(const Passenger *p);
const char *passenger_get_last_name(const Passenger *p);
const char *passenger_get_dob(const Passenger *p);
const char *passenger_get_nationality(const Passenger *p);
const char *passenger_get_gender(const Passenger *p);
const char *passenger_get_email(const Passenger *p);
int        *passenger_get_phone(const Passenger *p);
const char *passenger_get_adress(const Passenger *p);
const char *passenger_get_photo(const Passenger *p);

bool passenger_set_document_number(Passenger *p, int *document_number);
bool passenger_set_first_name(Passenger *p, const char *name);
bool passenger_set_last_name(Passenger *p, const char *name);
bool passenger_set_dob(Passenger *p, const char *dob);
bool passenger_set_nationality(Passenger *p, const char *nationality);
bool passenger_set_gender(Passenger *p, const char *gender);
bool passenger_set_email(Passenger *p, const char *email);
bool passenger_set_phone(Passenger *p, int *phone);
bool passenger_set_adress(Passenger *p, const char *adress);
bool passenger_set_photo(Passenger *p, const char *photo);

#endif
