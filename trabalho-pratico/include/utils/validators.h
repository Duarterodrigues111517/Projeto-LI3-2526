#ifndef VALIDATOR_H
#define VALIDATOR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Valida uma data no formato "aaaa-mm-dd".
 *
 * Verifica se a string representa uma data válida de acordo com as regras
 * implementadas (formato, separadores e intervalos).
 *
 * @param yyyy_mm_dd String com a data a validar.
 *
 * @return 1 se a data for válida; 0 caso contrário.
 */
int is_valid_date(const char *yyyy_mm_dd); 

/**
 * @brief Valida uma data e hora no formato "aaaa-mm-dd hh:mm".
 *
 * Verifica se a string representa um datetime válido de acordo com as regras
 * implementadas (formato, separadores e intervalos).
 *
 * @param yyyy_mm_dd_hh_mm String com o datetime a validar.
 *
 * @return 1 se o datetime for válido; 0 caso contrário.
 */
int is_valid_datetime(const char *yyyy_mm_dd_hh_mm);  

/**
 * @brief Valida um ano no formato "aaaa".
 *
 * Verifica se a string representa um ano válido de acordo com as regras
 * implementadas.
 *
 * @param yyyy String com o ano a validar.
 *
 * @return 1 se o ano for válido; 0 caso contrário.
 */
int is_valid_year(const char *yyyy);                        

/**
 * @brief Valida um email.
 *
 * Verifica se a string cumpre o formato de email definido pela implementação.
 *
 * @param email String com o email a validar.
 *
 * @return 1 se o email for válido; 0 caso contrário.
 */
int is_valid_email(const char *email);

/**
 * @brief Valida o tipo de aeroporto.
 *
 * Confirma se o valor fornecido corresponde a um tipo de aeroporto aceite
 * pela implementação (por exemplo, categorias definidas no dataset).
 *
 * @param type String com o tipo de aeroporto.
 *
 * @return 1 se for válido; 0 caso contrário.
 */
int is_valid_airport_type(const char *type); 

/**
 * @brief Valida um código IATA de 3 caracteres.
 *
 * @param code String com o código IATA (3 letras).
 *
 * @return 1 se for válido; 0 caso contrário.
 */
int is_valid_iata3(const char *code);                      

/**
 * @brief Valida uma latitude.
 *
 * Verifica se a string representa uma latitude válida (formato numérico e
 * limites aceites pela implementação).
 *
 * @param s String com a latitude.
 *
 * @return 1 se for válida; 0 caso contrário.
 */
int is_valid_lat(const char *s);  

/**
 * @brief Valida uma longitude.
 *
 * Verifica se a string representa uma longitude válida (formato numérico e
 * limites aceites pela implementação).
 *
 * @param s String com a longitude.
 *
 * @return 1 se for válida; 0 caso contrário.
 */
int is_valid_lon(const char *s);   


/**
 * @brief Valida o identificador de um voo.
 *
 * @param s String com o id do voo.
 *
 * @return 1 se for válido; 0 caso contrário.
 */
int is_valid_flight_id(const char *s);      

/**
 * @brief Valida o identificador de uma reserva.
 *
 * @param s String com o id da reserva.
 *
 * @return 1 se for válido; 0 caso contrário.
 */
int is_valid_reservation_id(const char *s); 

/**
 * @brief Valida o número de documento de um passageiro.
 *
 * @param s String com o número do documento.
 *
 * @return 1 se for válido; 0 caso contrário.
 */
int is_valid_document_number(const char *s);

/**
 * @brief Valida o género.
 *
 * Confirma se a string corresponde a um valor aceite pela implementação.
 *
 * @param s String com o género.
 *
 * @return 1 se for válido; 0 caso contrário.
 */
int is_valid_gender(const char *s);        

/**
 * @brief Valida uma lista entre parênteses retos (brackets).
 *
 * Usado para campos que representam listas no formato esperado pela implementação
 * (por exemplo, algo do género "[...,...]").
 *
 * @param s String com a lista.
 *
 * @return 1 se for válida; 0 caso contrário.
 */
int is_valid_bracket_list(const char *s);   


/**
 * @brief Valida o estado (status) de um voo.
 *
 * @param s String com o status.
 *
 * @return 1 se for válido; 0 caso contrário.
 */
int is_valid_status(const char *s);   

/**
 * @brief Verifica se uma string não é vazia.
 *
 * Tipicamente confirma se o apontador não é NULL e se a string contém pelo menos
 * um carácter não-terminador.
 *
 * @param s String a verificar.
 *
 * @return 1 se for não vazia; 0 caso contrário.
 */
int is_nonempty_str(const char *s);     

/**
 * @brief Valida o género.
 *
 * @param s String com o género.
 * @return 1 se for válido; 0 caso contrário.
 */
int is_valid_gender(const char *s);   

/**
 * @brief Valida um código de país.
 *
 * @param s String com o código do país.
 * @return 1 se for válido; 0 caso contrário.
 */
int is_valid_country_code(const char *s); 

/**
 * @brief Valida uma lista no formato esperado pelo projeto.
 *
 * @param s String com a lista.
 * @return 1 se for válida; 0 caso contrário.
 */
int is_valid_list(const char *s);

/*
 * @brief Compara dois datetimes no formato "YYYY-MM-DD HH:MM".
 *
 * @param dt1 Primeiro datetime.
 * @param dt2 Segundo datetime.
 *
 * @return Valor negativo se dt1 < dt2;
 *         0 se forem iguais;
 *         valor positivo se dt1 > dt2.
 */
int compare_datetimes(const char *dt1, const char *dt2); 




#endif