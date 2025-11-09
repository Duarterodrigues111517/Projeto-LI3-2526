#include "Parser/passengers_parser.h"
#include "utils/validators.h"
#include <string.h>
#include <stdio.h>

#define PASSENGERS_ERR_PATH "resultados/passengers_errors.csv"

// cria o ficheiro de erros apenas quando necessário
static void ensure_errors_file(FILE **fp, const char *path, const char *header) {
    if (*fp) return;
    *fp = fopen(path, "w");
    if (*fp) fputs(header, *fp); // header ainda tem '\n'
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
    const char *phone           = g_array_index(f, char*, 7);
    const char *adress          = g_array_index(f, char*, 8);
    const char *photo           = g_array_index(f, char*, 9);

    // validações sintáticas básicas
    int ok = 1;
    ok &= is_valid_document_number(document_number); // 9 dígitos
    ok &= is_nonempty_str(first_name);
    ok &= is_nonempty_str(last_name);
    ok &= is_valid_date(dob);                        // aaaa-mm-dd
    ok &= is_nonempty_str(nationality);
    ok &= is_valid_gender(gender);                   // M|F|O
    ok &= is_valid_email(email);
    ok &= is_nonempty_str(phone);
    ok &= is_nonempty_str(adress);
    ok &= is_nonempty_str(photo);

    if (!ok) {
        ensure_errors_file(errors_fp, PASSENGERS_ERR_PATH, header);
        if (*errors_fp) fputs(raw, *errors_fp);
        return 0;
    }

    // ⚙️ Cria o passageiro com os 10 argumentos corretos
    Passenger *p = passenger_new(document_number,
                                 first_name,
                                 last_name,
                                 dob,
                                 nationality,
                                 gender,
                                 email,
                                 phone,
                                 adress,
                                 photo);

    passengers_manager_add(mgr, p);
    return 1;
}
