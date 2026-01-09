#include <ctype.h>
#include "utils/validators.h"

// Verifica se a string contém apenas dígitos
static int all_digits(const char *s) {
    if (!s || !*s) return 0;
    for (; *s; s++) if (!isdigit((unsigned char)*s)) return 0;
    return 1;
}

// Verifica se a string é um código IATA válido com três letras maiúsculas
int is_valid_iata3(const char *s) {
    if (!s || strlen(s)!=3) return 0;
    for (int i=0;i<3;i++) if (s[i]<'A'||s[i]>'Z') return 0;
    return 1;
}

// Converte n caracteres numéricos consecutivos para um inteiro
static int parse_int2(const char *p, int n, int *out) {
    int v=0; for (int i=0;i<n;i++) { if (!isdigit((unsigned char)p[i])) return 0; v = v*10 + (p[i]-'0'); }
    *out = v; return 1;
}

// Verifica se a data não é posterior a 30 de setembro de 2025
static int not_future_date(int Y,int M,int D) {
    if (Y>2025) return 0;
    if (Y==2025 && M>9) return 0;
    if (Y==2025 && M==9 && D>30) return 0;
    return 1;
}

// Verifica se a string representa uma data válida no formato YYYY-MM-DD
int is_valid_date(const char *s) {
    if (!s || strlen(s)!=10) return 0;
    if (s[4]!='-'||s[7]!='-') return 0;
    int Y,M,D;
    if (!parse_int2(s,4,&Y)) return 0;            
    Y = (s[0]-'0')*1000+(s[1]-'0')*100+(s[2]-'0')*10+(s[3]-'0');
    M = (s[5]-'0')*10+(s[6]-'0');
    D = (s[8]-'0')*10+(s[9]-'0');
    if (M<1||M>12||D<1||D>31) return 0;
    return not_future_date(Y,M,D);
}

// Verifica se a string representa uma data e hora válida no formato YYYY-MM-DD HH:MM
int is_valid_datetime(const char *s) {
    
    if (!s || strlen(s) != 16) return 0;
    if (s[4] != '-' || s[7] != '-' || s[10] != ' ' || s[13] != ':') return 0;

   
    char date[11];
    memcpy(date, s, 10);
    date[10] = '\0';
    if (!is_valid_date(date)) return 0;

    int hh = (s[11]-'0')*10 + (s[12]-'0');
    int mm = (s[14]-'0')*10 + (s[15]-'0');
    if (hh < 0 || hh > 23 || mm < 0 || mm > 59) return 0;
    return 1;
}

// Verifica se a string representa um endereço de email válido segundo o enunciado
int is_valid_email(const char *e) {
    if (!e) return 0;
    const char *at = strchr(e,'@'); if (!at) return 0;
    
    if (at==e) return 0;
    for (const char *p=e; p<at; p++)
        if (!( (*p>='a'&&*p<='z') || (*p>='0'&&*p<='9') || *p=='.')) return 0;
    
    const char *dot = strrchr(at+1, '.'); if (!dot || dot==(at+1)) return 0;
    int rlen = (int)strlen(dot+1); if (rlen<2||rlen>3) return 0;
    
    for (const char *p=at+1; p<dot; p++) if (!(*p>='a'&&*p<='z')) return 0;
    for (const char *p=dot+1; *p; p++) if (!(*p>='a'&&*p<='z')) return 0;
    return 1;
}

// Verifica se o tipo de aeroporto pertence ao conjunto de valores permitidos
int is_valid_airport_type(const char *t) {
    return t && (!strcmp(t,"small_airport")||!strcmp(t,"medium_airport")||
                 !strcmp(t,"large_airport")||!strcmp(t,"heliport")||!strcmp(t,"seaplane_base"));
}

// Verifica se a string é um decimal válido e está dentro do intervalo permitido
static int is_valid_decimal_in_range(const char *s, int maxAbsDeg, int maxIntDigits) {
    if (!s || !*s) return 0;
    const char *p=s; if (*p=='-') p++;
    int intDigits=0, fracDigits=0; int sawDot=0;
    for (; *p; p++) {
        if (*p=='.') { if (sawDot) return 0; sawDot=1; continue; }
        if (!isdigit((unsigned char)*p)) return 0;
        if (!sawDot) intDigits++; else fracDigits++;
    }
    if (intDigits<1 || intDigits>maxIntDigits) return 0;
    if (fracDigits>8) return 0;
   
    double val = atof(s);
    if (val<-maxAbsDeg || val>maxAbsDeg) return 0;
    return 1;
}

// Valida latitude e longitude reutilizando a verificação genérica de decimais
int is_valid_lat(const char *s){ return is_valid_decimal_in_range(s, 90, 2); }
int is_valid_lon(const char *s){ return is_valid_decimal_in_range(s,180, 3); }

// Verifica se o identificador de voo segue o formato ccdddddd? definido no enunciado
int is_valid_flight_id(const char *s) {
    if (!s) return 0;
    
    size_t len = strlen(s);
    if (len != 7 && len != 8) return 0;  // 7 ou 8 caracteres
    
    // Verifica se as 2 primeiras são letras maiúsculas
    if (!(s[0]>='A' && s[0]<='Z') || !(s[1]>='A' && s[1]<='Z')) 
        return 0;
    
    // Verifica se os próximos 5 ou 6 caracteres são dígitos
    return all_digits(s+2);
}

// Verifica se o identificador de reserva segue o formato R seguido de 9 dígitos
int is_valid_reservation_id(const char *s) {
    return s && strlen(s)==10 && s[0]=='R' && all_digits(s+1);
}

// Verifica se o número de documento tem exatamente 9 dígitos
int is_valid_document_number(const char *s) {
    return s && strlen(s)==9 && all_digits(s);
}

// Verifica se o género é um dos valores permitidos (M, F ou O)
int is_valid_gender(const char *s) {
    return s && (!strcmp(s,"M")||!strcmp(s,"F")||!strcmp(s,"O"));
}

// Verifica se a string está no formato de lista entre parênteses retos (começa em '[' e termina em ']')
int is_valid_bracket_list(const char *s) {
    size_t n = s? strlen(s):0;
    return n>=2 && s[0]=='[' && s[n-1]==']';
}

// Verifica se a string não é vazia após ignorar espaços iniciais
int is_nonempty_str(const char *s) {
    if (!s) return 0;
    while (*s && isspace((unsigned char)*s)) s++;
    return *s != '\0';
}

// Verifica se o estado do voo é um dos valores permitidos (On Time, Cancelled ou Delayed)
int is_valid_status(const char *s) {
    return s && (
        strcmp(s, "On Time") == 0 ||
        strcmp(s, "Cancelled") == 0 ||
        strcmp(s, "Delayed")   == 0
    );
}

// Verifica se o código do país tem exatamente duas letras maiúsculas
int is_valid_country_code(const char *s) {
    return s && strlen(s)==2 && isupper((unsigned char)s[0]) && isupper((unsigned char)s[1]);
}

// Compara duas datas e horas no formato YYYY-MM-DD HH:MM por ordem cronológica
int compare_datetimes(const char *dt1, const char *dt2) {
    return strcmp(dt1, dt2);
}


