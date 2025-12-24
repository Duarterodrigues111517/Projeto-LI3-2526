#ifndef RESERVATION_MANAGER_H
#define RSERVATION_MANAGER_H


#include "reservations.h"
#include <glib.h>

typedef struct ReservationsManager ReservationsManager_t;

void destroy_reservation(void *r);
ReservationsManager_t *reservations_manager_new(void);
void reservations_manager_free(ReservationsManager_t *rm);
void reservations_manager_add(ReservationsManager_t *rm, Reservation *r);
Reservation *reservations_manager_get(const ReservationsManager_t *rm, const char *id);
void reservations_manager_foreach(ReservationsManager_t *rm,
                                  void (*fn)(Reservation *r, void *user_data),
                                  void *user_data);


#endif