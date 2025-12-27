#include "Flights_Manager/flights_manager.h"
#include <stdio.h> 
#include <stdlib.h>
#include <string.h>

/* ---- helper: datetime "YYYY-MM-DD HH:MM" -> minutos absolutos ---- */
static int is_leap(int y) {
    return (y % 400 == 0) || (y % 4 == 0 && y % 100 != 0);
}

static int days_before_month(int y, int m) {
    static const int cumdays_norm[] =
        {0,31,59,90,120,151,181,212,243,273,304,334}; /* before month m (1-based) */
    int d = cumdays_norm[m-1];
    if (m > 2 && is_leap(y)) d += 1;
    return d;
}

static long long days_from_civil(int y, int m, int d) {
    /* days since 1970-01-01, algorithm-based */
    y -= (m <= 2);
    const int era = (y >= 0 ? y : y - 399) / 400;
    const unsigned yoe = (unsigned)(y - era * 400);
    const unsigned doy = (unsigned)(days_before_month(y + (m <= 2), m) + (d - 1));
    const unsigned doe = yoe * 365 + yoe / 4 - yoe / 100 + doy;
    return (long long)era * 146097LL + (long long)doe - 719468LL; /* 719468 = days to 1970-01-01 */
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

/* Destroy */
void destroy_flight(void *f) {
    flight_free((Flight *)f);
}

static void destroy_q5_stat(void *p) {
    free(p);
}

struct FlightsManager {
    GHashTable *flights_table;

    /* Q5: key airline (strdup) -> Q5AirlineStat* */
    GHashTable *q5_airline_stats;
};

/* Create */
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

/* Free memory */
void flights_manager_free(FlightsManager_t *fm) {
    if (!fm) return;
    g_hash_table_destroy(fm->flights_table);
    g_hash_table_destroy(fm->q5_airline_stats);
    free(fm);
}

/* Q5 getter */
GHashTable *flights_manager_get_q5_table(const FlightsManager_t *fm) {
    return fm ? fm->q5_airline_stats : NULL;
}

/* Q5 updater */
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

/* Add flight */
void flights_manager_add(FlightsManager_t *fm, Flight *f) {
    if (!fm || !f) return;

    /* atualiza Q5 em O(1) */
    flights_manager_update_q5(fm, f);

    g_hash_table_insert(fm->flights_table, g_strdup(flight_get_id(f)), f);
}

/* Get flight */
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
