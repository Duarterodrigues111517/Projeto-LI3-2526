#include <ctype.h>
#include "utils/validators.h"

static int all_digits(const char *s) {
    if (!s || !*s) return 0;
    for (; *s; s++) if (!isdigit((unsigned char)*s)) return 0;
    return 1;
}

int is_valid_iata3(const char *s) {
    if (!s || strlen(s)!=3) return 0;
    for (int i=0;i<3;i++) if (s[i]<'A'||s[i]>'Z') return 0;
    return 1;
}

static int parse_int2(const char *p, int n, int *out) {
    int v=0; for (int i=0;i<n;i++) { if (!isdigit((unsigned char)p[i])) return 0; v = v*10 + (p[i]-'0'); }
    *out = v; return 1;
}

static int not_future_date(int Y,int M,int D) {
    // Spec: consider current date = 2025/09/30
    if (Y>2025) return 0;
    if (Y==2025 && M>9) return 0;
    if (Y==2025 && M==9 && D>30) return 0;
    return 1;
}

int is_valid_date(const char *s) {
    if (!s || strlen(s)!=10) return 0;
    if (s[4]!='-'||s[7]!='-') return 0;
    int Y,M,D;
    if (!parse_int2(s,4,&Y)) return 0;            // uses only 2 but ok: adjust to 4-digit parse
    // (for brevity, implement a parse_intN for 4 digits)
    Y = (s[0]-'0')*1000+(s[1]-'0')*100+(s[2]-'0')*10+(s[3]-'0');
    M = (s[5]-'0')*10+(s[6]-'0');
    D = (s[8]-'0')*10+(s[9]-'0');
    if (M<1||M>12||D<1||D>31) return 0;
    return not_future_date(Y,M,D);
}

int is_valid_datetime(const char *s) {
    // "aaaa-mm-dd hh:mm"
    if (!s || strlen(s) != 16) return 0;
    if (s[4] != '-' || s[7] != '-' || s[10] != ' ' || s[13] != ':') return 0;

    // validate date part s[0..9]
    char date[11];
    memcpy(date, s, 10);
    date[10] = '\0';
    if (!is_valid_date(date)) return 0;

    int hh = (s[11]-'0')*10 + (s[12]-'0');
    int mm = (s[14]-'0')*10 + (s[15]-'0');
    if (hh < 0 || hh > 23 || mm < 0 || mm > 59) return 0;
    return 1;
}

int is_valid_email(const char *e) {
    if (!e) return 0;
    const char *at = strchr(e,'@'); if (!at) return 0;
    // username
    if (at==e) return 0;
    for (const char *p=e; p<at; p++)
        if (!( (*p>='a'&&*p<='z') || (*p>='0'&&*p<='9') || *p=='.')) return 0;
    // domain lstring.rstring
    const char *dot = strrchr(at+1, '.'); if (!dot || dot==(at+1)) return 0;
    int rlen = (int)strlen(dot+1); if (rlen<2||rlen>3) return 0;
    // all letters
    for (const char *p=at+1; p<dot; p++) if (!(*p>='a'&&*p<='z')) return 0;
    for (const char *p=dot+1; *p; p++) if (!(*p>='a'&&*p<='z')) return 0;
    return 1;
}

int is_valid_airport_type(const char *t) {
    return t && (!strcmp(t,"small_airport")||!strcmp(t,"medium_airport")||
                 !strcmp(t,"large_airport")||!strcmp(t,"heliport")||!strcmp(t,"seaplane_base"));
}

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
    // range
    double val = atof(s);
    if (val<-maxAbsDeg || val>maxAbsDeg) return 0;
    return 1;
}
int is_valid_lat(const char *s){ return is_valid_decimal_in_range(s, 90, 2); }
int is_valid_lon(const char *s){ return is_valid_decimal_in_range(s,180, 3); }

int is_valid_flight_id(const char *s) {
    if (!s || strlen(s)!=7) return 0;
    return (s[0]>='A'&&s[0]<='Z') && (s[1]>='A'&&s[1]<='Z') &&
           all_digits(s+2);
}

int is_valid_reservation_id(const char *s) {
    return s && strlen(s)==10 && s[0]=='R' && all_digits(s+1);
}

int is_valid_document_number(const char *s) {
    return s && strlen(s)==9 && all_digits(s);
}

int is_valid_gender(const char *s) {
    return s && (!strcmp(s,"M")||!strcmp(s,"F")||!strcmp(s,"O"));
}

int is_valid_bracket_list(const char *s) {
    size_t n = s? strlen(s):0;
    return n>=2 && s[0]=='[' && s[n-1]==']';
}

int is_nonempty_str(const char *s) {
    if (!s) return 0;
    while (*s && isspace((unsigned char)*s)) s++;
    return *s != '\0';
}

int is_valid_status(const char *s) {
    return s && (
        strcmp(s, "On Time") == 0 ||
        strcmp(s, "Cancelled") == 0 ||
        strcmp(s, "Delayed")   == 0
    );
}

int is_valid_country_code(const char *s) {
    return s && strlen(s)==2 && isupper((unsigned char)s[0]) && isupper((unsigned char)s[1]);
}



int compare_datetimes(const char *dt1, const char *dt2) {
    // returns negative if dt1 < dt2, 0 if equal, positive if dt1 > dt2
    return strcmp(dt1, dt2);
}