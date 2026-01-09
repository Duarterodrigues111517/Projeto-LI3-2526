#ifndef AIRPORT_MANAGER_H
#define AIRPORT_MANAGER_H

#include "airports.h"
#include <glib.h>
#include "Flights_Manager/flights_manager.h"
#include "Reservations_Manager/reservations_manager.h"
#include <string.h>
#include "Flights_Manager/flights.h"
#include "Reservations_Manager/reservations.h"
#include "Airports_Manager/airports.h"

/**
 * @brief Estrutura opaca que gere um conjunto de aeroportos.
 *
 * Esta estrutura mantém uma tabela hash de aeroportos, indexados
 * pelo respetivo código IATA.
 */
typedef struct AirportsManager AirportsManager_t;

/**
 * @brief Função de destruição de um aeroporto.
 *
 * Função auxiliar usada como callback para libertar a memória
 * associada a um aeroporto armazenado na tabela hash.
 *
 * @param a Apontador genérico para o aeroporto a destruir.
 */
void destroy_airport(void *a);

/**
 * @brief Cria um novo gestor de aeroportos.
 *
 * Aloca e inicializa um novo AirportsManager, criando a estrutura
 * interna necessária para armazenar aeroportos.
 *
 * @return Apontador para o gestor de aeroportos criado, ou NULL em caso de erro.
 */
AirportsManager_t *airports_manager_new(void);

/**
 * @brief Liberta a memória associada a um gestor de aeroportos.
 *
 * Liberta todos os aeroportos armazenados e destrói a estrutura
 * interna do gestor.
 *
 * @param am Apontador para o gestor de aeroportos a libertar.
 */
void airports_manager_free(AirportsManager_t *am);

/**
 * @brief Adiciona um aeroporto ao gestor.
 *
 * Insere um aeroporto no gestor, indexando-o pelo seu código IATA.
 * A gestão da memória do aeroporto passa a ser responsabilidade do gestor.
 *
 * @param am Apontador para o gestor de aeroportos.
 * @param a Apontador para o aeroporto a adicionar.
 */
void airports_manager_add(AirportsManager_t *am, Airport *a);

/**
 * @brief Obtém um aeroporto a partir do seu código IATA.
 *
 * Procura no gestor um aeroporto com o código fornecido.
 *
 * @param am Apontador para o gestor de aeroportos.
 * @param id Código IATA do aeroporto a procurar.
 *
 * @return Apontador para o aeroporto encontrado, ou NULL se não existir.
 */
Airport *airports_manager_get(const AirportsManager_t *am, const char *id);

/**
 * @brief Calcula o número de chegadas e partidas por aeroporto.
 *
 * Percorre todas as reservas e voos existentes, atualizando os contadores
 * de chegadas e partidas de cada aeroporto, ignorando voos cancelados.
 *
 * @param am Apontador para o gestor de aeroportos.
 * @param fm Apontador para o gestor de voos.
 * @param rm Apontador para o gestor de reservas.
 */
void airports_manager_compute_passenger_counts(AirportsManager_t *am,
                                               FlightsManager_t *fm,
                                               ReservationsManager_t *rm);

#endif
