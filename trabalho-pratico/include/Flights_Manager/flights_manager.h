#ifndef FLIGHT_MANAGER_H
#define FLIGHT_MANAGER_H


#include "flights.h"
#include <glib.h>

/**
 * @brief Estrutura opaca que gere um conjunto de voos.
 *
 * O FlightsManager mantém a estrutura interna necessária para armazenar voos
 * e realizar operações de inserção/consulta/iteração.
 */
typedef struct FlightsManager FlightsManager_t;

/* ===== Q5 stats ===== */
/**
 * @brief Estrutura de estatísticas por companhia aérea para a Q5.
 *
 * delayed_count: número de voos considerados atrasados.
 * total_delay_minutes: soma total (em minutos) do atraso acumulado.
 */
typedef struct {
    long delayed_count; /**< @brief Número de voos atrasados. */
    long long total_delay_minutes; /**< @brief Soma dos minutos de atraso. */
} Q5AirlineStat;

/* ===================== Q5 getters/update ===================== */

/**
 * @brief Obtém a tabela de estatísticas da Q5.
 *
 * Tipicamente, esta tabela mapeia uma chave (ex.: nome/código da companhia aérea)
 * para um valor do tipo Q5AirlineStat*.
 *
 * @param fm Gestor de voos.
 * @return Apontador para a GHashTable interna (ou NULL se fm for NULL).
 *
 * @note A gestão de memória (chaves/valores) depende da implementação.
 */
GHashTable *flights_manager_get_q5_table(const FlightsManager_t *fm);
/**
 * @brief Atualiza as estatísticas da Q5 com base num voo.
 *
 * Atualiza/incrementa os acumuladores associados à companhia aérea do voo
 * (por exemplo, contando voos atrasados e somando minutos de atraso).
 *
 * @param fm Gestor de voos a atualizar.
 * @param f Voo a usar como fonte de dados.
 */
void flights_manager_update_q5(FlightsManager_t *fm, const Flight *f);

/* ===================== Gestão de voos ===================== */

/**
 * @brief Função auxiliar para destruir um Flight (para uso como callback).
 *
 * Útil ao configurar funções de destruição em estruturas GLib (ex.: g_hash_table_new_full),
 * permitindo libertar corretamente voos armazenados.
 *
 * @param f Apontador genérico para o Flight a destruir (espera-se (Flight *)f).
 */
void destroy_flight(void *f);
/**
 * @brief Cria um novo gestor de voos.
 *
 * Aloca e inicializa a estrutura interna (por exemplo, uma hash table).
 *
 * @return Apontador para o novo FlightsManager_t em caso de sucesso; NULL em caso de erro.
 */
FlightsManager_t *flights_manager_new(void);

/**
 * @brief Liberta a memória associada ao gestor de voos.
 *
 * Liberta os recursos internos do gestor. Dependendo da implementação,
 * pode também libertar os voos armazenados.
 *
 * @param fm Gestor a libertar (pode ser NULL; nesse caso não faz nada).
 */
void flights_manager_free(FlightsManager_t *fm);
/**
 * @brief Adiciona um voo ao gestor.
 *
 * Normalmente, o voo fica sob gestão do FlightsManager (ownership),
 * mas isso depende da implementação.
 *
 * @param fm Gestor onde inserir o voo.
 * @param f Voo a adicionar.
 */
void flights_manager_add(FlightsManager_t *fm, Flight *f);

/**
 * @brief Obtém um voo pelo seu id.
 *
 * @param fm Gestor de voos.
 * @param id Identificador do voo a procurar.
 *
 * @return Apontador para o Flight correspondente, ou NULL se não existir
 *         (ou se fm/id forem inválidos).
 *
 * @note O objeto devolvido é o armazenado internamente (não deve ser libertado
 *       pelo chamador).
 */
Flight *flights_manager_get(const FlightsManager_t *fm, const char *id);

/**
 * @brief Itera por todos os voos no gestor, aplicando uma função callback.
 *
 * Para cada voo armazenado, chama fn(f, user_data).
 *
 * @param fm Gestor a iterar.
 * @param fn Função a aplicar a cada voo.
 * @param user_data Dados extra passados para a callback (pode ser NULL).
 */
void flights_manager_foreach(FlightsManager_t *fm,
                             void (*fn)(Flight *f, void *user_data),
                             void *user_data);

#endif