#ifndef FLIGHTS_H
#define FLIGHTS_H

#include <stdbool.h>
#include <utils/validators.h>

/**
 * @brief EStrutura opaco que representa um voo.
 *
 * A estrutura interna é mantida privada no ficheiro de implementação (.c).
 * Deve ser criada com flight_new() e destruída com flight_free().
 */
typedef struct Flight Flight;

/**
 * @brief Cria um novo voo (Flight).
 *
 * Aloca e inicializa um voo com os campos fornecidos. Tipicamente, os campos
 * podem ser validados (formato de datas, strings obrigatórias, etc.).
 *
 * @param id Identificador único do voo.
 * @param departure Data/hora prevista de partida (string).
 * @param actual_departure Data/hora real de partida (string).
 * @param arrival Data/hora prevista de chegada (string).
 * @param actual_arrival Data/hora real de chegada (string).
 * @param gate Gate associado ao voo.
 * @param status Estado do voo (ex.: "Delayed", "On Time", ...).
 * @param origin Aeroporto/cidade de origem.
 * @param destination Aeroporto/cidade de destino.
 * @param aircraft Identificador/modelo da aeronave.
 * @param airline Companhia aérea.
 *
 * @return Apontador para o novo Flight em caso de sucesso; NULL se ocorrer
 *         erro de alocação ou se algum campo for considerado inválido.
 */
Flight *flight_new(const char *id, const char *departure, 
                   const char *actual_departure,
                   const char *arrival,
                   const char *actual_arrival,
                   const char *gate,
                   const char *status,
                   const char *origin,
                   const char *destination,
                   const char *aircraft,
                   const char *airline);

/**
 * @brief Liberta a memória associada a um voo.
 *
 * Liberta todos os recursos internos do Flight e o próprio objeto.
 * Após esta chamada, o apontador deixa de ser válido.
 *
 * @param f Voo a libertar (pode ser NULL; nesse caso não faz nada).
 */
void flight_free(Flight *f);

/* ===================== Getters ===================== */

/**
 * @brief Obtém o identificador do voo.
 * @param f Voo de onde obter o campo.
 * @return String interna com o id do voo, ou NULL se f for NULL.
 */
const char *flight_get_id(const Flight *f);
/**
 * @brief Obtém a data/hora prevista de partida.
 * @param f Voo de onde obter o campo.
 * @return String interna com a partida prevista, ou NULL se f for NULL.
 */
const char *flight_get_departure(const Flight *f);
/**
 * @brief Obtém a data/hora real de partida.
 * @param f Voo de onde obter o campo.
 * @return String interna com a partida real, ou NULL se f for NULL.
 */
const char *flight_get_actual_departure(const Flight *f);
/**
 * @brief Obtém a data/hora prevista de chegada.
 * @param f Voo de onde obter o campo.
 * @return String interna com a chegada prevista, ou NULL se f for NULL.
 */
const char *flight_get_arrival(const Flight *f);
/**
 * @brief Obtém a data/hora real de chegada.
 * @param f Voo de onde obter o campo.
 * @return String interna com a chegada real, ou NULL se f for NULL.
 */
const char *flight_get_actual_arrival(const Flight *f);
/**
 * @brief Obtém o gate do voo.
 * @param f Voo de onde obter o campo.
 * @return String interna com o gate, ou NULL se f for NULL.
 */
const char *flight_get_gate(const Flight *f);
/**
 * @brief Obtém o estado do voo.
 * @param f Voo de onde obter o campo.
 * @return String interna com o estado, ou NULL se f for NULL.
 */
const char *flight_get_status(const Flight *f);
/**
 * @brief Obtém a origem do voo.
 * @param f Voo de onde obter o campo.
 * @return String interna com a origem, ou NULL se f for NULL.
 */
const char *flight_get_origin(const Flight *f);
/**
 * @brief Obtém o destino do voo.
 * @param f Voo de onde obter o campo.
 * @return String interna com o destino, ou NULL se f for NULL.
 */
const char *flight_get_destination(const Flight *f);
/**
 * @brief Obtém a aeronave associada ao voo.
 * @param f Voo de onde obter o campo.
 * @return String interna com a aeronave, ou NULL se f for NULL.
 */
const char *flight_get_aircraft(const Flight *f);
/**
 * @brief Obtém a companhia aérea do voo.
 * @param f Voo de onde obter o campo.
 * @return String interna com a companhia aérea, ou NULL se f for NULL.
 */
const char *flight_get_airline(const Flight *f);

/* ===================== Setters ===================== */

/**
 * @brief Atualiza a data/hora prevista de partida.
 * @param f Voo a atualizar.
 * @param dt Nova data/hora (string).
 * @return true se a atualização for bem-sucedida; false se f/dt for inválido.
 */
bool flight_set_departure(Flight *f, const char *dt);
/**
 * @brief Atualiza a data/hora real de partida.
 * @param f Voo a atualizar.
 * @param dt Nova data/hora (string).
 * @return true se a atualização for bem-sucedida; false se f/dt for inválido.
 */
bool flight_set_actual_departure(Flight *f, const char *dt);
/**
 * @brief Atualiza a data/hora prevista de chegada.
 * @param f Voo a atualizar.
 * @param dt Nova data/hora (string).
 * @return true se a atualização for bem-sucedida; false se f/dt for inválido.
 */
bool flight_set_arrival(Flight *f, const char *dt);
/**
 * @brief Atualiza a data/hora real de chegada.
 * @param f Voo a atualizar.
 * @param dt Nova data/hora (string).
 * @return true se a atualização for bem-sucedida; false se f/dt for inválido.
 */
bool flight_set_actual_arrival(Flight *f, const char *dt);
/**
 * @brief Atualiza o gate do voo.
 * @param f Voo a atualizar.
 * @param gate Novo gate.
 * @return true se a atualização for bem-sucedida; false se f/gate for inválido.
 */
bool flight_set_gate(Flight *f, const char *gate);
/**
 * @brief Atualiza o estado do voo.
 * @param f Voo a atualizar.
 * @param status Novo estado.
 * @return true se a atualização for bem-sucedida; false se f/status for inválido.
 */
bool flight_set_status(Flight *f, const char *status);
/**
 * @brief Atualiza a origem do voo.
 * @param f Voo a atualizar.
 * @param origin Nova origem.
 * @return true se a atualização for bem-sucedida; false se f/origin for inválido.
 */
bool flight_set_origin(Flight *f, const char *origin);
/**
 * @brief Atualiza o destino do voo.
 * @param f Voo a atualizar.
 * @param destination Novo destino.
 * @return true se a atualização for bem-sucedida; false se f/destination for inválido.
 */
bool flight_set_destination(Flight *f, const char *destination);
/**
 * @brief Atualiza a aeronave do voo.
 * @param f Voo a atualizar.
 * @param aircraft Nova aeronave.
 * @return true se a atualização for bem-sucedida; false se f/aircraft for inválido.
 */
bool flight_set_aircraft(Flight *f, const char *aircraft);
/**
 * @brief Atualiza a companhia aérea do voo.
 * @param f Voo a atualizar.
 * @param airline Nova companhia aérea.
 * @return true se a atualização for bem-sucedida; false se f/airline for inválido.
 */
bool flight_set_airline(Flight *f, const char *airline);

#endif
