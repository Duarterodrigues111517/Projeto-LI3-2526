#ifndef AIRCRAFTS_PARSER_H
#define AIRCRAFTS_PARSER_H

#include "utils/validators.h"
#include "Aircrafts_Manager/aircrafts_manager.h"
#include "Parser/parser.h"
#include <string.h>
#include <errno.h>
#include <stdlib.h>

/**
 * @brief Faz o parsing de uma linha de aeronave e insere o resultado no gestor.
 *
 * A partir da linha crua (raw) e do cabeçalho (header), extrai os campos,
 * valida-os e, se estiverem corretos, cria a aeronave/entrada correspondente
 * e adiciona-a ao gestor.
 *
 * @param f Array de campos já extraídos (tokenizados) a partir da linha.
 * @param raw Linha original (texto completo), útil para logging de erros.
 * @param header Cabeçalho do ficheiro (para mapear/validar colunas).
 * @param mgr Gestor onde a aeronave será inserida.
 * @param errors_fp Apontador para um FILE* onde registar erros (pode ser NULL).
 *
 * @return 0 se a linha for processada com sucesso; valor diferente de 0 em caso
 *         de erro de validação/parsing (ou parâmetros inválidos).
 */
int parse_aircraft_row(GArray *f, const char *raw, const char *header,
                       AircraftsManager_t *mgr, FILE **errors_fp);

/**
 * @brief Faz o parsing de um ficheiro de aeronaves.
 *
 * Lê o ficheiro indicado por path, processa o cabeçalho e faz o parsing de cada
 * linha, construindo e devolvendo um gestor preenchido com as aeronaves válidas.
 *
 * @param path Caminho para o ficheiro a ler.
 *
 * @return Um apontador para um AircraftsManager_t preenchido em caso de sucesso;
 *         NULL em caso de erro (por exemplo, não foi possível abrir/ler o ficheiro
 *         ou ocorreu falha de alocação).
 */
AircraftsManager_t *parse_aircrafts_file(const char *path);

#endif
