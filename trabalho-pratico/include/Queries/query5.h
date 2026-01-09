#ifndef QUERY5_H
#define QUERY5_H

#include "Flights_Manager/flights_manager.h"

/**
 * @brief Executa a Query 5 e escreve o resultado num ficheiro de output.
 *
 * Interpreta os argumentos em formato texto (args) — tipicamente contendo N (top N) —
 * e produz um resultado usando os dados do gestor de voos.
 *
 * O separador sep define o separador de campos no ficheiro de saída (por exemplo ';').
 *
 * @param args String com os argumentos da query (normalmente contém N).
 * @param sep Separador a usar no output.
 * @param fm Gestor de voos usado como fonte de dados.
 * @param output_path Caminho do ficheiro onde será escrito o resultado.
 */
void querie5(const char *args, char sep, FlightsManager_t *fm, const char *output_path);

#endif
