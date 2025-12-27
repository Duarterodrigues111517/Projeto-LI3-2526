#ifndef QUERY5_H
#define QUERY5_H

#include "Flights_Manager/flights_manager.h"

/*
  args: normalmente é o N (top N companhias).
  sep: separador do output (';' ou outro).
  output_path: ficheiro de output (ex: resultados/command5_output.txt)
*/
void querie5(const char *args, char sep, FlightsManager_t *fm, const char *output_path);

#endif
