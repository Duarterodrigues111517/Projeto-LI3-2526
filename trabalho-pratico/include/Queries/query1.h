#ifndef QUERY1_H
#define QUERY1_H

#include "../Airports_Manager/airports_manager.h"
#include "../Flights_Manager/flights.h"

/**
 * @brief Executa a Query 1 e escreve o resultado num ficheiro de output.
 *
 * Interpreta os argumentos em formato texto (args), consulta os dados disponíveis
 * no gestor de aeroportos (am) e produz o output no caminho indicado.
 *
 * O separador sep define o separador de campos no ficheiro de saída (por exemplo ';').
 *
 * @param args String com os argumentos da query (conforme especificação do trabalho).
 * @param sep Separador a usar no output.
 * @param am Gestor de aeroportos usado como fonte de dados.
 * @param output_path Caminho do ficheiro onde será escrito o resultado.
 */
void querie1(const char *args, char sep, AirportsManager_t *am, const char *output_path);

#endif

