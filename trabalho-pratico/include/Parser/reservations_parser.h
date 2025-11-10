#ifndef RESERVATIONS_PARSER_H
#define RESERVATIONS_PARSER_H

#include <glib.h>
#include <stdio.h>
#include "Reservations_Manager/reservations_manager.h"
#include "Parser/parser.h"


int parse_reservation_row(GArray *f, const char *raw, const char *header,
                          ReservationsManager_t *mgr, FILE **errors_fp);


ReservationsManager_t *parse_reservations_file(const char *path);
#endif
