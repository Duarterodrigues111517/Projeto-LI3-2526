#ifndef FLIGHTS_PARSER_H
#define FLIGHTS_PARSER_H

#include <glib.h>
#include <stdio.h>
#include "Flights_Manager/flights_manager.h"
#include "Aircrafts_Manager/aircrafts_manager.h"
#include "Parser/parser.h"

/**
 * @brief Faz o parsing de uma linha de voo e insere o voo válido no gestor.
 *
 * Extrai os campos de f (já tokenizados), usa raw/header para mapeamento e/ou
 * logging, valida os dados e, se tudo estiver correto, cria o Flight e adiciona-o
 * ao FlightsManager.
 *
 * Pode também usar a informação do gestor de aeronaves (a_mgr) para validar
 * relações/consistência (por exemplo, aeronave existente).
 *
 * @param f Array de campos já extraídos (tokenizados) da linha.
 * @param raw Linha original completa (útil para registo de erros).
 * @param header Cabeçalho do ficheiro (para mapear colunas).
 * @param mgr Gestor de voos onde o voo será inserido.
 * @param a_mgr Gestor de aeronaves usado para validações cruzadas.
 * @param errors_fp Apontador para um FILE* onde registar linhas inválidas (pode ser NULL).
 *
 * @return 0 se a linha for processada com sucesso; valor diferente de 0 em caso
 *         de erro de validação/parsing (ou parâmetros inválidos).
 */
int parse_flight_row(GArray *f, const char *raw, const char *header,
                     FlightsManager_t *mgr,AircraftsManager_t *a_mgr, FILE **errors_fp);

/**
 * @brief Faz o parsing de um ficheiro CSV de voos.
 *
 * Lê o CSV indicado por csvPath, processa o cabeçalho e faz o parsing de todas
 * as linhas, construindo e devolvendo um gestor preenchido com os voos válidos.
 *
 * @param csvPath Caminho para o ficheiro CSV de voos.
 * @param a_mgr Gestor de aeronaves (para validações cruzadas durante o parsing).
 *
 * @return Apontador para um FlightsManager_t preenchido em caso de sucesso; NULL
 *         em caso de erro (por exemplo, falha ao abrir/ler o ficheiro ou alocação).
 */
FlightsManager_t *parse_flights_file(const char *csvPath, AircraftsManager_t *a_mgr);
#endif


