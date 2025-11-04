#ifndef VALIDATOR_H
#define VALIDATOR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>



// Dates / times (assume "now" = 2025/09/30 as per spec)
int is_valid_date(const char *yyyy_mm_dd);                 // "aaaa-mm-dd", ranges, <= today
int is_valid_datetime(const char *yyyy_mm_dd_hh_mm);       // "aaaa-mm-dd hh:mm", ranges, <= today
int is_valid_year(const char *yyyy);                        // "aaaa", <= current year

// Email: username [a-z0-9 and '.'] + '@' + lstring[a-z]+'.'+rstring[2..3][a-z]
int is_valid_email(const char *email);

// Airport type & codes
int is_valid_airport_type(const char *type);                // {small_airport,...}
int is_valid_iata3(const char *code);                       // exactly 3 chars [A-Z]

// Lat/Long
int is_valid_lat(const char *s);   // [-]dd.dddddddd (max 8 decimals) AND -90..90
int is_valid_lon(const char *s);   // [-]ddd.ddddddd (max 8 decimals) AND -180..180

// IDs
int is_valid_flight_id(const char *s);      // ccddddd
int is_valid_reservation_id(const char *s); // 'R' + 9 digits
int is_valid_document_number(const char *s);// 9 digits

// Passenger
int is_valid_gender(const char *s);         // {M,F,O}

// CSV "list" fields with [...] delimiters (no deep semantics here, Phase-1)
int is_valid_bracket_list(const char *s);   // starts '[' and ends ']'

#endif