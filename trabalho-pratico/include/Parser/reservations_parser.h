#ifndef RESERVATIONS_PARSER_H
#define RESERVATIONS_PARSER_H

#include <glib.h>
#include <stdio.h>
#include "Reservations_Manager/reservations_manager.h"
#include "Flights_Manager/flights_manager.h"
#include "Passengers_Manager/passengers_manager.h"
#include "Parser/parser.h"

/**
 * @brief Faz o parsing de uma linha de reserva e insere a reserva válida no gestor.
 *
 * Interpreta os campos já tokenizados (f), valida-os e, caso estejam corretos,
 * cria a reserva e adiciona-a ao ReservationsManager.
 *
 * Pode também usar os gestores de voos e passageiros para validações cruzadas
 * (por exemplo, confirmar se o voo e/ou passageiro existem).
 *
 * Em caso de erro, pode registar a linha original num ficheiro de erros através
 * de errors_fp (se fornecido).
 *
 * @param f Array de campos extraídos (tokenizados) da linha.
 * @param raw Linha original completa (útil para logging de erros).
 * @param header Cabeçalho do ficheiro (para mapear/validar colunas).
 * @param mgr Gestor de reservas onde inserir a reserva.
 * @param fl_mgr Gestor de voos (para validações cruzadas).
 * @param p_mgr Gestor de passageiros (para validações cruzadas).
 * @param errors_fp Apontador para um FILE* onde registar linhas inválidas (pode ser NULL).
 *
 * @return 0 se a linha for processada com sucesso; valor diferente de 0 em caso
 *         de erro de validação/parsing (ou parâmetros inválidos).
 */
int parse_reservation_row(GArray *f, const char *raw, const char *header,
                          ReservationsManager_t *mgr, FlightsManager_t *fl_mgr, PassengersManager_t *p_mgr, FILE **errors_fp);

/**
 * @brief Faz o parsing de um ficheiro de reservas.
 *
 * Lê o ficheiro indicado por path, processa o cabeçalho e faz o parsing das linhas,
 * devolvendo um gestor preenchido com as reservas válidas.
 *
 * Durante o parsing, pode recorrer aos gestores de voos e passageiros para validar
 * referências (consistência entre entidades).
 *
 * @param path Caminho para o ficheiro a ler.
 * @param fl_mgr Gestor de voos (para validações cruzadas).
 * @param p_mgr Gestor de passageiros (para validações cruzadas).
 *
 * @return Apontador para um ReservationsManager_t preenchido em caso de sucesso;
 *         NULL em caso de erro (por exemplo, falha ao abrir/ler o ficheiro ou alocação).
 */
ReservationsManager_t *parse_reservations_file(const char *path, 
                                               FlightsManager_t *fl_mgr, 
                                               PassengersManager_t *p_mgr);


#endif

