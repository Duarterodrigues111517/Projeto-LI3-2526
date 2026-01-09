#ifndef QUERY6_H
#define QUERY6_H

#include "../Flights_Manager/flights_manager.h"
#include "../Passengers_Manager/passengers_manager.h"
#include "../Reservations_Manager/reservations_manager.h"
#include <glib.h>
#include <stdio.h>

/**
 * @brief Pré-computa/atualiza a estrutura auxiliar usada pela Query 6.
 *
 * Constrói (ou recalcula) a tabela q6_table a partir dos dados existentes nos gestores
 * de reservas, voos e passageiros. Esta função é tipicamente chamada antes de executar
 * a query, para tornar a consulta mais eficiente.
 *
 * @param q6_table Tabela (GHashTable) onde serão guardadas as estruturas/índices da Q6.
 * @param rm Gestor de reservas usado como fonte de dados.
 * @param fm Gestor de voos usado como fonte de dados.
 * @param pm Gestor de passageiros usado como fonte de dados.
 */
void compute_q6(GHashTable *q6_table,
                ReservationsManager_t *rm,
                FlightsManager_t *fm,
                PassengersManager_t *pm);


/**
 * @brief Executa a Query 6 e escreve o resultado num ficheiro de output.
 *
 * Interpreta os argumentos em formato texto (args), consulta a estrutura q6_table
 * (pré-calculada por compute_q6) e escreve o resultado no caminho indicado.
 *
 * O separador sep define o separador de campos no ficheiro de saída (por exemplo ';').
 *
 * @param args String com os argumentos da query (conforme especificação do trabalho).
 * @param sep Separador a usar no output.
 * @param q6_table Tabela (GHashTable) com os dados/índices necessários para a Q6.
 * @param output_path Caminho do ficheiro onde será escrito o resultado.
 */
void querie6(const char *args,
             char sep,
             GHashTable *q6_table,
             const char *output_path);

#endif