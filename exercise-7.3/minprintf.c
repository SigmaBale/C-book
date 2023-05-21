#include <ctype.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>

//Official submission for code crimes check format_and_print skull

#define PARAMLIMIT 100

typedef enum {
    NONE,
    CHAR,
    SHORT,
    LONG,
    LLONG,
    LDOUBLE,
} Specifier;

typedef enum {
    LEFTADJ   = 1,
    WIDTH     = 2,
    PRECISION = 4,
    SPECIFIER = 8,
    END       = 16,
} Flags;

typedef union {
    int                    _int;
    unsigned int           _unsigned_int;
    long int               _long_int;
    unsigned long int      _unsigned_long_int;
    long long int          _long_long_int;
    unsigned long long int _unsigned_long_long_int;
    double                 _double;
    long double            _long_double;
    char*                  _string;
    void*                  _ptr;
} Atype;

void  minprintf(char* fmt, ...);
void  format_and_print(uint, char, Specifier, uint, uint, Atype*);
// Returns the pointer offset from
// i to after conversion - 1 step back
char* patoi(char* str, unsigned* n);

int
main(void)
{
    minprintf("Something %-20.10d like this\n", 120);
    minprintf("Maybe without args\n");
    minprintf("%s\n", "test");
    return 0;
}

void
minprintf(char* fmt, ...)
{
    va_list ap;
    char *  p, *sval;
    Atype   val;

    unsigned int width, precision;
    Specifier    spec       = NONE;
    char         conversion = '\0';

    unsigned int f = 0;

    va_start(ap, fmt);

    for(p = fmt; *p; p++) {
        if(*p != '%') {
            putchar(*p);
            continue;
        }
        if(*(p + 1) == '\0') {
            va_end(ap);
            return;
        }

        while(((f & END) == 0)) {
            switch(*++p) {
                case '-':
                    if((f & (WIDTH | PRECISION | SPECIFIER)) == 0) {
                        f |= LEFTADJ;
                    } else {
                        va_end(ap);
                        return;
                    }
                    break;
                case '.':
                    if((f & (PRECISION | SPECIFIER)) == 0) {
                        p = patoi(++p, &precision);
                        f |= PRECISION;
                    } else {
                        va_end(ap);
                        return;
                    }
                    break;
                case 'h':
                    if(spec == NONE)
                        spec = SHORT;
                    else if(spec == SHORT)
                        spec = CHAR;
                    else {
                        va_end(ap);
                        return;
                    }
                    f |= SPECIFIER;
                    break;
                case 'l':
                    if(spec == NONE)
                        spec = LONG;
                    else if(spec == LONG)
                        spec = LLONG;
                    else {
                        va_end(ap);
                        return;
                    }
                    f |= SPECIFIER;
                    break;
                case 'L':
                    if(spec == NONE)
                        spec = LDOUBLE;
                    else {
                        va_end(ap);
                        return;
                    }
                    f |= SPECIFIER;
                    break;
                case 'd':
                case 'c':
                case 'i':
                    if((f & (PRECISION | SPECIFIER)) != 0 && *p == 'c') {
                        va_end(ap);
                        return;
                    } else if((f & SPECIFIER) != 0) {
                        switch(spec) {
                            case CHAR:
                            case SHORT:
                                val._int = va_arg(ap, int);
                                break;
                            case LONG:
                                val._long_int = va_arg(ap, long int);
                                break;
                            case LLONG:
                                val._long_long_int = va_arg(ap, long long int);
                                break;
                            default:
                                va_end(ap);
                                return;
                        }
                    } else {
                        val._int = va_arg(ap, int);
                    }
                    if(*p == 'd' || *p == 'i')
                        conversion = 'd';
                    else
                        conversion = 'c';
                    f |= END;
                    format_and_print(f, conversion, spec, precision, width, &val);
                    break;
                case 'u':
                case 'o':
                case 'x':
                case 'X':
                    if(f & SPECIFIER) {
                        switch(spec) {
                            case CHAR:
                            case SHORT:
                                val._unsigned_int = va_arg(ap, unsigned int);
                            case LONG:
                                val._unsigned_long_int = va_arg(ap, unsigned long int);
                                break;
                            case LLONG:
                                val._unsigned_long_long_int = va_arg(ap, unsigned long long int);
                                break;
                            default:
                                va_end(ap);
                                return;
                        }
                    }
                    if(*p == 'u')
                        conversion = 'u';
                    else if(*p == 'x')
                        conversion = 'x';
                    else if(*p == 'X')
                        conversion = 'X';
                    else
                        conversion = 'o';
                    f |= END;
                    format_and_print(f, conversion, spec, precision, width, &val);
                    break;
                case 'f':
                case 'F':
                case 'e':
                case 'E':
                case 'g':
                case 'G':
                    if(f & SPECIFIER) {
                        switch(spec) {
                            case LONG:
                                val._double = va_arg(ap, double);
                                break;
                            case LDOUBLE:
                                val._long_double = va_arg(ap, long double);
                                break;
                            default:
                                va_end(ap);
                                return;
                        }
                    }
                    if(*p == 'f')
                        conversion = 'f';
                    else if(*p == 'e')
                        conversion = 'e';
                    else if(*p == 'E')
                        conversion = 'E';
                    else if(*p == 'g')
                        conversion = 'g';
                    else
                        conversion = 'G';
                    f |= END;
                    format_and_print(f, conversion, spec, precision, width, &val);
                    break;
                case 's':
                    // No support for wide char
                    if(f & SPECIFIER) {
                        va_end(ap);
                        return;
                    }
                    val._string = va_arg(ap, char*);
                    conversion  = 's';
                    f           |= END;
                    format_and_print(f, conversion, spec, precision, width, &val);
                    break;
                case 'p':
                    if((f & (SPECIFIER | PRECISION)) != 0) {
                        va_end(ap);
                        return;
                    }
                    val._ptr   = va_arg(ap, void*);
                    conversion = 'p';
                    f          |= END;
                    format_and_print(f, conversion, spec, precision, width, &val);
                    break;
                default:
                    if(isdigit(*p) && (f & (WIDTH | PRECISION | SPECIFIER)) == 0) {
                        p = patoi(p, &width);
                        f |= WIDTH;
                    } else if(*p == '%') {
                        putchar(*p);
                        f |= END;
                    } else {
                        va_end(ap);
                        return;
                    }
                    break;
            }
        }
    }
    va_end(ap);
}

