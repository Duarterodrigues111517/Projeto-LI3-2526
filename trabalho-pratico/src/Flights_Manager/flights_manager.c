#include "Flights_Manager/flights_manager.h"
#include <stdio.h> 
#include <stdlib.h>
#include <string.h>


static int is_leap(int y) {
    return (y % 400 == 0) || (y % 4 == 0 && y % 100 != 0);
}

static int days_in_month(int y, int m) {
    static const int days[] = {0,31,28,31,30,31,30,31,31,30,31,30,31};
    if (m == 2 && is_leap(y)) return 29;
    return days[m];
}

static long long days_from_civil(int y, int m, int d) {
    long long total_days = 0;
    for (int year = 1970; year < y; year++) {
        total_days += is_leap(year) ? 366 : 365;
    }
    for (int month = 1; month < m; month++) {
        total_days += days_in_month(y, month);
    }
    
    total_days += d - 1;  
    
    return total_days;
}

static int parse_datetime_minutes(const char *s, long long *out_minutes) {
    if (!s || !out_minutes) return 0;
    int Y,M,D,h,mi;
    if (sscanf(s, "%d-%d-%d %d:%d", &Y, &M, &D, &h, &mi) != 5) return 0;
    if (M < 1 || M > 12) return 0;
    if (D < 1 || D > 31) return 0;
    if (h < 0 || h > 23) return 0;
    if (mi < 0 || mi > 59) return 0;

    long long days = days_from_civil(Y, M, D);
    *out_minutes = days * 1440LL + (long long)h * 60LL + (long long)mi;
    return 1;
}

void destroy_flight(void *f) {
    flight_free((Flight *)f);
}

static void destroy_q5_stat(void *p) {
    free(p);
}

struct FlightsManager {
    GHashTable *flights_table;

    GHashTable *q5_airline_stats;
};


FlightsManager_t *flights_manager_new(void) {
    FlightsManager_t *fm = malloc(sizeof(FlightsManager_t));
    if (!fm) return NULL;

    fm->flights_table = g_hash_table_new_full(
        g_str_hash,
        g_str_equal,
        free,
        destroy_flight
    );
    if (!fm->flights_table) {
        free(fm);
        return NULL;
    }

    fm->q5_airline_stats = g_hash_table_new_full(
        g_str_hash,
        g_str_equal,
        free,
        destroy_q5_stat
    );
    if (!fm->q5_airline_stats) {
        g_hash_table_destroy(fm->flights_table);
        free(fm);
        return NULL;
    }

    return fm;
}


void flights_manager_free(FlightsManager_t *fm) {
    if (!fm) return;
    g_hash_table_destroy(fm->flights_table);
    g_hash_table_destroy(fm->q5_airline_stats);
    free(fm);
}


GHashTable *flights_manager_get_q5_table(const FlightsManager_t *fm) {
    return fm ? fm->q5_airline_stats : NULL;
}


void flights_manager_update_q5(FlightsManager_t *fm, const Flight *f) {
    if (!fm || !f) return;

    const char *status = flight_get_status(f);
    if (!status || strcmp(status, "Delayed") != 0) return;

    const char *airline = flight_get_airline(f);
    if (!airline) airline = "";

    const char *dep  = flight_get_departure(f);
    const char *adep = flight_get_actual_departure(f);
    if (!dep || !adep) return;
    if (strcmp(adep, "N/A") == 0) return;

    long long dep_min = 0, adep_min = 0;
    if (!parse_datetime_minutes(dep, &dep_min)) return;
    if (!parse_datetime_minutes(adep, &adep_min)) return;

    long long delay = adep_min - dep_min;
    if (delay <= 0) return;

    Q5AirlineStat *st = g_hash_table_lookup(fm->q5_airline_stats, airline);
    if (!st) {
        st = calloc(1, sizeof(*st));
        if (!st) return;
        g_hash_table_insert(fm->q5_airline_stats, strdup(airline), st);
    }

    st->delayed_count += 1;
    st->total_delay_minutes += delay;
}


void flights_manager_add(FlightsManager_t *fm, Flight *f) {
    if (!fm || !f) return;

    
    flights_manager_update_q5(fm, f);

    g_hash_table_insert(fm->flights_table, g_strdup(flight_get_id(f)), f);
}


Flight *flights_manager_get(const FlightsManager_t *fm, const char *id) {
    if (!fm || !id) return NULL;
    return (Flight *)g_hash_table_lookup(fm->flights_table, id);
}

void flights_manager_foreach(FlightsManager_t *fm,
                             void (*fn)(Flight *f, void *user_data),
                             void *user_data)
{
    if (!fm || !fn) return;

    GList *values = g_hash_table_get_values(fm->flights_table);
    for (GList *l = values; l != NULL; l = l->next) {
        Flight *f = (Flight *)l->data;
        if (f) fn(f, user_data);
    }
    g_list_free(values);
}