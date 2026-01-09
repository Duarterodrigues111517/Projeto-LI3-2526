#ifndef PARSER_GEN_H
#define PARSER_GEN_H

#include <glib.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/**
 * @brief Liberta todos os elementos armazenados num GArray (sem destruir o GArray).
 *
 * Percorre o array e liberta a memória associada a cada elemento (por exemplo,
 * strings duplicadas durante o parsing). O próprio GArray mantém-se válido.
 *
 * @param array GArray cujos elementos devem ser libertados.
 */
void free_garray_parsed_elements(GArray *array);

/**
 * @brief Processa uma linha de um ficheiro CSV, separando campos por ';' e guardando-os num GArray.
 *
 * Lê uma linha do ficheiro, cria (ou atualiza) uma cópia da linha em lineCopy e
 * divide-a em campos usando ';' como delimitador. Os campos são armazenados em array.
 *
 * @param file Ficheiro aberto de onde será lida a próxima linha.
 * @param array GArray onde serão colocados os campos obtidos do parsing.
 * @param lineCopy Apontador para uma string que ficará com a cópia da linha lida (para uso posterior).
 *
 * @return 0 se a linha foi lida e processada com sucesso; valor diferente de 0
 *         em caso de erro ou fim de ficheiro (conforme a implementação).
 */
int process_line(FILE *file, GArray *array, char **lineCopy);

/**
 * @brief Liberta todos os elementos do GArray e destrói o próprio GArray.
 *
 * Função de conveniência que combina a libertação dos elementos (conteúdo)
 * com a destruição do contêiner GArray.
 *
 * @param array GArray a libertar e destruir (pode ser NULL; nesse caso não faz nada).
 */
void free_garray_parsed(GArray *array);

#endif