void
format_and_print(unsigned int flags, char conversion, Specifier specifier, uint precision, uint width, Atype* val)
{
    if(flags == (LEFTADJ | WIDTH | PRECISION | SPECIFIER | END)) {
        switch(conversion) {
            case 'd':
            case 'i':
                switch(specifier) {
                    case CHAR:
                        printf("%-*.*hhd", width, precision, val->_int);
                        break;
                    case SHORT:
                        printf("%-*.*hd", width, precision, val->_int);
                        break;
                    case LONG:
                        printf("%-*.*ld", width, precision, val->_long_int);
                        break;
                    case LLONG:
                        printf("%-*.*lld", width, precision, val->_long_long_int);
                        break;
                    default:
                        printf("Unreachable\n");
                        break;
                }
                break;
            case 'u':
            case 'o':
            case 'x':
            case 'X':
                switch(specifier) {
                    case CHAR:
                        if(conversion == 'u')
                            printf("%-*.*hhu", width, precision, val->_unsigned_int);
                        else if(conversion == 'o')
                            printf("%-*.*hho", width, precision, val->_unsigned_int);
                        else if(conversion == 'x')
                            printf("%-*.*hhx", width, precision, val->_unsigned_int);
                        else
                            printf("%-*.*hhX", width, precision, val->_unsigned_int);
                        break;
                    case SHORT:
                        if(conversion == 'u')
                            printf("%-*.*hu", width, precision, val->_unsigned_int);
                        else if(conversion == 'o')
                            printf("%-*.*ho", width, precision, val->_unsigned_int);
                        else if(conversion == 'x')
                            printf("%-*.*hx", width, precision, val->_unsigned_int);
                        else
                            printf("%-*.*hX", width, precision, val->_unsigned_int);
                        break;
                    case LONG:
                        if(conversion == 'u')
                            printf("%-*.*lu", width, precision, val->_unsigned_long_int);
                        else if(conversion == 'o')
                            printf("%-*.*lo", width, precision, val->_unsigned_long_int);
                        else if(conversion == 'x')
                            printf("%-*.*lx", width, precision, val->_unsigned_long_int);
                        else
                            printf("%-*.*lX", width, precision, val->_unsigned_long_int);
                        break;
                    case LLONG:
                        if(conversion == 'u')
                            printf("%-*.*llu", width, precision, val->_unsigned_long_long_int);
                        else if(conversion == 'o')
                            printf("%-*.*llo", width, precision, val->_unsigned_long_long_int);
                        else if(conversion == 'x')
                            printf("%-*.*llx", width, precision, val->_unsigned_long_long_int);
                        else
                            printf("%-*.*llX", width, precision, val->_unsigned_long_long_int);
                        break;
                    default:
                        printf("Unreachable\n");
                        break;
                }
                break;
            case 'f':
            case 'F':
            case 'e':
            case 'E':
            case 'G':
            case 'g':
                switch(specifier) {
                    case LONG:
                    case LLONG:
                        if(conversion == 'f')
                            printf("%-*.*lf", width, precision, val->_double);
                        else if(conversion == 'F')
                            printf("%-*.*lF", width, precision, val->_double);
                        else if(conversion == 'e')
                            printf("%-*.*le", width, precision, val->_double);
                        else if(conversion == 'E')
                            printf("%-*.*lE", width, precision, val->_double);
                        else if(conversion == 'G')
                            printf("%-*.*lG", width, precision, val->_double);
                        else
                            printf("%-*.*lg", width, precision, val->_double);
                        break;
                    case LDOUBLE:
                        if(conversion == 'f')
                            printf("%-*.*Lf", width, precision, val->_long_double);
                        else if(conversion == 'F')
                            printf("%-*.*LF", width, precision, val->_long_double);
                        else if(conversion == 'e')
                            printf("%-*.*Le", width, precision, val->_long_double);
                        else if(conversion == 'E')
                            printf("%-*.*LE", width, precision, val->_long_double);
                        else if(conversion == 'G')
                            printf("%-*.*LG", width, precision, val->_long_double);
                        else
                            printf("%-*.*Lg", width, precision, val->_long_double);
                        break;
                    default:
                        printf("Unreachable\n");
                        break;
                }
                break;
            default:
                printf("Unreachable conversion %c\n", conversion);
                break;
        }
    } else if(flags == (LEFTADJ | WIDTH | PRECISION | END)) {
        switch(conversion) {
            case 'd':
            case 'i':
                printf("%-*.*d", width, precision, val->_int);
                break;
            case 'u':
                printf("%-*.*u", width, precision, val->_unsigned_int);
                break;
            case 'o':
                printf("%-*.*o", width, precision, val->_unsigned_int);
                break;
            case 'x':
                printf("%-*.*x", width, precision, val->_unsigned_int);
                break;
            case 'X':
                printf("%-*.*X", width, precision, val->_unsigned_int);
                break;
            case 'f':
                printf("%-*.*f", width, precision, val->_double);
                break;
            case 'F':
                printf("%-*.*F", width, precision, val->_double);
                break;
            case 'e':
                printf("%-*.*e", width, precision, val->_double);
                break;
            case 'E':
                printf("%-*.*E", width, precision, val->_double);
                break;
            case 'G':
                printf("%-*.*G", width, precision, val->_double);
                break;
            case 'g':
                printf("%-*.*g", width, precision, val->_double);
                break;
            case 's':
                printf("%-*.*s", width, precision, val->_string);
                break;
            default:
                printf("Unreachable conversion %c\n", conversion);
                break;
        }
    } else if(flags == (LEFTADJ | WIDTH | END)) {
        switch(conversion) {
            case 'd':
            case 'i':
                printf("%-*d", width, val->_int);
                break;
            case 'c':
                printf("%-*c", width, val->_int);
                break;
            case 'u':
                printf("%-*u", width, val->_unsigned_int);
                break;
            case 'o':
                printf("%-*o", width, val->_unsigned_int);
                break;
            case 'x':
                printf("%-*x", width, val->_unsigned_int);
                break;
            case 'X':
                printf("%-*X", width, val->_unsigned_int);
                break;
            case 'f':
                printf("%-*f", width, val->_double);
                break;
            case 'F':
                printf("%-*F", width, val->_double);
                break;
            case 'e':
                printf("%-*e", width, val->_double);
                break;
            case 'E':
                printf("%-*E", width, val->_double);
                break;
            case 'G':
                printf("%-*G", width, val->_double);
                break;
            case 'g':
                printf("%-*g", width, val->_double);
                break;
            case 's':
                printf("%-*s", width, val->_string);
                break;
            case 'p':
                printf("%-*p", width, val->_ptr);
                break;
            default:
                printf("Unreachable conversion %c\n", conversion);
                break;
        }
    } else if(flags == (LEFTADJ | END)) {
        switch(conversion) {
            case 'd':
            case 'i':
                printf("%-d", val->_int);
                break;
            case 'c':
                printf("%-c", val->_int);
                break;
            case 'u':
                printf("%-u", val->_unsigned_int);
                break;
            case 'o':
                printf("%-o", val->_unsigned_int);
                break;
            case 'x':
                printf("%-x", val->_unsigned_int);
                break;
            case 'X':
                printf("%-X", val->_unsigned_int);
                break;
            case 'f':
                printf("%-f", val->_double);
                break;
            case 'F':
                printf("%-F", val->_double);
                break;
            case 'e':
                printf("%-e", val->_double);
                break;
            case 'E':
                printf("%-E", val->_double);
                break;
            case 'G':
                printf("%-G", val->_double);
                break;
            case 'g':
                printf("%-g", val->_double);
                break;
            case 's':
                printf("%-s", val->_string);
                break;
            case 'p':
                printf("%-p", val->_ptr);
                break;
            default:
                printf("Unreachable conversion %c\n", conversion);
                break;
        }
    } else {
        switch(conversion) {
            case 'd':
            case 'i':
                printf("%d", val->_int);
                break;
            case 'c':
                printf("%c", val->_int);
                break;
            case 'u':
                printf("%u", val->_unsigned_int);
                break;
            case 'o':
                printf("%o", val->_unsigned_int);
                break;
            case 'x':
                printf("%x", val->_unsigned_int);
                break;
            case 'X':
                printf("%X", val->_unsigned_int);
                break;
            case 'f':
                printf("%f", val->_double);
                break;
            case 'F':
                printf("%F", val->_double);
                break;
            case 'e':
                printf("%e", val->_double);
                break;
            case 'E':
                printf("%E", val->_double);
                break;
            case 'G':
                printf("%G", val->_double);
                break;
            case 'g':
                printf("%g", val->_double);
                break;
            case 's':
                printf("%s", val->_string);
                break;
            case 'p':
                printf("%p", val->_ptr);
                break;
            default:
                printf("Unreachable conversion %c\n", conversion);
                break;
        }
    }
    return;
}

char*
patoi(char* str, unsigned* n)
{
    char* p = str;

    for(*n = 0; isdigit(*p); p++)
        *n = *n * 10 + (*p - '0');

    // We need to be one step
    // behind because we are going
    // to the next iteration
    return p - 1;
}
