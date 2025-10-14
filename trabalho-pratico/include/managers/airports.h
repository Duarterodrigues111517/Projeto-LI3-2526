#ifndef AIRPORTS_H
#define AIRPORTS_H

typedef struct airports *Airports;

Airports airports_create(void);
void     airports_destroy(Airports a);

/* devolve 0 em sucesso; negativo em erro (por enquanto só stub) */
int      airports_load_csv(Airports a, const char *csv_path, const char *errors_dir);

#endif
