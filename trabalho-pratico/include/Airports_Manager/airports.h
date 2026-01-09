#ifndef AIRPORTS_H
#define AIRPORTS_H

#include <stddef.h>
#include <stdbool.h>

/**
 * @brief Estrutura opaca que representa um aeroporto.
 *
 * Contém a informação associada a um aeroporto, como código IATA,
 * nome, localização geográfica e contadores de chegadas e partidas.
 */
typedef struct Airport Airport;

/**
 * @brief Cria um novo aeroporto.
 *
 * Aloca e inicializa um aeroporto com os dados fornecidos.
 *
 * @param code Código IATA do aeroporto.
 * @param name Nome do aeroporto.
 * @param city Cidade onde o aeroporto se localiza.
 * @param country País onde o aeroporto se localiza.
 * @param icao Código ICAO do aeroporto.
 * @param type Tipo do aeroporto.
 * @param latitude Latitude geográfica.
 * @param longitude Longitude geográfica.
 * @param arrival_count Número inicial de chegadas.
 * @param departure_count Número inicial de partidas.
 *
 * @return Apontador para o aeroporto criado, ou NULL em caso de erro.
 */
Airport *airport_new(const char *code, const char *name, const char *city,
                     const char *country, const char *icao, const char *type,
                     double latitude, double longitude, int arrival_count,
                     int departure_count);

/**
 * @brief Liberta a memória associada a um aeroporto.
 *
 * Liberta todos os recursos alocados para o aeroporto.
 *
 * @param a Apontador para o aeroporto a libertar.
 */
void airport_free(Airport *a);

/**
 * @brief Obtém o código IATA do aeroporto.
 *
 * @param a Apontador para o aeroporto.
 *
 * @return Código IATA do aeroporto.
 */
const char *airport_get_code(const Airport *a);

/**
 * @brief Obtém o nome do aeroporto.
 *
 * @param a Apontador para o aeroporto.
 *
 * @return Nome do aeroporto.
 */
const char *airport_get_name(const Airport *a);

/**
 * @brief Obtém a cidade do aeroporto.
 *
 * @param a Apontador para o aeroporto.
 *
 * @return Cidade onde o aeroporto se localiza.
 */
const char *airport_get_city(const Airport *a);

/**
 * @brief Obtém o país do aeroporto.
 *
 * @param a Apontador para o aeroporto.
 *
 * @return País onde o aeroporto se localiza.
 */
const char *airport_get_country(const Airport *a);

/**
 * @brief Obtém o código ICAO do aeroporto.
 *
 * @param a Apontador para o aeroporto.
 *
 * @return Código ICAO do aeroporto.
 */
const char *airport_get_icao(const Airport *a);

/**
 * @brief Obtém o tipo do aeroporto.
 *
 * @param a Apontador para o aeroporto.
 *
 * @return Tipo do aeroporto.
 */
const char *airport_get_type(const Airport *a);

/**
 * @brief Obtém a latitude do aeroporto.
 *
 * @param a Apontador para o aeroporto.
 *
 * @return Latitude geográfica.
 */
double airport_get_latitude(const Airport *a);

/**
 * @brief Obtém a longitude do aeroporto.
 *
 * @param a Apontador para o aeroporto.
 *
 * @return Longitude geográfica.
 */
double airport_get_longitude(const Airport *a);

/**
 * @brief Obtém o número de chegadas do aeroporto.
 *
 * @param a Apontador para o aeroporto.
 *
 * @return Número de chegadas.
 */
int airport_get_arrival_count(const Airport *a);

/**
 * @brief Obtém o número de partidas do aeroporto.
 *
 * @param a Apontador para o aeroporto.
 *
 * @return Número de partidas.
 */
int airport_get_departure_count(const Airport *a);

/**
 * @brief Define o código IATA do aeroporto.
 *
 * @param a Apontador para o aeroporto.
 * @param code Novo código IATA.
 *
 * @return true se a operação foi bem-sucedida, false caso contrário.
 */
bool airport_set_code(Airport *a, const char *code);

/**
 * @brief Define o nome do aeroporto.
 *
 * @param a Apontador para o aeroporto.
 * @param name Novo nome do aeroporto.
 *
 * @return true se a operação foi bem-sucedida, false caso contrário.
 */
bool airport_set_name(Airport *a, const char *name);

/**
 * @brief Define a cidade do aeroporto.
 *
 * @param a Apontador para o aeroporto.
 * @param city Nova cidade do aeroporto.
 *
 * @return true se a operação foi bem-sucedida, false caso contrário.
 */
bool airport_set_city(Airport *a, const char *city);

/**
 * @brief Define o país do aeroporto.
 *
 * @param a Apontador para o aeroporto.
 * @param country Novo país do aeroporto.
 *
 * @return true se a operação foi bem-sucedida, false caso contrário.
 */
bool airport_set_country(Airport *a, const char *country);

/**
 * @brief Define o código ICAO do aeroporto.
 *
 * @param a Apontador para o aeroporto.
 * @param icao Novo código ICAO.
 *
 * @return true se a operação foi bem-sucedida, false caso contrário.
 */
bool airport_set_icao(Airport *a, const char *icao);

/**
 * @brief Define o tipo do aeroporto.
 *
 * @param a Apontador para o aeroporto.
 * @param type Novo tipo do aeroporto.
 *
 * @return true se a operação foi bem-sucedida, false caso contrário.
 */
bool airport_set_type(Airport *a, const char *type);

/**
 * @brief Define a latitude do aeroporto.
 *
 * @param a Apontador para o aeroporto.
 * @param lat Nova latitude.
 *
 * @return true se a operação foi bem-sucedida, false caso contrário.
 */
bool airport_set_latitude(Airport *a, double lat);

/**
 * @brief Define a longitude do aeroporto.
 *
 * @param a Apontador para o aeroporto.
 * @param lon Nova longitude.
 *
 * @return true se a operação foi bem-sucedida, false caso contrário.
 */
bool airport_set_longitude(Airport *a, double lon);

/**
 * @brief Incrementa o número de chegadas do aeroporto.
 *
 * @param a Apontador para o aeroporto.
 * @param n Valor a adicionar ao número de chegadas.
 */
void airport_inc_arrivals(Airport *a, int n);

/**
 * @brief Incrementa o número de partidas do aeroporto.
 *
 * @param a Apontador para o aeroporto.
 * @param n Valor a adicionar ao número de partidas.
 */
void airport_inc_departures(Airport *a, int n);

#endif
