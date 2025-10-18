#ifndef PASSENGERS_ENTITY_H
#define PASSENGERS_ENTITY_H

#include <stdbool.h>

typedef struct Passenger Passenger;

Passenger *passenger_new(const char *id, const char *name, const char *gender,
                         const char *birth_date, const char *country,
                         const char *document, const char *email);
void passenger_free(Passenger *p);

const char *passenger_get_id(const Passenger *p);
const char *passenger_get_name(const Passenger *p);
const char *passenger_get_gender(const Passenger *p);
const char *passenger_get_birth_date(const Passenger *p);
const char *passenger_get_country(const Passenger *p);
const char *passenger_get_document(const Passenger *p);
const char *passenger_get_email(const Passenger *p);

bool passenger_set_name(Passenger *p, const char *name);
bool passenger_set_gender(Passenger *p, const char *gender);
bool passenger_set_birth_date(Passenger *p, const char *date);
bool passenger_set_country(Passenger *p, const char *country);
bool passenger_set_document(Passenger *p, const char *doc);
bool passenger_set_email(Passenger *p, const char *email);

#endif
