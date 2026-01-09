#ifndef AIRCRAFTS_ENTITY_H
#define AIRCRAFTS_ENTITY_H

#include <stdbool.h>

/**
 * @brief Estrutura opaca que representa uma aeronave.
 *
 * Contém a informação associada a uma aeronave, como identificador,
 * fabricante, modelo, ano, capacidade e alcance.
 */
typedef struct Aircraft Aircraft;

/**
 * @brief Cria uma nova aeronave.
 *
 * Aloca e inicializa uma nova aeronave com os dados fornecidos.
 *
 * @param id Identificador único da aeronave.
 * @param manufacturer Fabricante da aeronave.
 * @param model Modelo da aeronave.
 * @param year Ano de fabrico.
 * @param capacity Capacidade de passageiros.
 * @param range Alcance máximo da aeronave.
 *
 * @return Apontador para a aeronave criada, ou NULL em caso de erro.
 */
Aircraft *aircraft_new(const char *id,
                       const char *manufacturer,
                       const char *model,
                       int year,
                       int capacity,
                       int range);

/**
 * @brief Liberta a memória associada a uma aeronave.
 *
 * Liberta todos os recursos alocados para a aeronave.
 *
 * @param a Apontador para a aeronave a libertar.
 */
void aircraft_free(Aircraft *a);

/**
 * @brief Obtém o identificador da aeronave.
 *
 * @param a Apontador para a aeronave.
 *
 * @return Identificador da aeronave.
 */
const char *aircraft_get_id(const Aircraft *a);

/**
 * @brief Obtém o modelo da aeronave.
 *
 * @param a Apontador para a aeronave.
 *
 * @return Modelo da aeronave.
 */
const char *aircraft_get_model(const Aircraft *a);

/**
 * @brief Obtém o fabricante da aeronave.
 *
 * @param a Apontador para a aeronave.
 *
 * @return Fabricante da aeronave.
 */
const char *aircraft_get_manufacturer(const Aircraft *a);

/**
 * @brief Obtém a capacidade da aeronave.
 *
 * @param a Apontador para a aeronave.
 *
 * @return Capacidade de passageiros.
 */
int aircraft_get_capacity(const Aircraft *a);

/**
 * @brief Obtém o alcance da aeronave.
 *
 * @param a Apontador para a aeronave.
 *
 * @return Alcance máximo da aeronave.
 */
int aircraft_get_range(const Aircraft *a);

/**
 * @brief Obtém o ano de fabrico da aeronave.
 *
 * @param a Apontador para a aeronave.
 *
 * @return Ano de fabrico.
 */
int aircraft_get_year(const Aircraft *a);

/**
 * @brief Define o identificador da aeronave.
 *
 * @param a Apontador para a aeronave.
 * @param id Novo identificador da aeronave.
 *
 * @return true se a operação foi bem-sucedida, false caso contrário.
 */
bool aircraft_set_id(Aircraft *a, const char *id);

/**
 * @brief Define o modelo da aeronave.
 *
 * @param a Apontador para a aeronave.
 * @param model Novo modelo da aeronave.
 *
 * @return true se a operação foi bem-sucedida, false caso contrário.
 */
bool aircraft_set_model(Aircraft *a, const char *model);

/**
 * @brief Define o fabricante da aeronave.
 *
 * @param a Apontador para a aeronave.
 * @param manufacturer Novo fabricante da aeronave.
 *
 * @return true se a operação foi bem-sucedida, false caso contrário.
 */
bool aircraft_set_manufacturer(Aircraft *a, const char *manufacturer);

/**
 * @brief Define a capacidade da aeronave.
 *
 * @param a Apontador para a aeronave.
 * @param capacity Nova capacidade da aeronave.
 *
 * @return true se a operação foi bem-sucedida, false caso contrário.
 */
bool aircraft_set_capacity(Aircraft *a, int capacity);

/**
 * @brief Define o alcance da aeronave.
 *
 * @param a Apontador para a aeronave.
 * @param range Novo alcance da aeronave.
 *
 * @return true se a operação foi bem-sucedida, false caso contrário.
 */
bool aircraft_set_range(Aircraft *a, int range);

/**
 * @brief Define o ano de fabrico da aeronave.
 *
 * @param a Apontador para a aeronave.
 * @param year Novo ano de fabrico.
 *
 * @return true se a operação foi bem-sucedida, false caso contrário.
 */
bool aircraft_set_year(Aircraft *a, int year);

#endif

