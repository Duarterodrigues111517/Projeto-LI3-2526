#ifndef RESERVATIONS_PARSER_H
#define RESERVATIONS_PARSER_H

#include <glib.h>
#include <stdio.h>
#include "Reservations_Manager/reservations_manager.h"
#include "Flights_Manager/flights_manager.h"
#include "Passengers_Manager/passengers_manager.h"
#include "Parser/parser.h"


int parse_reservation_row(GArray *f, const char *raw, const char *header,
                          ReservationsManager_t *mgr, FlightsManager_t *fl_mgr, PassengersManager_t *p_mgr, FILE **errors_fp);


ReservationsManager_t *parse_reservations_file(const char *path, 
                                               FlightsManager_t *fl_mgr, 
                                               PassengersManager_t *p_mgr);


#endif

