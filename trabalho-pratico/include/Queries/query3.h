#ifndef QUERY3_H
#define QUERY3_H

#include "Airports_Manager/airports_manager.h"
#include "Flights_Manager/flights_manager.h"

/**
 * @brief Executa a Query 3 e escreve o resultado num ficheiro de output.
 *
 * Usa um intervalo temporal definido por start_date e end_date para filtrar/calcular
 * resultados com base nos dados de aeroportos e voos.
 *
 * O separador sep define o separador de campos no ficheiro de saída (por exemplo ';').
 *
 * @param start_date Data inicial do intervalo (string).
 * @param end_date Data final do intervalo (string).
 * @param sep Separador a usar no output.
 * @param am Gestor de aeroportos usado como fonte de dados.
 * @param fm Gestor de voos usado como fonte de dados.
 * @param output_path Caminho do ficheiro onde será escrito o resultado.
 */
void querie3(const char *start_date,
             const char *end_date, char sep,
             AirportsManager_t *am,
             FlightsManager_t *fm,
             const char *output_path);

#endif
