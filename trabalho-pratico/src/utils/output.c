#include "utils/output.h"


void log_error(FILE* file, const char* error){
    char* line_cp = strdup(error);
    if (!error)
        printf("error opening file\n");
    
    fprintf(file,"%s",line_cp);
    
    free(line_cp);
}
