#ifndef AIRPORTS_PARSER_H
#define AIRPORTS_PARSER_H

#include "utils/validators.h"
#include "Airports_Manager/airports_manager.h"
#include "Parser/parser.h"
#include <string.h>
#include <errno.h>
#include <stdlib.h>

/**
 * @brief Faz o parsing de uma linha de aeroporto e insere o resultado no gestor.
 *
 * A partir da linha crua (raw_line) e do cabeçalho (header), extrai os campos,
 * valida-os e, se estiverem corretos, cria a entrada correspondente e adiciona-a
 * ao gestor.
 *
 * @param fields Array de campos já extraídos (tokenizados) a partir da linha.
 * @param raw_line Linha original (texto completo), útil para logging de erros.
 * @param header Cabeçalho do ficheiro (para mapear/validar colunas).
 * @param manager Gestor onde o aeroporto será inserido.
 * @param errors_fp Apontador para um FILE* onde registar erros (pode ser NULL).
 *
 * @return 0 se a linha for processada com sucesso; valor diferente de 0 em caso
 *         de erro de validação/parsing (ou parâmetros inválidos).
 */
int parse_airport_row(GArray *fields, const char *raw_line, const char *header,
                      AirportsManager_t *manager, FILE **errors_fp);

/**
 * @brief Faz o parsing de um ficheiro de aeroportos.
 *
 * Lê o ficheiro indicado por path, processa o cabeçalho e faz o parsing de cada
 * linha, construindo e devolvendo um gestor preenchido com os aeroportos válidos.
 *
 * @param path Caminho para o ficheiro a ler.
 *
 * @return Um apontador para um AirportsManager_t preenchido em caso de sucesso;
 *         NULL em caso de erro (por exemplo, não foi possível abrir/ler o ficheiro
 *         ou ocorreu falha de alocação).
 */
AirportsManager_t *parse_airports_file(const char *path);
#endif
