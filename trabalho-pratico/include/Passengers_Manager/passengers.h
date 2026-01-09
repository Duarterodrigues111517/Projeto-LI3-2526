#ifndef PASSENGERS_ENTITY_H
#define PASSENGERS_ENTITY_H

#include <stdbool.h>

/**
 * @brief Estrutura opaca que representa um passageiro.
 *
 * A estrutura interna é mantida privada no ficheiro de implementação (.c).
 * Deve ser criada com passenger_new() e destruída com passenger_free().
 */
typedef struct Passenger Passenger;

//* ===================== Construção / destruição ===================== */

/**
 * @brief Cria um novo passageiro.
 *
 * Aloca e inicializa um passageiro com os campos fornecidos. Em geral, esta função
 * pode validar os argumentos (por exemplo, formatos de data, strings vazias, etc.).
 *
 * @param document_number Número do documento do passageiro (identificador).
 * @param first_name Primeiro nome do passageiro.
 * @param last_name Último nome do passageiro.
 * @param dob Data de nascimento (string).
 * @param nationality Nacionalidade do passageiro.
 * @param gender Género do passageiro.
 *
 * @return Apontador para o novo Passenger em caso de sucesso; NULL se ocorrer erro
 *         de alocação e/ou se algum campo for considerado inválido.
 */
Passenger *passenger_new(const char *document_number,
                         const char *first_name,
                         const char *last_name,
                         const char *dob,
                         const char *nationality,
                         const char *gender);
/**
 * @brief Liberta a memória associada a um passageiro.
 *
 * Liberta os recursos internos do Passenger e o próprio objeto.
 *
 * @param p Passageiro a libertar (pode ser NULL; nesse caso não faz nada).
 */
void passenger_free(Passenger *p);

/* ===================== Getters ===================== */

/**
 * @brief Obtém o número do documento do passageiro.
 * @param p Passageiro.
 * @return String interna com o document_number, ou NULL se p for NULL.
 */
const char *passenger_get_document_number(const Passenger *p);

/**
 * @brief Obtém o primeiro nome do passageiro.
 * @param p Passageiro.
 * @return String interna com o first_name, ou NULL se p for NULL.
 */
const char *passenger_get_first_name(const Passenger *p);

/**
 * @brief Obtém o último nome do passageiro.
 * @param p Passageiro.
 * @return String interna com o last_name, ou NULL se p for NULL.
 */
const char *passenger_get_last_name(const Passenger *p);

/**
 * @brief Obtém a data de nascimento do passageiro.
 * @param p Passageiro.
 * @return String interna com o dob, ou NULL se p for NULL.
 */
const char *passenger_get_dob(const Passenger *p);

/**
 * @brief Obtém a nacionalidade do passageiro.
 * @param p Passageiro.
 * @return String interna com a nationality, ou NULL se p for NULL.
 */
const char *passenger_get_nationality(const Passenger *p);

/**
 * @brief Obtém o género do passageiro.
 * @param p Passageiro.
 * @return String interna com o gender, ou NULL se p for NULL.
 */
const char *passenger_get_gender(const Passenger *p);

/* ===================== Setters ===================== */

/**
 * @brief Atualiza o número do documento do passageiro.
 *
 * @param p Passageiro a atualizar.
 * @param document_number Novo número de documento.
 *
 * @return true se a atualização for bem-sucedida; false se p/document_number forem inválidos
 *         (ou se falhar validação/alocação interna, conforme a implementação).
 */
bool passenger_set_document_number(Passenger *p, const char *document_number);

/**
 * @brief Atualiza o primeiro nome do passageiro.
 *
 * @param p Passageiro a atualizar.
 * @param name Novo primeiro nome.
 *
 * @return true se a atualização for bem-sucedida; false caso contrário.
 */
bool passenger_set_first_name(Passenger *p, const char *name);

/**
 * @brief Atualiza o último nome do passageiro.
 *
 * @param p Passageiro a atualizar.
 * @param name Novo último nome.
 *
 * @return true se a atualização for bem-sucedida; false caso contrário.
 */
bool passenger_set_last_name(Passenger *p, const char *name);

/**
 * @brief Atualiza a data de nascimento do passageiro.
 *
 * @param p Passageiro a atualizar.
 * @param dob Nova data de nascimento (string).
 *
 * @return true se a atualização for bem-sucedida; false caso contrário.
 */
bool passenger_set_dob(Passenger *p, const char *dob);

/**
 * @brief Atualiza a nacionalidade do passageiro.
 *
 * @param p Passageiro a atualizar.
 * @param nationality Nova nacionalidade.
 *
 * @return true se a atualização for bem-sucedida; false caso contrário.
 */
bool passenger_set_nationality(Passenger *p, const char *nationality);

/**
 * @brief Atualiza o género do passageiro.
 *
 * @param p Passageiro a atualizar.
 * @param gender Novo género.
 *
 * @return true se a atualização for bem-sucedida; false caso contrário.
 */
bool passenger_set_gender(Passenger *p, const char *gender);

#endif

