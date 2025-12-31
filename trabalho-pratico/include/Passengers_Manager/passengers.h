#ifndef PASSENGERS_ENTITY_H
#define PASSENGERS_ENTITY_H

#include <stdbool.h>

typedef struct Passenger Passenger;

// Construção / destruição
Passenger *passenger_new(const char *document_number,
                         const char *first_name,
                         const char *last_name,
                         const char *dob,
                         const char *nationality,
                         const char *gender,
                         const char *email);
void passenger_free(Passenger *p);

// Getters
const char *passenger_get_document_number(const Passenger *p);
const char *passenger_get_first_name(const Passenger *p);
const char *passenger_get_last_name(const Passenger *p);
const char *passenger_get_dob(const Passenger *p);
const char *passenger_get_nationality(const Passenger *p);
const char *passenger_get_gender(const Passenger *p);
const char *passenger_get_email(const Passenger *p);

// Setters
bool passenger_set_document_number(Passenger *p, const char *document_number);
bool passenger_set_first_name(Passenger *p, const char *name);
bool passenger_set_last_name(Passenger *p, const char *name);
bool passenger_set_dob(Passenger *p, const char *dob);
bool passenger_set_nationality(Passenger *p, const char *nationality);
bool passenger_set_gender(Passenger *p, const char *gender);
bool passenger_set_email(Passenger *p, const char *email);

#endif

