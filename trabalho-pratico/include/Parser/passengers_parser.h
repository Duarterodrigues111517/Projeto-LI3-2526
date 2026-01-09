#ifndef PASSENGERS_PARSER_H
#define PASSENGERS_PARSER_H

#include <glib.h>
#include <stdio.h>
#include "Passengers_Manager/passengers_manager.h"
#include "Parser/parser.h"

/**
 * @brief Faz o parsing de uma linha de passageiro e insere o passageiro válido no gestor.
 *
 * Interpreta os campos já tokenizados (f), valida-os e, caso estejam corretos,
 * cria a entrada/estrutura correspondente e adiciona-a ao PassengersManager.
 * Em caso de erro, pode registar a linha original num ficheiro de erros
 * através de errors_fp (se fornecido).
 *
 * @param f Array de campos extraídos (tokenizados) da linha.
 * @param raw Linha original completa (útil para logging de erros).
 * @param header Cabeçalho do ficheiro (para mapear/validar colunas).
 * @param mgr Gestor de passageiros onde inserir o passageiro.
 * @param errors_fp Apontador para um FILE* onde registar linhas inválidas (pode ser NULL).
 *
 * @return 0 se a linha for processada com sucesso; valor diferente de 0 em caso
 *         de erro de validação/parsing (ou parâmetros inválidos).
 */
int parse_passenger_row(GArray *f, const char *raw, const char *header,
                        PassengersManager_t *mgr, FILE **errors_fp);
                        
/**
 * @brief Faz o parsing de um ficheiro de passageiros.
 *
 * Lê o ficheiro indicado por path, processa o cabeçalho e faz o parsing das linhas,
 * devolvendo um gestor preenchido com os passageiros válidos.
 *
 * @param path Caminho para o ficheiro a ler.
 *
 * @return Apontador para um PassengersManager_t preenchido em caso de sucesso;
 *         NULL em caso de erro (por exemplo, falha ao abrir/ler o ficheiro ou alocação).
 */
PassengersManager_t *parse_passengers_file(const char *path);

#endif

