#include "Parser/passengers_parser.h"
#include "utils/validators.h"
#include <string.h>
#include <stdio.h>

#define PASSENGERS_ERR_PATH "resultados/passengers_errors.csv"

// cria o ficheiro de erros apenas quando necessário
static void ensure_errors_file(FILE **fp, const char *path, const char *header) {
    if (*fp) return;
    *fp = fopen(path, "w");
    if (*fp) fputs(header, *fp); 
}


int parse_passenger_row(GArray *f, const char *raw, const char *header,
                        PassengersManager_t *mgr, FILE **errors_fp)
{
    if (f->len != 10) {
        ensure_errors_file(errors_fp, PASSENGERS_ERR_PATH, header);
        if (*errors_fp) fputs(raw, *errors_fp);
        return 0;
    }

    const char *document_number = g_array_index(f, char*, 0);
    const char *first_name      = g_array_index(f, char*, 1);
    const char *last_name       = g_array_index(f, char*, 2);
    const char *dob             = g_array_index(f, char*, 3);
    const char *nationality     = g_array_index(f, char*, 4);
    const char *gender          = g_array_index(f, char*, 5);
    const char *email           = g_array_index(f, char*, 6);

    // validações sintáticas básicas
    int ok = 1;
    ok &= is_valid_document_number(document_number); 
    ok &= is_nonempty_str(first_name);
    ok &= is_nonempty_str(last_name);
    ok &= is_valid_date(dob);                        
    ok &= is_nonempty_str(nationality);
    ok &= is_valid_gender(gender);                   
    ok &= is_valid_email(email);

    if (!ok) {
        ensure_errors_file(errors_fp, PASSENGERS_ERR_PATH, header);
        if (*errors_fp) fputs(raw, *errors_fp);
        return 0;
    }

  
    Passenger *p = passenger_new(document_number,
                                 first_name,
                                 last_name,
                                 dob,
                                 nationality,
                                 gender,
                                 email);

    passengers_manager_add(mgr, p);
    return 1;
}


PassengersManager_t *parse_passengers_file(const char *path) {
    PassengersManager_t *mgr = passengers_manager_new();
    FILE *fp = fopen(path, "r");
    if (!fp) { perror("passenger.csv"); return mgr; }

    GArray *fields = g_array_new(FALSE, FALSE, sizeof(char *));
    char *raw = NULL;
    char *header = NULL;
    FILE *errors_fp = NULL;

    if (!process_line(fp, fields, &raw)) goto cleanup;
    header = g_strdup(raw);
    free(raw); raw = NULL;

    while (process_line(fp, fields, &raw)) {
        parse_passenger_row(fields, raw, header, mgr, &errors_fp);
        free(raw); raw = NULL;
    }

cleanup:
    if (errors_fp) fclose(errors_fp);
    if (header) g_free(header);
    if (raw) free(raw);
    if (fields) free_garray_parsed(fields);
    fclose(fp);
    return mgr;
}
