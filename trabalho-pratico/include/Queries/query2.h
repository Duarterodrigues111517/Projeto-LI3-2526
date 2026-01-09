#ifndef QUERY2_H
#define QUERY2_H

#include "Aircrafts_Manager/aircrafts_manager.h"
#include "Flights_Manager/flights_manager.h"

/**
 * @brief Executa a Query 2 e escreve o resultado num ficheiro de output.
 *
 * Produz um resultado com base em:
 *  - N (por exemplo, "top N")
 *  - manufacturer (filtro por fabricante)
 *  - dados disponíveis nos gestores de aeronaves e voos.
 *
 * O separador sep define o separador de campos no ficheiro de saída (por exemplo ';').
 *
 * @param N Número (por exemplo, top N) usado pela query.
 * @param manufacturer Fabricante a filtrar (string).
 * @param sep Separador a usar no output.
 * @param acm Gestor de aeronaves usado como fonte de dados.
 * @param fm Gestor de voos usado como fonte de dados.
 * @param output_path Caminho do ficheiro onde será escrito o resultado.
 */
void querie2(int N,
             const char *manufacturer,  char sep,      
             AircraftsManager_t *acm,
             FlightsManager_t *fm,
             const char *output_path);

#endif
