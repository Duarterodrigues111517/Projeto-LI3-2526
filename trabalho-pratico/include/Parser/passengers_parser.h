#ifndef PASSENGERS_PARSER_H
#define PASSENGERS_PARSER_H

#include <glib.h>
#include <stdio.h>
#include "Passengers_Manager/passengers_manager.h"
#include "Parser/parser.h"


int parse_passenger_row(GArray *f, const char *raw, const char *header,
                        PassengersManager_t *mgr, FILE **errors_fp);

PassengersManager_t *parse_passengers_file(const char *path);

#endif

