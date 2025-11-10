#ifndef AIRCRAFTS_PARSER_H
#define AIRCRAFTS_PARSER_H

#include "utils/validators.h"
#include "Aircrafts_Manager/aircrafts_manager.h"
#include "Parser/parser.h"
#include <string.h>
#include <errno.h>
#include <stdlib.h>

int parse_aircraft_row(GArray *f, const char *raw, const char *header,
                       AircraftsManager_t *mgr, FILE **errors_fp);



AircraftsManager_t *parse_aircrafts_file(const char *path);

#endif
