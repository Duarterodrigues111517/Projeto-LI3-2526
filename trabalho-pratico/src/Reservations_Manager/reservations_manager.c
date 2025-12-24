#include "Reservations_Manager/reservations_manager.h"


struct ReservationsManager {
    GHashTable *reservations_table;
};

// Destroy
void destroy_reservation(void *r) {
    reservation_free((Reservation *)r);
}

//Create 

ReservationsManager_t *reservations_manager_new(void) {
    ReservationsManager_t *rm = malloc(sizeof(ReservationsManager_t));
    if (!rm) return NULL;

    rm->reservations_table = g_hash_table_new_full(
        g_str_hash,          
        g_str_equal,          
        free,                 
        destroy_reservation    
    );

    if (!rm->reservations_table) {
        free(rm);
        return NULL;
    }

    return rm;
}

// Free memory
void reservations_manager_free(ReservationsManager_t *rm) {
    if (!rm) return;
    g_hash_table_destroy(rm->reservations_table);
    free(rm);
}

//Add reservation
void reservations_manager_add(ReservationsManager_t *rm, Reservation *r) {
    if (!rm || !r) return;

    g_hash_table_insert(rm->reservations_table,
                    g_strdup(reservation_get_reservation_id(r)), r);

}

// Get reservation
Reservation *reservations_manager_get(const ReservationsManager_t *rm, const char *id) {
    if (!rm || !id) return NULL;
    return (Reservation *)g_hash_table_lookup(rm->reservations_table, id);
}

void reservations_manager_foreach(ReservationsManager_t *rm,
                                  void (*fn)(Reservation *r, void *user_data),
                                  void *user_data)
{
    if (!rm || !fn) return;

    GList *values = g_hash_table_get_values(rm->reservations_table);
    for (GList *l = values; l != NULL; l = l->next) {
        Reservation *r = (Reservation *)l->data;
        if (r) fn(r, user_data);
    }
    g_list_free(values);
}

