#ifndef AIRPORTS_PARSER_H
#define AIRPORTS_PARSER_H

#include "utils/validators.h"
#include "Airports_Manager/airports_manager.h"
#include <string.h>
#include <errno.h>
#include <stdlib.h>

int parse_airport_row(GArray *fields, const char *raw_line, const char *header,
                      AirportsManager_t *manager, FILE **errors_fp);




#endif