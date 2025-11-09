#ifndef PASSENGERS_PARSER_H
#define PASSENGERS_PARSER_H

#include <glib.h>
#include <stdio.h>
#include "Passengers_Manager/passengers_manager.h"


int parse_passenger_row(GArray *f, const char *raw, const char *header,
                        PassengersManager_t *mgr, FILE **errors_fp);

#endif
