#ifndef PASSENGER_MANAGER_H
#define PASSENGER_MANAGER_H

#include "passengers.h"
#include <glib.h>

/**
 * @brief Estrutura opaca que gere um conjunto de passageiros.
 *
 * Mantém internamente as estruturas necessárias para armazenar e consultar passageiros
 * (por exemplo, uma tabela de dispersão indexada por identificador).
 */
typedef struct PassengersManager PassengersManager_t;

/**
 * @brief Função auxiliar para destruir um Passenger (para uso como callback).
 *
 * Útil para passar como função de destruição (destroy func) em estruturas da GLib,
 * como GHashTable, garantindo que os passageiros armazenados são libertados corretamente.
 *
 * @param p Apontador genérico para o passageiro a destruir (espera-se (Passenger*)p).
 */
void destroy_passenger(void *p);

/**
 * @brief Cria um novo gestor de passageiros.
 *
 * Aloca e inicializa a estrutura interna do gestor (por exemplo, a hash table).
 *
 * @return Apontador para um PassengersManager_t em caso de sucesso; NULL em caso de erro.
 */
PassengersManager_t *passengers_manager_new(void);

/**
 * @brief Liberta a memória associada ao gestor de passageiros.
 *
 * Liberta os recursos internos do gestor. Dependendo da implementação, pode também
 * libertar os passageiros armazenados.
 *
 * @param pm Gestor a libertar (pode ser NULL; nesse caso não faz nada).
 */
void passengers_manager_free(PassengersManager_t *pm);

/**
 * @brief Adiciona um passageiro ao gestor.
 *
 * Insere o passageiro na estrutura interna do gestor. A política de ownership
 * (se o gestor passa a ser dono do objeto) depende da implementação, mas é comum
 * que o gestor fique responsável por libertar o passageiro.
 *
 * @param pm Gestor onde inserir.
 * @param p Passageiro a adicionar.
 */
void passengers_manager_add(PassengersManager_t *pm, Passenger *p);

/**
 * @brief Obtém um passageiro a partir do seu identificador.
 *
 * O id usado para pesquisa deve corresponder ao identificador armazenado internamente
 * (por exemplo, document_number).
 *
 * @param pm Gestor de passageiros.
 * @param id Identificador do passageiro a procurar.
 *
 * @return Apontador para o Passenger correspondente, ou NULL se não existir
 *         (ou se pm/id forem inválidos).
 *
 * @note O objeto devolvido pertence ao gestor e não deve ser libertado pelo chamador.
 */
Passenger *passengers_manager_get(const PassengersManager_t *pm, const char *id);

#endif
