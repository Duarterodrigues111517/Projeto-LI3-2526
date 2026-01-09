#ifndef RESERVATIONS_ENTITY_H
#define RESERVATIONS_ENTITY_H

#include <stdbool.h>

/**
 * @brief Estrutura opaca que representa uma reserva.
 *
 * A estrutura interna é mantida privada no ficheiro de implementação (.c).
 * Deve ser criada com reservation_new() e destruída com reservation_free().
 */
typedef struct Reservation Reservation;

/* ===================== Construção / destruição ===================== */

/**
 * @brief Cria uma nova reserva.
 *
 * Aloca e inicializa uma reserva com:
 *  - identificador da reserva,
 *  - até dois identificadores de voo,
 *  - número de documento do passageiro,
 *  - lugar,
 *  - preço.
 *
 * @param reservation_id Identificador da reserva.
 * @param flight_id1 Identificador do 1.º voo associado à reserva.
 * @param flight_id2 Identificador do 2.º voo associado à reserva (se aplicável).
 * @param document_number Número do documento do passageiro.
 * @param seat Lugar atribuído na reserva.
 * @param price Preço associado à reserva.
 *
 * @return Apontador para a nova Reservation em caso de sucesso; NULL em caso de falha
 *         de alocação e/ou validação (conforme a implementação).
 */
Reservation *reservation_new(const char *reservation_id,
                             const char *flight_id1,
                             const char *flight_id2,   
                             int document_number,
                             const char *seat,
                             double price);

/**
 * @brief Liberta a memória associada a uma reserva.
 *
 * Liberta os recursos internos da Reservation e o próprio objeto.
 *
 * @param r Reserva a libertar (pode ser NULL; nesse caso não faz nada).
 */
void reservation_free(Reservation *r);

/* ===================== Getters ===================== */

/**
 * @brief Obtém o identificador da reserva.
 * @param r Reserva.
 * @return String interna com o reservation_id, ou NULL se r for NULL.
 */
const char *reservation_get_reservation_id(const Reservation *r);

/**
 * @brief Obtém um identificador de voo associado à reserva.
 *
 * Nota: esta função devolve um identificador de voo associado, conforme definido
 * pela implementação (por exemplo, o primeiro voo).
 *
 * @param r Reserva.
 * @return String interna com um flight_id, ou NULL se r for NULL.
 */
const char *reservation_get_flight_id(const Reservation *r);

/**
 * @brief Obtém o número de voos associados à reserva.
 *
 * Por exemplo, poderá ser 1 ou 2, dependendo de quantos flight_id estão definidos.
 *
 * @param r Reserva.
 * @return Número de voos associados; 0 se r for NULL (conforme a implementação).
 */
int reservation_get_flights_count(const Reservation *r);

/**
 * @brief Obtém o identificador de voo associado na posição indicada.
 *
 * @param r Reserva.
 * @param index Índice do voo (0, 1, ...), conforme a implementação.
 *
 * @return String interna com o flight_id na posição index, ou NULL se r for NULL
 *         ou se index estiver fora do intervalo.
 */
const char *reservation_get_flight_id_at(const Reservation *r, int index);

/**
 * @brief Obtém o número do documento do passageiro associado à reserva.
 * @param r Reserva.
 * @return document_number; valor indefinido se r for NULL (depende da implementação).
 */
int        reservation_get_document_number(const Reservation *r);

/**
 * @brief Obtém o lugar atribuído na reserva.
 * @param r Reserva.
 * @return String interna com o seat, ou NULL se r for NULL.
 */
const char *reservation_get_seat(const Reservation *r);

/**
 * @brief Obtém o preço da reserva.
 * @param r Reserva.
 * @return Preço da reserva; valor indefinido se r for NULL (depende da implementação).
 */
double     reservation_get_price(const Reservation *r);

/* ===================== Setters ===================== */

/**
 * @brief Atualiza o identificador da reserva.
 *
 * @param r Reserva a atualizar.
 * @param reservation_id Novo identificador.
 *
 * @return true se a atualização for bem-sucedida; false caso contrário.
 */
bool reservation_set_reservation_id(Reservation *r, const char *reservation_id);

/**
 * @brief Atualiza os voos associados à reserva.
 *
 * @param r Reserva a atualizar.
 * @param flight_id1 Identificador do 1.º voo.
 * @param flight_id2 Identificador do 2.º voo (se aplicável).
 *
 * @return true se a atualização for bem-sucedida; false caso contrário.
 */
bool reservation_set_flights(Reservation *r, const char *flight_id1, const char *flight_id2);

/**
 * @brief Atualiza o número do documento do passageiro associado à reserva.
 *
 * @param r Reserva a atualizar.
 * @param document_number Novo número do documento.
 *
 * @return true se a atualização for bem-sucedida; false caso contrário.
 */
bool reservation_set_document_number(Reservation *r, int document_number);

/**
 * @brief Atualiza o lugar atribuído à reserva.
 *
 * @param r Reserva a atualizar.
 * @param seat Novo lugar.
 *
 * @return true se a atualização for bem-sucedida; false caso contrário.
 */
bool reservation_set_seat(Reservation *r, const char *seat);

/**
 * @brief Atualiza o preço da reserva.
 *
 * @param r Reserva a atualizar.
 * @param price Novo preço.
 *
 * @return true se a atualização for bem-sucedida; false caso contrário.
 */
bool reservation_set_price(Reservation *r, double price);




#endif
