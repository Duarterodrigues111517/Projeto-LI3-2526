#ifndef AIRCRAFT_MANAGER_H
#define AIRCRAFT_MANAGER_H

#include "aircrafts.h"
#include <glib.h>

/**
 * @brief Estrutura opaca que gere um conjunto de aeronaves.
 *
 * Esta estrutura mantém uma tabela hash de aeronaves, indexadas
 * pelo identificador único de cada aeronave.
 */
typedef struct AircraftsManager AircraftsManager_t;

/**
 * @brief Função de destruição de uma aeronave.
 *
 * Função auxiliar usada como callback para libertar a memória
 * associada a uma aeronave armazenada na tabela hash.
 *
 * @param a Apontador genérico para a aeronave a destruir.
 */
void destroy_aircraft(void *a);

/**
 * @brief Cria um novo gestor de aeronaves.
 *
 * Aloca e inicializa um novo AircraftsManager, criando a estrutura
 * interna necessária para armazenar as aeronaves.
 *
 * @return Apontador para o novo gestor de aeronaves, ou NULL em caso de erro.
 */
AircraftsManager_t *aircrafts_manager_new(void);

/**
 * @brief Liberta a memória associada a um gestor de aeronaves.
 *
 * Liberta todas as aeronaves armazenadas e destrói a estrutura
 * interna do gestor.
 *
 * @param acm Apontador para o gestor de aeronaves a libertar.
 */
void aircrafts_manager_free(AircraftsManager_t *acm);

/**
 * @brief Adiciona uma aeronave ao gestor.
 *
 * Insere uma aeronave no gestor, indexando-a pelo seu identificador.
 * A gestão da memória da aeronave passa a ser responsabilidade do gestor.
 *
 * @param acm Apontador para o gestor de aeronaves.
 * @param a Apontador para a aeronave a adicionar.
 */
void aircrafts_manager_add(AircraftsManager_t *acm, Aircraft *a);

/**
 * @brief Obtém uma aeronave a partir do seu identificador.
 *
 * Procura no gestor uma aeronave com o identificador fornecido.
 *
 * @param acm Apontador para o gestor de aeronaves.
 * @param id Identificador da aeronave a procurar.
 *
 * @return Apontador para a aeronave encontrada, ou NULL se não existir.
 */
Aircraft *aircrafts_manager_get(const AircraftsManager_t *acm, const char *id);

#endif
