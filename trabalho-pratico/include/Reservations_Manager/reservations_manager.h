#ifndef RESERVATION_MANAGER_H
#define RSERVATION_MANAGER_H


#include "reservations.h"
#include <glib.h>

/**
 * @brief Estrutura opaca que gere um conjunto de reservas.
 *
 * Mantém internamente as estruturas necessárias para armazenar e consultar reservas
 * (por exemplo, uma tabela de dispersão indexada por id).
 */
typedef struct ReservationsManager ReservationsManager_t;

/**
 * @brief Função auxiliar para destruir uma Reservation (uso como callback).
 *
 * Útil para passar como função de destruição em estruturas da GLib, garantindo
 * que as reservas armazenadas são libertadas corretamente.
 *
 * @param r Apontador genérico para a reserva a destruir (espera-se (Reservation *)r).
 */
void destroy_reservation(void *r);

/**
 * @brief Cria um novo gestor de reservas.
 *
 * Aloca e inicializa a estrutura interna do gestor.
 *
 * @return Apontador para um ReservationsManager_t em caso de sucesso; NULL em caso de erro.
 */
ReservationsManager_t *reservations_manager_new(void);

/**
 * @brief Liberta a memória associada ao gestor de reservas.
 *
 * Liberta os recursos internos do gestor e, dependendo da implementação, também
 * as reservas armazenadas.
 *
 * @param rm Gestor a libertar (pode ser NULL; nesse caso não faz nada).
 */
void reservations_manager_free(ReservationsManager_t *rm);

/**
 * @brief Adiciona uma reserva ao gestor.
 *
 * Insere a reserva na estrutura interna do gestor.
 *
 * @param rm Gestor onde inserir a reserva.
 * @param r Reserva a adicionar.
 */
void reservations_manager_add(ReservationsManager_t *rm, Reservation *r);

/**
 * @brief Obtém uma reserva a partir do seu identificador.
 *
 * @param rm Gestor de reservas.
 * @param id Identificador da reserva a procurar.
 *
 * @return Apontador para a Reservation correspondente, ou NULL se não existir
 *         (ou se rm/id forem inválidos).
 *
 * @note O objeto devolvido pertence ao gestor e não deve ser libertado pelo chamador.
 */
Reservation *reservations_manager_get(const ReservationsManager_t *rm, const char *id);

/**
 * @brief Itera sobre todas as reservas no gestor.
 *
 * Aplica a função fn a cada reserva armazenada, passando user_data como argumento extra.
 *
 * @param rm Gestor a iterar.
 * @param fn Função callback aplicada a cada reserva.
 * @param user_data Dados adicionais passados à callback (pode ser NULL).
 */
void reservations_manager_foreach(ReservationsManager_t *rm,
                                  void (*fn)(Reservation *r, void *user_data),
                                  void *user_data);


#endif